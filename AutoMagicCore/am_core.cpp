/************************************************************
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "ofMain.h"

#include "am_common.h"
#include "HF_Analyze.h"
#include "DoubtBeat.h"
#include "StopWatch.h"

#include "am_core.h"

#include "LIGHT/Light.h"
#include "VJ/vj.h"


/************************************************************
************************************************************/
static STOP_WATCH StopWatch_ColorThemeChange(60000 * 2);

static SPACE_LIGHT::LIGHT* light = SPACE_LIGHT::LIGHT::getInstance();
static SPACE_VJ::VJ* vj = SPACE_VJ::VJ::getInstance();


/************************************************************
************************************************************/

/******************************
******************************/
AUTOMAGIC_CORE::AUTOMAGIC_CORE()
: fp_debug_state(NULL)
, Boost_AGC(1e9)
, ReverseBoostAGC_for_Log(1e4)
, ReverseBoostAGC_fft(1e8)
, MIN_BEAT_TIME_MS(280)
, b_ColorAutoChange(true)
, b_StopColorAutoChange(false)
, c_INT(0)
, debug_b_BeatDetect(0)
{
	/********************
	********************/
	fp_debug_state = fopen("../../../state.csv", "w");
	if(fp_debug_state == NULL)	{ ERROR_MSG(); std::exit(1); }
	
	srand((unsigned)time(NULL));
	ParamErrorCheck();
	On_ColorChange(COLPATTERN_AUTO);
}

/******************************
******************************/
AUTOMAGIC_CORE::~AUTOMAGIC_CORE()
{
	close_all_LogFile();
}

/******************************
******************************/
void AUTOMAGIC_CORE::ParamErrorCheck()
{
}

/******************************
******************************/
void AUTOMAGIC_CORE::test()
{
	light->test();
	vj->test();
}

/******************************
******************************/
void AUTOMAGIC_CORE::setBootmode(int mode)
{
	/********************
	********************/
	enum BOOT_MODE{
		MODE__NOSET = -1,
		
		MODE__TEST = 0,
		MODE__CHECK_FILTEROUT,
		MODE__CHECK_DESIGN_PARAM,
		MODE__DEMO_LOG,
		MODE__DEMO_NOLOG,
	};
	
	switch(mode){
		case MODE__TEST:
		case MODE__CHECK_FILTEROUT:
			b_Fileout	= true;
			b_Demo		= false;
			break;
			
		case MODE__CHECK_DESIGN_PARAM:
			b_Fileout	= true;
			b_Demo		= false;
			break;
			
		case MODE__DEMO_LOG:
			b_Fileout	= true;
			b_Demo		= true;
			break;
			
		case MODE__DEMO_NOLOG:
			b_Fileout	= false;
			b_Demo		= true;
			break;
			
		default:
			b_Fileout	= true;
			b_Demo		= false;
			break;
	}
}	

/******************************
******************************/
void AUTOMAGIC_CORE::setup(int mode)
{
	/********************
	********************/
	setBootmode(mode);

	/********************
	********************/
	light->setup();
	vj->setup();	
}

/******************************
******************************/
void AUTOMAGIC_CORE::set__b_Fileout(bool flag)
{
	b_Fileout = flag;
	
	char buf[BUF_SIZE];
	sprintf(buf, "b_Fileout = %d", b_Fileout);
	printMessage(buf);
}

/******************************
******************************/
void AUTOMAGIC_CORE::exit()
{
	light->exit();
	vj->exit();
}

/******************************
description
	When user changes color theme, please call this function.
******************************/
void AUTOMAGIC_CORE::On_ColorChange(enum COLORPATTERNS ColorPattern)
{
	/********************
	********************/
	if(NUM_COLORPATTERNS <= ColorPattern){
		ERROR_MSG(); ofExit(); return;
	}

	/********************
	********************/
	if(ColorPattern == COLPATTERN_AUTO){
		b_ColorAutoChange = true;
		b_StopColorAutoChange = FALSE;
		
		SetColorTheme(COLPATTERN_AQUA, 1); // Top of AUTO is "Aqua"
		
	}else{
		b_ColorAutoChange = FALSE;
		
		SetColorTheme(ColorPattern, 1);
	}
}

/******************************
******************************/
void AUTOMAGIC_CORE::close_all_LogFile()
{
	if(fp_debug_state)	{ fclose(fp_debug_state); fp_debug_state = NULL; }
}

/******************************
description
	connect LedColor[] and Palette actually.
	This function is called when the color theme is changed.
	
param
	OperationType
		0	for Flash. Set color palette of background for next transition(smooth change from flash to new color theme)
		1	for Quick color change. for example, User changed the color theme by the hardware button.
		2	for smooth color change.
******************************/
void AUTOMAGIC_CORE::SetColorTheme(enum COLORPATTERNS ColorPattern, int OperationType)
{
	light->SetColorTheme(ColorPattern, OperationType);
	vj->SetColorTheme(ColorPattern);
}

/******************************
******************************/
void AUTOMAGIC_CORE::INT(GRAPH& Graph, double now_sec, double Vol_Thtough, double Vol_Lpf, double Vol_Bpf, double Vol_SoundSync)
{
	/********************
	********************/
	now_ms = (int)(now_sec * 1000);
	
	/********************
	********************/
	update(Graph, Vol_Thtough, Vol_Lpf, Vol_Bpf, Vol_SoundSync);
	draw();
	
	/********************
	********************/
	LastINT_ms = now_ms;
	
	fprintf_Log(fp_debug_state, "%d\n", int(ofGetElapsedTimef() * 1000));
}

/******************************
******************************/
void AUTOMAGIC_CORE::update(GRAPH& Graph, double Vol_Thtough, double Vol_Lpf, double Vol_Bpf, double Vol_SoundSync)
{
	/*
	moving ave.
	After this function, VolLevel[] are boosted with "Boost_AGC" and then averaged.
	*/
	MovingAve_vol(Vol_Thtough, Vol_Lpf, Vol_Bpf, Vol_SoundSync);
	
	/* */
	Set_vol_max_assumed();
	
	/* StateChart */
	MusicAnalysis(Graph);

	/* */
	light->update();
	vj->update();
}

/******************************
******************************/
void AUTOMAGIC_CORE::draw()
{
	light->draw();
	vj->draw((double)VolLevel[DATA_VOL_SOUNDSYNC]/ReverseBoostAGC_fft);
}

/******************************
description
	vol, vol_Lowは、和から平均を算出。
	vol_Highは、	係数を使った平均算出。
	
	和から平均を算出した方が、きちんとデータが抜けていくので、追従性が良い。
	vol, vol_Lowは、HAS2015でも和から算出しており、実績もあるので、これを踏襲。
	
	一方、vol_Highは長い時間の平均化を取って滑らかにしたいので、メモリ節約の意味もあって、係数タイプにしておく。
	
	
return
	Moving average value.
	Note that this value is boosted by "Boost_AGC".
******************************/
void AUTOMAGIC_CORE::MovingAve_vol(double vol, double vol_Low, double vol_High, double vol_SoundSync)
{
	/********************
	********************/
	enum {
		AVE_NUM_VOL				= 36,
		AVE_NUM_VOL_LOW			= 18,
		AVE_NUM_VOL_SOUNDSYNC	= 18,
	};
	const double Ck_vol_ave_High = 0.0005;
	
	
	static long long history_vol[AVE_NUM_VOL];
	static long long history_Low[AVE_NUM_VOL_LOW];
	static double last_vol_ave_High = 0;
	
	static long long history_SoundSync[AVE_NUM_VOL_LOW];

	/********************
	********************/
	static bool IsFirst = true;
	if(IsFirst){
		IsFirst = FALSE;
		
		for(int i = 0; i < AVE_NUM_VOL; i++)			{ history_vol[i] = 0; }
		for(int i = 0; i < AVE_NUM_VOL_LOW; i++)		{ history_Low[i] = 0; }
		for(int i = 0; i < AVE_NUM_VOL_SOUNDSYNC; i++)	{ history_SoundSync[i] = 0; }
		
		last_vol_ave_High = 0;
	}

	/********************
	********************/
	for(int i = AVE_NUM_VOL - 1; 0 < i; i--)		{ history_vol[i] = history_vol[i - 1]; }
	history_vol[0] = (long long)(vol * Boost_AGC);

	for(int i = AVE_NUM_VOL_LOW - 1; 0 < i; i--)	{ history_Low[i] = history_Low[i - 1]; }
	history_Low[0] = (long long)(vol_Low * Boost_AGC);
	
	vol_High *= Boost_AGC;
	last_vol_ave_High	= last_vol_ave_High * (1 - Ck_vol_ave_High) + vol_High * Ck_vol_ave_High;
	
	for(int i = AVE_NUM_VOL_SOUNDSYNC - 1; 0 < i; i--)	{ history_SoundSync[i] = history_SoundSync[i - 1]; }
	history_SoundSync[0] = (long long)(vol_SoundSync * Boost_AGC);
	
	/********************
	********************/
	long long sum = 0;
	for(int i = 0; i < AVE_NUM_VOL; i++)		{ sum += history_vol[i]; }
	VolLevel[DATA_VOL] = sum / AVE_NUM_VOL;

	sum = 0;
	for(int i = 0; i < AVE_NUM_VOL_LOW; i++)	{ sum += history_Low[i]; }
	VolLevel[DATA_VOL_LOW] = sum / AVE_NUM_VOL_LOW;
	
	VolLevel[DATA_VOL_HIGH]	= (long long)(last_vol_ave_High);
	
	sum = 0;
	for(int i = 0; i < AVE_NUM_VOL_SOUNDSYNC; i++)	{ sum += history_SoundSync[i]; }
	VolLevel[DATA_VOL_SOUNDSYNC] = sum / AVE_NUM_VOL_SOUNDSYNC;
	
	return 0;
}

/******************************
******************************/
void AUTOMAGIC_CORE::Set_vol_max_assumed()
{
	/********************
	********************/
	enum{
		// NUM_HISTORY = 900, // about 10[sec]...1 sample = 11[ms]
		NUM_HISTORY = 200, // about 2.2[sec]...1 sample = 11[ms]
	};
	
	/********************
	********************/
	static long long Vol_history[NUM_TYPE_OF_VOL_DATA][NUM_HISTORY];
	const long long MIN_OF_MAX = (long long)(0.005 * Boost_AGC);

	/********************
	********************/
	static bool IsFirst = true;
	if(IsFirst){
		IsFirst = FALSE;
		
		for(int i = 0; i < NUM_HISTORY; i++){
			Vol_history[DATA_VOL][i]			= VolLevel[DATA_VOL];
			Vol_history[DATA_VOL_LOW][i]		= VolLevel[DATA_VOL_LOW];
			Vol_history[DATA_VOL_HIGH][i]		= VolLevel[DATA_VOL_HIGH];
			Vol_history[DATA_VOL_SOUNDSYNC][i]	= VolLevel[DATA_VOL_SOUNDSYNC];
		}
	}
	
	/********************
	********************/
	for(int VolDataType = 0; VolDataType < NUM_TYPE_OF_VOL_DATA; VolDataType++){
		int k;
		for(k = NUM_HISTORY - 1; 0 < k; k--){
			Vol_history[VolDataType][k] = Vol_history[VolDataType][k - 1];
		}
	}
	Vol_history[DATA_VOL][0]			= VolLevel[DATA_VOL];
	Vol_history[DATA_VOL_LOW][0]		= VolLevel[DATA_VOL_LOW];
	Vol_history[DATA_VOL_HIGH][0]		= VolLevel[DATA_VOL_HIGH];
	Vol_history[DATA_VOL_SOUNDSYNC][0]	= VolLevel[DATA_VOL_SOUNDSYNC];

	for(int VolDataType = 0; VolDataType < NUM_TYPE_OF_VOL_DATA; VolDataType++){
		/********************
		********************/
		Vol_max_assumed[VolDataType] = Vol_history[VolDataType][0];
		for(int k = 1; k < NUM_HISTORY; k++){
			if(Vol_max_assumed[VolDataType] < Vol_history[VolDataType][k]){
				Vol_max_assumed[VolDataType] = Vol_history[VolDataType][k];
			}
		}
		if(Vol_max_assumed[VolDataType] < MIN_OF_MAX){
			Vol_max_assumed[VolDataType] = MIN_OF_MAX;
		}
		
		/********************
		********************/
		Vol_min_assumed[VolDataType] = Vol_history[VolDataType][0];
		for(int k = 1; k < NUM_HISTORY; k++){
			if(Vol_history[VolDataType][k] < Vol_min_assumed[VolDataType]){
				Vol_min_assumed[VolDataType] = Vol_history[VolDataType][k];
			}
		}
		if(Vol_min_assumed[VolDataType] < 0){
			Vol_min_assumed[VolDataType] = 0;
		}
	}
}

/******************************
******************************/
int AUTOMAGIC_CORE::MusicAnalysis(GRAPH& Graph)
{
	/********************
	初期値:非active時、Graphからはみ出すように設定.
	...太いラインがzero Levelに見えてしまうのを避ける.
	********************/
	debug_PatternChange[0] = -1;
	debug_PatternChange[1] = -1;
	debug_PatternChange[2] = -1;
	debug_PatternChange[3] = -1;
	
	/********************
	********************/
	enum{
		TIMEOUT_MS = 2000,
	};
	
	/********************
	********************/
	static int c_Beats_in_Flywheel = 0;	// for pattern change in FLYWHEEL.
	static int t_NoSound_NoBeat = 0;
	
	/********************
	********************/
	const long long THRESH_ENOUGH_BEAT = 40; // [%]
	
	const long long THRESH_TO_SOUND		= (long long)(0.004  * Boost_AGC);
	const long long THRESH_TO_NOSOUND	= (long long)(0.0038 * Boost_AGC);
	
	static long long VolLow_Peak = 0;

	static enum STATE State = STATE_NOSOUND;
	static bool IsFirst = true;
	
	/********************
	every int
	********************/
	// cal tangent of High Freq.
	double tan_HF = HF_input_vol_high( (double)VolLevel[DATA_VOL_HIGH] , now_ms);
	
	t_NoSound_NoBeat += now_ms - LastINT_ms;

	/********************
	********************/
	if(IsFirst)	{
		IsFirst = FALSE; 
		
		State = STATE_NOSOUND;
		StateChart_Transition(BOOT_TO_NOSOUND, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
	}
	
	/********************
	********************/
	long long ratio;
	if( (VolLevel[DATA_VOL] <= VolLevel[DATA_VOL_LOW]) || (VolLevel[DATA_VOL] < THRESH_TO_NOSOUND) || (VolLevel[DATA_VOL_LOW] < THRESH_TO_NOSOUND) ){
		ratio = 0;
	}else{
		ratio = VolLevel[DATA_VOL_LOW] * 100 / VolLevel[DATA_VOL];
	}
	/********************
	********************/
	switch(State){
		case STATE_NOSOUND:
		{
			if(THRESH_TO_SOUND < VolLevel[DATA_VOL]){
				State = STATE_SOUND;
				StateChart_Transition(NOSOUND_TO_SOUND, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
				
			}else if(light->Is_StayTooLong_PatternChange(State)){
				StateChart_Transition(NOSOUND_TO_NOSOUND, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
			}
			
			break;
		}
		
		case STATE_SOUND:
		{
			HF_everyINT_inSOUND(now_ms, self_Beat_interval);
				
			if(THRESH_TO_NOSOUND < VolLevel[DATA_VOL]){
				t_NoSound_NoBeat = 0;
			}
			
			if(TIMEOUT_MS <= t_NoSound_NoBeat){
				State = STATE_SOUND_DROP;
				StateChart_Transition(SOUND_TO_SOUNDDROP, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
			}else if(THRESH_ENOUGH_BEAT < ratio){ // enough volume and enough ratio.
				State = STATE_BEAT_IN;
				StateChart_Transition(SOUND_TO_BEATIN, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
			}else if(light->Is_StayTooLong_PatternChange(State)){
				StateChart_Transition(SOUND_TO_SOUND, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
			}
			break;
		}
		case STATE_SOUND_DROP:
		{
			if(THRESH_TO_SOUND < VolLevel[DATA_VOL]){
				State = STATE_SOUND;
				StateChart_Transition(SOUNDDROP_TO_SOUND, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
			}else if(light->Is_SelfPropultion_Finish()){
				State = STATE_NOSOUND;
				StateChart_Transition(SOUNDDROP_TO_NOSOUND, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
			}
			
			break;
		}
		case STATE_BEAT_IN:
		{
			if(THRESH_ENOUGH_BEAT < ratio){ // enough volume and enough ratio.
				t_NoSound_NoBeat = 0;
			}
			
			if(TIMEOUT_MS <= t_NoSound_NoBeat){
				State = STATE_BEAT_IN_DROP;
				StateChart_Transition(BEATIN_TO_BEATINDROP, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
			}else if(t_NoSound_NoBeat == 0){ // Beat checkするための条件を満たしている(上でのcheck結果が"t_NoSound_NoBeat"に反映されている)
				/********************
				enum{
					RET_NONE,
					RET_LOCK,
					RET_1ST_BEAT_DETECTED,
					RET_DOUBT_BEAT_CLEARED,
					RET_DOUBT,
				};
				********************/
				int ret = Is_Flywheel_Lock(VolLow_Peak);
				
				if(ret == 1){
					State = STATE_FLYWHEEL;
					StateChart_Transition(BEATIN_TO_FLYWHEEL, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
					
				}else if( (ret == 2) || (ret == 3) ){ // これが返ってきている時点でno Doubting
					/********************
					color set change
					********************/
					if( b_ColorAutoChange && !b_StopColorAutoChange && StopWatch_ColorThemeChange.IsTimePassed(now_ms) ){
						b_StopColorAutoChange = true;
						ColorPalette_AutoChange(2);
					}
					
					HF_ReLoad__selfBeatInterval_EnteringSOUND(self_Beat_interval, true);
					
					StateChart_Transition(BEATIN_TO_BEATIN, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
					
				}else if(ret == 4){
					StateChart_Transition(BEATIN_TO_BEATIN, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
					
				}else if(light->Is_StayTooLong_PatternChange(State)){
					StateChart_Transition(BEATIN_TO_BEATIN, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
				}
			}
			
			break;
		}
		case STATE_BEAT_IN_DROP:
		{
			if(THRESH_ENOUGH_BEAT < ratio){ // enough volume and enough ratio.
				State = STATE_BEAT_IN;
				StateChart_Transition(BEATINDROP_TO_BEATIN, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
			}else if(light->Is_SelfPropultion_Finish()){
				if(VolLevel[DATA_VOL] < THRESH_TO_NOSOUND){
					State = STATE_NOSOUND;
					StateChart_Transition(BEATINDROP_TO_NOSOUND, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
				}else{
					State = STATE_SOUND;
					StateChart_Transition(BEATINDROP_TO_SOUND, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
				}
			}

			break;
		}
		case STATE_FLYWHEEL:
		{
			/********************
			enum{
				RET_NONE,
				RET_UNLOCK,
			};
			********************/
			int ret = Is_Flywheel_UnLock(VolLow_Peak, &c_Beats_in_Flywheel);
			if(ret == 1){
				State = STATE_FLYWHEEL_DROP;
				StateChart_Transition(FLYWHEEL_TO_FLYWHEELDROP, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
				
			}else if(PATTERN_CHANGE_BEATS <= c_Beats_in_Flywheel){
				StateChart_Transition(FLYWHEEL_TO_FLYWHEEL, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
				
			}
			
			break;
		}
		case STATE_FLYWHEEL_DROP:
		{
			if(light->Is_SelfPropultion_Finish()){
				if(VolLevel[DATA_VOL] < THRESH_TO_NOSOUND){
					State = STATE_NOSOUND;
					StateChart_Transition(FLYWHEELDROP_TO_NOSOUND, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
				}else{
					State = STATE_SOUND;
					StateChart_Transition(FLYWHEELDROP_TO_SOUND, &c_Beats_in_Flywheel, &t_NoSound_NoBeat);
				}
			}
			
			break;
		}
		
		default:
			break;
	}
	
	/********************
	Log.
	INT()の終わりで現在時刻Logを取ることで、実行時間を把握できるようにしてあるので、ここでは改行なし。
	********************/
	char buf[BUF_SIZE];
	sprintf(buf, "%d,%lld,%lld,%lld,%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,,", // 改行なしね.
			now_ms,
			VolLevel[DATA_VOL]/ReverseBoostAGC_for_Log, VolLevel[DATA_VOL_LOW]/ReverseBoostAGC_for_Log, VolLevel[DATA_VOL_HIGH]/ReverseBoostAGC_for_Log,
			tan_HF/ReverseBoostAGC_for_Log,
			get_BoostMode(),
			debug_b_BeatDetect, State, debug_int[0]/* counter_Beat in IsLock() */, 
			DB_isDoubting(),
			light->CalProgress(Beat_interval, LastBeat_ms, 1),
			HF_getSubState(),
			Beat_interval,
			self_Beat_interval,
			State_IsLock,
			debug_PatternChange[0]/* Tangible PatternChange */);

	fprintf_Log(fp_debug_state, "%s", buf);
	
	
	/********************
	Log.
	INT()の終わりで現在時刻Logを取ることで、実行時間を把握できるようにしてあるので、ここでは改行なし。
	********************/
	GRAPH_DATA GprahData;
	
	/* */
	GprahData.VolThrough = int(VolLevel[DATA_VOL]/ReverseBoostAGC_for_Log);
	GprahData.VolLpf = int(VolLevel[DATA_VOL_LOW]/ReverseBoostAGC_for_Log);
	GprahData.f_Beat = debug_b_BeatDetect;
	GprahData.f_State = State;
	
	if(DB_isDoubting())	GprahData.f_DoubtBeat = 1.5;
	else				GprahData.f_DoubtBeat = 0;
	
	GprahData.f_Light_TangibleChange = debug_PatternChange[0];
	GprahData.f_Light_PatternChange = debug_PatternChange[1];
	GprahData.f_vj_PatternChange = debug_PatternChange[2];
	GprahData.f_vj_ContentsChange = debug_PatternChange[3];
	
	/* */
	GprahData.VolBpf = int(VolLevel[DATA_VOL_HIGH]/ReverseBoostAGC_for_Log);
	GprahData.tan_HighFreq = tan_HF/ReverseBoostAGC_for_Log;
	GprahData.f_Boost = get_BoostMode();
	
	/* */
	GprahData.VolSoundSync = (double)VolLevel[DATA_VOL_SOUNDSYNC]/ReverseBoostAGC_fft;
	GprahData.f_StateIsLock = State_IsLock;
	
	/* */
	Graph.lock();
	Graph.update(GprahData);
	Graph.unlock();
	
	/********************
	********************/
	return 0;

}

/******************************
******************************/
BOOSTMODE get_BoostMode()
{
	// if( HF_IsBoost() && !DB_isDoubting() ){
	if( HF_IsBoost() ){
		return BOOSTMODE_BOOST;
	}else{
		return BOOSTMODE_NORMAL;
	}
}

/******************************
******************************/
void AUTOMAGIC_CORE::fix_NumPatternChangeBeats(enum TRANSITION Transition, int Is_ColorChangeTo_Flash)
{
	char buf[BUF_SIZE];
	
	const int BEAT_INTERVAL_TOO_LONG = Beat_interval_amb / 2;
	
	switch(Transition){
		/********************
		********************/
		case SOUND_TO_SOUNDDROP:
		case SOUNDDROP_TO_SOUND:
		case BEATIN_TO_BEATINDROP:
		case BEATINDROP_TO_BEATIN:
		case FLYWHEEL_TO_FLYWHEELDROP:
			// no touch.
			break;
		
		/********************
		********************/
		case SOUND_TO_BEATIN:
			// SOUNDからの流れ:no change.
			light->fprint(";Carry PATTER_CHANGE_BEATS value\n");
			break;
			
		/********************
		********************/
		case BEATIN_TO_BEATIN:
		{
			if(BEAT_INTERVAL_TOO_LONG <= self_Beat_interval){
				PATTERN_CHANGE_BEATS = 3;
			}else{
				PATTERN_CHANGE_BEATS = 16;
			}

		}
			break;

		/********************
		********************/
		case BOOT_TO_NOSOUND:
		case NOSOUND_TO_NOSOUND:
		case SOUNDDROP_TO_NOSOUND:
		case BEATINDROP_TO_NOSOUND:
		case FLYWHEELDROP_TO_NOSOUND:
			PATTERN_CHANGE_BEATS = 8;
			break;

		case NOSOUND_TO_SOUND:
		case SOUND_TO_SOUND:
		case BEATINDROP_TO_SOUND:
		case FLYWHEELDROP_TO_SOUND:
		{
			switch(HF_getSubState()){
				case STATE_SOUND_1ST_PATTEN:
					PATTERN_CHANGE_BEATS = 8;
					break;
					
				case STATE_SOUND_NORMAL_AFTER_2ND_PATTERN:
					/* self_Beat_interval is already long and slow. */
					PATTERN_CHANGE_BEATS = 8;
					break;
					
				case STATE_SOUND_NORMAL_TO_BOOST:
				case STATE_SOUND_BOOST:
				{
					enum{
						BEATS_8,
						BEATS_16,
						BEATS_32,
						
						NUM_BEATS_TYPE,
					};
					int Weight[NUM_BEATS_TYPE]	= {2, 5, 3};
					
					int index = Dice_index(Weight, NUM_BEATS_TYPE);
					if(index == -1) { ERROR_MSG(); ofExit(); return; }
					
					if(index == BEATS_8)		PATTERN_CHANGE_BEATS = 8;
					else if(index == BEATS_16)	PATTERN_CHANGE_BEATS = 16;
					else						PATTERN_CHANGE_BEATS = 32;
				}
					break;
			}
		}
		
		/********************
		********************/
		case BEATIN_TO_FLYWHEEL:
		case FLYWHEEL_TO_FLYWHEEL:
		{
			if(b_ColorAutoChange && Is_ColorChangeTo_Flash){
				PATTERN_CHANGE_BEATS = 8;
				
			}else{
				enum{
					BEATS_8,
					BEATS_16,
					BEATS_32,
					
					NUM_BEATS_TYPE,
				};
				int Weight_Normal[NUM_BEATS_TYPE]	= {2, 4, 4};
				int Weight_Boost[NUM_BEATS_TYPE]	= {2, 5, 3};
				int *Weight;
				
				if(get_BoostMode() == BOOSTMODE_BOOST)	Weight = Weight_Boost;
				else									Weight = Weight_Normal;
				
				int index = Dice_index(Weight, NUM_BEATS_TYPE);
				if(index == -1) { ERROR_MSG(); ofExit(); return; }
				
				if(index == BEATS_8)		PATTERN_CHANGE_BEATS = 8;
				else if(index == BEATS_16)	PATTERN_CHANGE_BEATS = 16;
				else						PATTERN_CHANGE_BEATS = 32;
			}
		}
			break;

		/********************
		********************/
		default:
			// 来ないはず.
			ERROR_MSG(); std::exit(1);
			break;
	}
	
	/********************
	********************/
	sprintf(buf, ";PATTER_CHANGE_BEATS = %d\n", PATTERN_CHANGE_BEATS);
	light->fprint(buf);
}

/******************************
******************************/
int AUTOMAGIC_CORE::PlausibleOfArray(int* array, int num)
{
	char buf[BUF_SIZE];
	
	qsort(array, num, sizeof(int), compare_int);
	
	sprintf(buf, ";%s:(", __FUNCTION__);
	light->fprint(buf);
	for(int i = 0; i < num; i++){
		sprintf(buf, "%d, ", array[i]);
		light->fprint(buf);
	}
	sprintf(buf, ")\n");
	light->fprint(buf);

	if(num < 4){
		if(Beat_interval_amb < array[0])	return Beat_interval_amb;
		else								return array[0];
		
	}else{
		
		if(Beat_interval_amb < array[1])	return Beat_interval_amb;
		else								return array[1];
	}
}

/******************************
description
	for qsort()
	Sort:Big to Small
	
	http://www.cc.kyoto-su.ac.jp/~yamada/ap/qsort.html
******************************/
int AUTOMAGIC_CORE::compare_int(const void *a, const void *b)
{
    return *(int*)b - *(int*)a;
}

/******************************
description
	Color theme paletteの変更.
	
parameter
	OperationType( cf. SetColorTheme() )
		0	for Flash. 
			change the color palette in background.
			after FLASH pattern, color will be changed to the new color palette smoothly.
			
		2	for smooth color change.
******************************/
void AUTOMAGIC_CORE::ColorPalette_AutoChange(int OperationType)
{
	if(b_ColorAutoChange){
		const PALETTE *pre_palette = system_ColorTheme_palette;
		
		const int MAX_RETRY = 3;
		int counter = 0;
		int RandomNumber;
		do{
			RandomNumber = rand() % COLPATTERN_RAINBOW;
			
			if(&Palette[RandomNumber] != pre_palette) break;

			counter++;
			
		}while(counter < MAX_RETRY);
		
		SetColorTheme( (enum COLORPATTERNS)RandomNumber, OperationType );
	}
}

/******************************
******************************/
void AUTOMAGIC_CORE::init_StateChart()
{
	/********************
	********************/
	Beat_interval = Beat_interval_amb;
	LastBeat_ms = now_ms;
	
	self_Beat_interval = Beat_interval_amb;
	
	/********************
	********************/
	HF_init();
	
	c_INT = 0;
	
	DB_init();
	
	StopWatch_ColorThemeChange.Reset();
}

/******************************
******************************/
bool AUTOMAGIC_CORE::IsVolDown_Enough_fromPeak(long long VolLowNow, long long VolLow_Peak)
{
	if(VolLowNow < double(VolLow_Peak) * 0.8){
		return true;
	}else{
		return false;
	}
}

/******************************
******************************/
void AUTOMAGIC_CORE::StateChart_Transition(enum TRANSITION Transition, int *c_Beats_in_Flywheel, int *t_NoSound_NoBeat)
{
	/********************
	********************/
	bool Is_Flash = false;

	/********************
	********************/
	switch(Transition){
		case BOOT_TO_NOSOUND:
		{
			init_StateChart();
			break;
		}
		case NOSOUND_TO_NOSOUND:
		{
			break;
		}
		case NOSOUND_TO_SOUND:
		{
			HF_EnterSOUND(now_ms, self_Beat_interval);
			break;
		}
		case SOUND_TO_SOUND:
		{
			if(HF_Transraion_Sound_to_Sound()){ // Boost mode refresh first.
				light->Reset_StopWatch_TangiblePatternChange();
			} 
			break;
		}
		case SOUND_TO_BEATIN:
		{
			/********************
			********************/
			HF_EnterBEATIN();
			
			DB_ClearFlag_DoubtSet();
			
			/********************
			********************/
			c_INT = 0;
			if(Beat_interval_amb <= Beat_interval) Beat_interval = Beat_interval_temp;
			
			break;
		}
		case SOUND_TO_SOUNDDROP:
		{
			break;
		}
		case SOUNDDROP_TO_NOSOUND:
		{
			init_StateChart();
			break;
		}
		case SOUNDDROP_TO_SOUND:
		{
			break;
		}
		case BEATIN_TO_BEATIN:
		{
			break;
		}
		case BEATIN_TO_FLYWHEEL:
		{
			HF_EnterFLYWHEEL(now_ms);
			
			DB_ClearFlag_DoubtSet();
			
			b_StopColorAutoChange = FALSE;
			
			c_INT = 0;
			
			self_Beat_interval = Beat_interval;
			
			break;
		}
		case BEATIN_TO_BEATINDROP:
		{
			break;
		}
		case BEATINDROP_TO_NOSOUND:
		{
			init_StateChart();
			break;
		}
		case BEATINDROP_TO_SOUND:
		{
			HF_EnterSOUND_fromDrop(now_ms, self_Beat_interval);
			break;
		}
		case BEATINDROP_TO_BEATIN:
		{
			break;
		}
		case FLYWHEEL_TO_FLYWHEEL:
		{
			break;
		}
		case FLYWHEEL_TO_FLYWHEELDROP:
		{
			HF_DropFlywheel(now_ms);
			break;
		}
		case FLYWHEELDROP_TO_NOSOUND:
		{
			init_StateChart();
			break;
		}
		case FLYWHEELDROP_TO_SOUND:
		{
			HF_EnterSOUND(now_ms, self_Beat_interval);
			break;
		}
		
		default:
			break;
	}

	/***********************
	***********************/
	light->StateChart_Transition( Transition, Is_Flash );
	vj->StateChart_Transition( Transition );
	
	/***********************
	***********************/
	fix_NumPatternChangeBeats(Transition, Is_Flash);

	/***********************
	***********************/
	*c_Beats_in_Flywheel = 0;
	*t_NoSound_NoBeat = 0;
}

/******************************
******************************/
int AUTOMAGIC_CORE::Is_VolLpf_HighEnough()
{
	if( (Vol_min_assumed[DATA_VOL_LOW] + (Vol_max_assumed[DATA_VOL_LOW] - Vol_min_assumed[DATA_VOL_LOW]) * 0.4) < VolLevel[DATA_VOL_LOW] ){
		return true;
	}else{
		return false;
	}
}

/******************************
return
	enum{
		RET_NONE,
		RET_LOCK,
		RET_1ST_BEAT_DETECTED,
		RET_DOUBT_BEAT_CLEARED,
		RET_DOUBT,
	};
******************************/
int AUTOMAGIC_CORE::Is_Flywheel_Lock(long long& VolLow_Peak)
{
	/********************
	********************/
	enum{
		LOCK_COUNT = 5, // Lock after 4Beat.
	};
	
	enum{
		RET_NONE,
		RET_LOCK,
		RET_1ST_BEAT_DETECTED,
		RET_DOUBT_BEAT_CLEARED,
		RET_DOUBT,
	};
	
	int ret = (int)RET_NONE;
	
	static int counter_Beat = 0;
	static int interval_history[LOCK_COUNT - 1];
	
	/* */
	static long long Last_VolLevel = 0;
	static long long Last_tangent = 0;
	
	// static STATE__BEAT_DETECT State_IsLock;

	/********************
	********************/
	long long tangent = VolLevel[DATA_VOL_LOW] - Last_VolLevel;
	
	debug_b_BeatDetect = 0;
	
	if(c_INT < 2){
		counter_Beat = 0;
		c_INT++;
		
		State_IsLock = STATE_WAIT_1ST_PEAK;
		
	}else{
		
		switch(State_IsLock){
			case STATE_WAIT_1ST_PEAK:
				if( ((0 < Last_tangent) && (tangent <= 0)) &&
					(Is_VolLpf_HighEnough())
					 )
				{
					// Beat detect
					debug_b_BeatDetect = 2;
					
					counter_Beat++;
					
					LastBeat_ms = now_ms;
					
					/********************
					********************/
					char buf[BUF_SIZE];
					sprintf(buf, ";Beat in %s. interval = %d(1st Beat in STATE_BEAT_IN)\n", __FUNCTION__, Beat_interval);
					light->fprint(buf);
					
					if(!DB_isDoubting()){
						ret = RET_1ST_BEAT_DETECTED;
						
					}else{
						sprintf(buf, ";Doubting!!!\n");
						light->fprint(buf);
					}
					
					/********************
					********************/
					State_IsLock = STATE_KEEP_PEAK;
					VolLow_Peak = VolLevel[DATA_VOL_LOW];
				}
				break;
				
			case STATE_KEEP_PEAK:
				if(VolLow_Peak < VolLevel[DATA_VOL_LOW]){
					VolLow_Peak = VolLevel[DATA_VOL_LOW];
				}else if( IsVolDown_Enough_fromPeak(VolLevel[DATA_VOL_LOW], VolLow_Peak) ){
					State_IsLock = STATE_WAIT_NEXT_PEAK;
				}
				
				if(700 < now_ms - LastBeat_ms){
					// 本状態でStayの時は、連続でLog出力しないため
					if(0 < counter_Beat){
						char buf[BUF_SIZE];
						sprintf(buf, "%s KeepPeak timeout ... Retry.\n", __FUNCTION__);
						light->fprint(buf);
					}
					
					counter_Beat = 0;
					
					if(!DB_isDoubtSetInThisState())	ret = RET_DOUBT;
					
					DB_SetDoubt(true);
				}
				break;
				
			case STATE_WAIT_NEXT_PEAK:
				if( ((0 < Last_tangent) && (tangent <= 0)) &&
					(Is_VolLpf_HighEnough()) && 
					(MIN_BEAT_TIME_MS < now_ms - LastBeat_ms)
					 )
				{
					// Beat detect
					debug_b_BeatDetect = 2;
					
					if( (1 <= counter_Beat) && (counter_Beat <= LOCK_COUNT - 1) ) interval_history[counter_Beat - 1] = now_ms - LastBeat_ms;
					
					counter_Beat++;
					
					LastBeat_ms = now_ms;
					
					light->Beat_PatternIndex_next_AllBlock();
					vj->Beat_PatternIndex_next_AllBlock();
					
					State_IsLock = STATE_KEEP_PEAK;
					VolLow_Peak = VolLevel[DATA_VOL_LOW];
					
					if(2 <= counter_Beat){
						if(DB_isDoubting()) ret = RET_DOUBT_BEAT_CLEARED;
						
						DB_SetDoubt(false);
						
						/********************
						********************/
						char buf[BUF_SIZE];
						sprintf(buf, ";Beat in %s. interval = %d\n", __FUNCTION__, interval_history[counter_Beat - 2]);
						light->fprint(buf);
					}
					
					if(DB_isDoubting()){
						char buf[BUF_SIZE];
						sprintf(buf, ";Still Doubting!!!\n");
						light->fprint(buf);
					}
					

				}else if(1500 < now_ms - LastBeat_ms){
					// 本状態でStayの時は、連続でLog出力しないため
					if(0 < counter_Beat){
						char buf[BUF_SIZE];
						sprintf(buf, "%s Wait next Beat timeout ... Retry.\n", __FUNCTION__);
						light->fprint(buf);
					}
					
					counter_Beat = 0;
					
					if(!DB_isDoubtSetInThisState())	ret = RET_DOUBT;
					
					DB_SetDoubt(true);
				}
				break;
		}
	}
	
	/********************
	********************/
	Last_VolLevel = VolLevel[DATA_VOL_LOW];
	Last_tangent = tangent;
	

	/********************
	********************/
	debug_int[0] = counter_Beat;
	if(LOCK_COUNT <= counter_Beat){
		Beat_interval = PlausibleOfArray(interval_history, counter_Beat - 1);
		return int(RET_LOCK);

	}else{
		return ret;
	}
}

/******************************
******************************/
int AUTOMAGIC_CORE::Is_Flywheel_UnLock(long long& VolLow_Peak, int *Counter_Beats)
{
	/********************
	********************/
	enum{
		RET_NONE,
		RET_UNLOCK,
	};
	
	int ret = (int)RET_NONE;

	/********************
	********************/
	const int NextBeat_min_ms = (long)(LastBeat_ms + Beat_interval * 0.7);
	const int NextBeat_max_ms = (long)(LastBeat_ms + Beat_interval * 2.2); // half Beat

	const int NextBeat_min_ms_double = (long)(LastBeat_ms + Beat_interval * 0.3);
	
	/********************
	********************/
	// static STATE__BEAT_DETECT State_IsLock;
	
	static long long Last_VolLevel = 0;
	static long long Last_tangent = 0;

	static bool b_double  = false;
	static int LastBeat_double = 0;

	long long tangent = VolLevel[DATA_VOL_LOW] - Last_VolLevel;

	debug_b_BeatDetect = 0;
	if(c_INT < 2){
		c_INT++;
		b_double = false;
		
		State_IsLock = STATE_KEEP_PEAK;
		
	}else{
		if(NextBeat_max_ms <= now_ms){
			if(State_IsLock == STATE_KEEP_PEAK) DB_SetDoubt(true);
			
			return RET_UNLOCK;

		}else{
			
			switch(State_IsLock){
				case STATE_KEEP_PEAK:
					if(VolLow_Peak < VolLevel[DATA_VOL_LOW])									{ VolLow_Peak = VolLevel[DATA_VOL_LOW]; }
					else if( IsVolDown_Enough_fromPeak(VolLevel[DATA_VOL_LOW], VolLow_Peak) )	{ State_IsLock = STATE_WAIT_NEXT_PEAK; }
					
					break;
					
				case STATE_WAIT_NEXT_PEAK:
					if( (0 < Last_tangent) && (tangent <= 0) && (Is_VolLpf_HighEnough()) ){
						int LastBeat_temp;
						if(b_double)	LastBeat_temp = LastBeat_double;
						else			LastBeat_temp = LastBeat_ms;

						if(MIN_BEAT_TIME_MS < now_ms - LastBeat_temp){
							// Beatdetect.
							debug_b_BeatDetect = 2;
							(*Counter_Beats)++;
							
							if( (NextBeat_min_ms < now_ms) && (now_ms < NextBeat_max_ms) ){
								
								if(b_double){
									b_double = FALSE;
									Beat_interval = now_ms - LastBeat_double;
								}else{
									Beat_interval = now_ms - LastBeat_ms;
								}
								LastBeat_ms = now_ms;
								
								light->Beat_PatternIndex_next_AllBlock();
								vj->Beat_PatternIndex_next_AllBlock();
								
								/********************
								********************/
								char buf[BUF_SIZE];
								sprintf(buf, ";Beat in %s. interval = %d\n", __FUNCTION__, Beat_interval);
								light->fprint(buf);
								
								/********************
								********************/
								State_IsLock = STATE_KEEP_PEAK;
								VolLow_Peak = VolLevel[DATA_VOL_LOW];
								

							}else if( (NextBeat_min_ms_double < now_ms) && (now_ms < NextBeat_max_ms) ){
								/********************
								double Beat
								現在走行中のPatternには影響を与えず、次のBeatでdouble Beat考慮したparamを格納するための仕掛けをsetして抜ける.
								********************/
								b_double = true;
								LastBeat_double = now_ms;

								/********************
								********************/
								char buf[BUF_SIZE];
								sprintf(buf, ";Double Beat in %s\n", __FUNCTION__);
								light->fprint(buf);
								
								/********************
								********************/
								State_IsLock = STATE_KEEP_PEAK;
								VolLow_Peak = VolLevel[DATA_VOL_LOW];
								
							}else{
								// out of predicted zone.
								
							}
						}
					}
					break;
					
				default:
					break;
			}
		}
	}
	
	Last_VolLevel = VolLevel[DATA_VOL_LOW];
	Last_tangent = tangent;
	
	return ret;
}


