/************************************************************
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "vj.h"
#include "vj_ShortPattern.h"
#include "vj_BlockPattern.h"
#include "vj_BlockGrouping.h"
#include "vj_Weight.h"

/************************************************************************************************************************/
namespace SPACE_VJ{



/************************************************************
************************************************************/

/******************************
******************************/
VJ_DATASET::VJ_DATASET()
: mov_a(0)
{
}

/******************************
******************************/
VJ_DATASET::~VJ_DATASET()
{
}

/************************************************************
************************************************************/

/******************************
******************************/
VJ::VJ()
: StopWatch_AddGenerativeImage(10000)
, StopWatch_AddText(4000)
, StopWatch_AddEffectToMov(10000)
, StopWatch_AddEffectToMov_0(10000)

, StopWatch_ContentsChangeTiming(40000)
, StopWatch_EnterSOUND(10000)
, b_ContentsChange(false)

, t__From_mov_a(0)
, t_Transition_mov_a(2000)
, b_SmoothingOnPatternChange(true)

, fp_ColorTheme(NULL)
, fp_ContentsChangeTiming(NULL)
, fp_BpmInfo(NULL)
, fp_Alpha_fft(NULL)
, fp_test(NULL)

, OscVj("127.0.0.1", 12349, 12348)
, b_VjExist(true)
{
	/********************
	********************/
	fp_ColorTheme = fopen("../../../VJSB_ColorTheme.txt", "w");
	if(fp_ColorTheme == NULL)				{ ERROR_MSG(); std::exit(1); }
	
	fp_ContentsChangeTiming = fopen("../../../VJSB_ContentsChangeTiming.txt", "w");
	if(fp_ContentsChangeTiming == NULL)		{ ERROR_MSG(); std::exit(1); }
	
	fp_BpmInfo = fopen("../../../VJSB_BpmInfo.txt", "w");
	if(fp_BpmInfo == NULL)					{ ERROR_MSG(); std::exit(1); }
	
	fp_Alpha_fft = fopen("../../../VJSB_Alpha_fft.txt", "w");
	if(fp_Alpha_fft == NULL)				{ ERROR_MSG(); std::exit(1); }
	
	/********************
	********************/
	fp_test = fopen("../../../vj_test.csv", "w");
	if(fp_test == NULL)						{ ERROR_MSG(); std::exit(1); }
}

/******************************
******************************/
VJ::~VJ()
{
	close_all_LogFile();
}

/******************************
******************************/
void VJ::exit()
{
	ofxOscMessage m;
	m.setAddress("/Quit");
	m.addIntArg(1);
	
	OscVj.OscSend.sendMessage(m);
}

/******************************
******************************/
void VJ::close_all_LogFile()
{
	if(fp_ColorTheme)			{ fclose(fp_ColorTheme); fp_ColorTheme = NULL;}
	if(fp_ContentsChangeTiming)	{ fclose(fp_ContentsChangeTiming); fp_ContentsChangeTiming = NULL; }
	if(fp_BpmInfo)				{ fclose(fp_BpmInfo); fp_BpmInfo = NULL; }
	if(fp_Alpha_fft)			{ fclose(fp_Alpha_fft); fp_Alpha_fft = NULL; }
	
	if(fp_test)					{ fclose(fp_test); fp_test = NULL; }
}

/******************************
******************************/
void VJ::test()
{
}

/******************************
******************************/
void VJ::Beat_PatternIndex_next_AllBlock()
{
	for(int Block_id = 0; !Is_PeriodOfBlockGroup(Block[Block_id]); Block_id++){
		if(Block[Block_id].BpInfo.PlayMode == BEAT_PROPULSION){
			PatternIndex_next(Block[Block_id].Bp_Pattern[Block[Block_id].BpInfo.Bp_Pattern_index], Block[Block_id].BpInfo.Pattern_index);
		}
	}
}

/******************************
******************************/
void VJ::SetColorTheme(int ThemeId)
{
	/********************
	********************/
	fprintf_Vj_ColorTheme(fp_ColorTheme, "<time_ms> %10d %d\n", now_ms, ThemeId);
	
	/********************
	********************/
	if(b_Demo && b_VjExist){
		ofxOscMessage m;
		m.setAddress("/VJColorTheme");
		m.addIntArg(ThemeId);
		
		OscVj.OscSend.sendMessage(m);
	}
}

/******************************
******************************/
void VJ::ContentsChange()
{
	/********************
	********************/
	debug_PatternChange[3] = 8.5;

	/********************
	********************/
	fprintf_Vj_ContentsChangeTiming(fp_ContentsChangeTiming, "<time_ms> %10d\n", now_ms);
	
	/********************
	********************/
	if(b_Demo && b_VjExist){
		ofxOscMessage m;
		m.setAddress("/VJContentsChange");
		m.addIntArg(1);
		
		OscVj.OscSend.sendMessage(m);
	}
}

/******************************
******************************/
void VJ::SetBpmInfo(int self_Beat_interval)
{
	/********************
	********************/
	fprintf_Vj_BpmInfo(fp_BpmInfo, "<time_ms> %10d %10d\n", now_ms, self_Beat_interval);
	
	/********************
	********************/
	if(b_Demo && b_VjExist){
		ofxOscMessage m;
		m.setAddress("/VJ_BpmInfo");
		m.addIntArg(self_Beat_interval);
		
		OscVj.OscSend.sendMessage(m);
	}
}

/******************************
******************************/
void VJ::init_StateChart()
{
	for(int i = 0; !Is_PeriodOfBlockGroup(Block[i]); i++){
		Block[i].Set_AllBpInfo_SelfPropulsion_LastBeatms(now_ms);
	}
	
	b_SmoothingOnPatternChange = true;
}

/******************************
******************************/
void VJ::Process_in_Transition(STATE State)
{
	/********************
	********************/
	fprintf_Log(fp_Alpha_fft, ";Add Effect...(GeneratedImage, text, Mov, Mov0, Strobe) = (");
	
	Dice_ifAddEffect(W_AddGeneratedImage, State, get_BoostMode(), &VJ_DATASET::set__b_GeneratedImage_on, VjDataSet.get__b_GeneratedImage_on(), StopWatch_AddGenerativeImage);
	Dice_ifAddEffect(W_AddText, State, get_BoostMode(), &VJ_DATASET::set__b_text_on, VjDataSet.get__b_text_on(), StopWatch_AddText);
	Dice_ifAddEffect(W_AddEffectToMov_All, State, get_BoostMode(), &VJ_DATASET::set__b_mov_Effect_On, VjDataSet.get__b_mov_Effect_On(), StopWatch_AddEffectToMov);
	Dice_ifAddEffect(W_AddEffectToMov_0, State, get_BoostMode(), &VJ_DATASET::set__b_mov0_Effect_On, VjDataSet.get__b_mov0_Effect_On(), StopWatch_AddEffectToMov_0);
	
	fprintf_Log(fp_Alpha_fft, ")\n");
	
	
	SelectPlayMode(State);
	SelectBlockPattern(State, get_BoostMode());
	
	/********************
	********************/
	for(int id = 0; !Is_PeriodOfBlockGroup(Block[id]); id++){
		Block[id].Set_AllBpInfo_SelfPropulsion_LastBeatms(now_ms);
	}
}

/******************************
******************************/
void VJ::SelectBlockPattern(enum STATE State, BOOSTMODE BoostMode)
{
	/********************
	********************/
	debug_PatternChange[2] = 8.0;
	
	/********************
	set Bp_Pattern_index of BpInfo
	********************/
	for(int id = 0; !Is_PeriodOfBlockGroup(Block[id]); id++){
		int NumCandidates = get_num_PatternTypes_in_Bp(Block[id].Bp_Pattern);
		int* Weight = (int*)malloc(sizeof(int) * NumCandidates);
		
		BP_INFO *BpInfo = &Block[id].BpInfo;
		
		enum VJ_ALPHA_CH_TYPE AlphaType = BpInfo->AlphaChType;
		enum PLAYMODE PlayMode = BpInfo->PlayMode;
		
		
		for(int i = 0; i < NumCandidates; i++){
			Weight[i] = Block[id].Bp_Pattern[i].Weight[AlphaType][State][PlayMode][BoostMode];
		}
		
		BpInfo->Bp_Pattern_index = Dice_index(Weight, NumCandidates);
		if(BpInfo->Bp_Pattern_index == -1) { ERROR_MSG(); ofExit(); return; }
		
		
		/* */
		Dice_StartPatternId(BpInfo, Block[id].Bp_Pattern[BpInfo->Bp_Pattern_index].StartPatternId_Candidate);
		
		/********************
		********************/
		free(Weight);
		
		/********************
		********************/
		double phase_deg = asin((Block[id].BpInfo.LastOutputLevel - 0.5) * 2) * 180.0 / PI; // 0to1 -> -1->1にしてからasin()
		
		double delta_deg = 90 - phase_deg;
		
		int sgn = 1;
		if(rand() % 2 == 0)	sgn = 1;
		else				sgn = -1;
		Block[id].BpInfo.PhaseDeg_for_BlockPattern = 90 + sgn * delta_deg;
		
		/********************
		********************/
		Block[id].BpInfo.t_NewPatternStart = now_ms;
	}
	
	
	/********************
	log
	********************/
	char buf[BUF_SIZE];
	
	if( BoostMode == BOOSTMODE_BOOST )	sprintf(buf, ";Boost mode\n");
	else								sprintf(buf, ";Normal mode(No Boost)\n");
	fprintf_Log(fp_Alpha_fft, "%s", buf);

	sprintf(buf, ";Pattern = (\n");
	fprintf_Log(fp_Alpha_fft, "%s", buf);
	
	for(int id = 0; !Is_PeriodOfBlockGroup(Block[id]); id++){
		
		BP_INFO *BpInfo = &Block[id].BpInfo;
		
		sprintf(	buf, "\t[%5d]%50s, start id = %5d, phase = %f\n",
					id, Block[id].Bp_Pattern[BpInfo->Bp_Pattern_index].name, BpInfo->Pattern_index, BpInfo->PhaseDeg_for_BlockPattern);
		fprintf_Log(fp_Alpha_fft, "%s", buf);
	}
	sprintf(buf, ")\n\n");
	fprintf_Log(fp_Alpha_fft, "%s", buf);
}

/******************************
******************************/
void VJ::Dice_ifAddEffect(const int (*W_Table)[NUM_BOOSTMODE][NUM_ADD_EFFECT], STATE State, BOOSTMODE BoostMode, pFunc_Set_bool pFunc, bool b_Current, STOP_WATCH& StopWatch)
{
	/********************
	********************/
	if(!b_Current || StopWatch.IsTimePassed(now_ms)){
		/********************
		********************/
		int Weight[NUM_ADD_EFFECT];
		for(int i = 0; i < NUM_ADD_EFFECT; i++){
			Weight[i] = W_Table[State][BoostMode][i];
		}
		
		int index = Dice_index(Weight, NUM_ADD_EFFECT);
		if(index == -1) { ERROR_MSG(); ofExit(); return; }
		
		/********************
		********************/
		char buf[BUF_SIZE];
		if(index == ADD_EFFECT__ON){
			(VjDataSet.*pFunc)(true);
			sprintf(buf, "ON, ");
			
			StopWatch.start(now_ms);
			
		}else{
			(VjDataSet.*pFunc)(false);
			sprintf(buf, "OFF, ");
		}
		fprintf_Log(fp_Alpha_fft, "%s", buf);
		
	}else{
		
		fprintf_Log(fp_Alpha_fft, "Skip, ");
		
	}
}

/******************************
******************************/
void VJ::SelectPlayMode(STATE State)
{
	/********************
	********************/
	char buf[BUF_SIZE];
	sprintf(buf, ";PlaymodeLum = (");
	fprintf_Log(fp_Alpha_fft, "%s", buf);
	
	/********************
	********************/
	for(int id = 0; !Is_PeriodOfBlockGroup(Block[id]); id++){
		if(DB_isDoubtSetInThisState()){
			Block[id].BpInfo.PlayMode = SELF_PROPULSION;
			
		}else{
			int Weight[NUM_PLAYMODES];
			for(int i = 0; i < NUM_PLAYMODES; i++){
				Weight[i] = Block[id].Weight_PlayMode[State][i];
			}
			
			int index = Dice_index(Weight, NUM_PLAYMODES);
			if(index == -1) { ERROR_MSG(); ofExit(); return; }
			
			Block[id].BpInfo.PlayMode = (enum PLAYMODE)index;
		}
		
		sprintf(buf, "%d, ", (int)Block[id].BpInfo.PlayMode);
		fprintf_Log(fp_Alpha_fft, "%s", buf);
	}
	
	fprintf_Log(fp_Alpha_fft, ")\n");
}

/******************************
description
	各BlockのBp_Patternを変更.
	Beat_interval, self_Beat_interval, LastBeat_msは、main側で、
	SelfPropulsion.LastBeat_msはvj側、update()にて更新.
	
	上記情報から、各BlockのLevelを計算できる状況が整う,
	→update()にてcal.
******************************/
void VJ::StateChart_Transition(TRANSITION Transition)
{
	/********************
	********************/
	char buf[BUF_SIZE];
	sprintf(buf, "\n;%10d[ms] Transition = %d-------------------------------------------------------------------------------------------------\n", now_ms, Transition);
	fprintf_Log(fp_Alpha_fft, "%s", buf);
	
	/********************
	********************/
	switch(Transition){
		case BOOT_TO_NOSOUND:
		{
			t__From_mov_a = -1;
			
			init_StateChart();
			Process_in_Transition(STATE_NOSOUND);
			break;
		}
		case NOSOUND_TO_NOSOUND:
		{
			t__From_mov_a = -1;
			
			Process_in_Transition(STATE_NOSOUND);
			break;
		}
		case NOSOUND_TO_SOUND:
		{
			fprintf_Log(fp_Alpha_fft, ";No pattern change.\n");
			t__From_mov_a = now_ms;
			break;
		}
		case SOUND_TO_SOUND:
		{
			Process_in_Transition(STATE_SOUND);
			break;
		}
		case SOUND_TO_BEATIN:
		{
			// StopWatch_ContentsChangeTiming.Reset();
			fprintf_Log(fp_Alpha_fft, ";No pattern change.\n");
			break;
		}
		case SOUND_TO_SOUNDDROP:
		{
			fprintf_Log(fp_Alpha_fft, ";No pattern change.\n");
			break;
		}
		case SOUNDDROP_TO_NOSOUND:
		{
			t__From_mov_a = -1;
			
			init_StateChart();
			Process_in_Transition(STATE_NOSOUND);
			break;
		}
		case SOUNDDROP_TO_SOUND:
		{
			fprintf_Log(fp_Alpha_fft, ";No pattern change.\n");
			break;
		}
		case BEATIN_TO_BEATIN:
		{
			if(StopWatch_EnterSOUND.IsTimePassed(now_ms)){
				if( (b_ContentsChange == false) && StopWatch_ContentsChangeTiming.IsTimePassed(now_ms) ){
					ContentsChange();
					b_ContentsChange = true;
					StopWatch_ContentsChangeTiming.start(now_ms, 40000);
				}
				
				Process_in_Transition(STATE_BEAT_IN);
			}
			break;
		}
		case BEATIN_TO_FLYWHEEL:
		{
			if( (b_ContentsChange == false) && StopWatch_ContentsChangeTiming.IsTimePassed(now_ms) ){
				ContentsChange();
				StopWatch_ContentsChangeTiming.start(now_ms, 40000);
			}

			Process_in_Transition(STATE_FLYWHEEL);
			SetBpmInfo(self_Beat_interval);
			
			/* */
			b_SmoothingOnPatternChange = false;
			b_ContentsChange = false;
			
			break;
		}
		case BEATIN_TO_BEATINDROP:
		{
			fprintf_Log(fp_Alpha_fft, ";No pattern change.\n");
			break;
		}
		case BEATINDROP_TO_NOSOUND:
		{
			t__From_mov_a = -1;
			
			init_StateChart();
			Process_in_Transition(STATE_NOSOUND);
			break;
		}
		case BEATINDROP_TO_SOUND:
		{
			Process_in_Transition(STATE_SOUND);
			b_SmoothingOnPatternChange = true;
			StopWatch_EnterSOUND.start(now_ms);
			break;
		}
		case BEATINDROP_TO_BEATIN:
		{
			fprintf_Log(fp_Alpha_fft, ";No pattern change.\n");
			break;
		}
		case FLYWHEEL_TO_FLYWHEEL:
		{
			/* */
			SetBpmInfo(self_Beat_interval);
			
			/* */
			Process_in_Transition(STATE_FLYWHEEL);
			break;
		}
		case FLYWHEEL_TO_FLYWHEELDROP:
		{
			fprintf_Log(fp_Alpha_fft, ";No pattern change.\n");
			break;
		}
		case FLYWHEELDROP_TO_NOSOUND:
		{
			t__From_mov_a = -1;
			
			init_StateChart();
			Process_in_Transition(STATE_NOSOUND);
			break;
		}
		case FLYWHEELDROP_TO_SOUND:
		{
			if( StopWatch_ContentsChangeTiming.IsTimePassed(now_ms) ){
				ContentsChange();
				// b_ContentsChange : no touch.
				
				StopWatch_ContentsChangeTiming.start(now_ms, 3000);
			}
			
			Process_in_Transition(STATE_SOUND);
			StopWatch_EnterSOUND.start(now_ms);
			b_SmoothingOnPatternChange = true;
			break;
		}
		
		default:
			break;
	}
}

/******************************
******************************/
void VJ::setup()
{
	/********************
	********************/
	udpConnection.Create();
	// udpConnection.Connect("10.0.0.3", UDP_SEND_PORT);
	udpConnection.Connect("127.0.0.1", UDP_SEND_PORT);
	udpConnection.SetNonBlocking(true);
}

/******************************
******************************/
void VJ::update()
{
	/********************
	mov_a
	********************/
	if(t__From_mov_a == -1)									VjDataSet.set__mov_a(0.0);
	else if( t_Transition_mov_a < now_ms - t__From_mov_a )	VjDataSet.set__mov_a(1.0);
	else if(now_ms - t__From_mov_a <= 0)					VjDataSet.set__mov_a(0.0);
	else													VjDataSet.set__mov_a((1.0 / t_Transition_mov_a) * (now_ms - t__From_mov_a));
	
	/********************
	********************/
	fprintf_Log(fp_Alpha_fft, "(Self or Beat, Progress) of Block 0, 1, ... = \n");
	for(int id = 0; !Is_PeriodOfBlockGroup(Block[id]); id++){
		update_OneBlock(Block[id]);
	}
	fprintf_Log(fp_Alpha_fft, "\n\n");
	
}

/******************************
******************************/
void VJ::update_OneBlock(BLOCK& block)
{
	fprintf_Log(fp_Alpha_fft, "{ ");
	
	char buf[BUF_SIZE];
	
	BP_INFO *BpInfo = &(block.BpInfo);
	
	/********************
	********************/
	int Progress;
	
	if(BpInfo->PlayMode == SELF_PROPULSION){
		Progress = CalProgress(self_Beat_interval, BpInfo->SelfPropulsion.LastBeat_ms, block.Bp_Pattern[BpInfo->Bp_Pattern_index].Speed);
		sprintf(buf, "(Self, %d), ", (int)Progress);
	}else{
		Progress = CalProgress(Beat_interval, LastBeat_ms, block.Bp_Pattern[BpInfo->Bp_Pattern_index].Speed);
		sprintf(buf, "(Beat, %d), ", (int)Progress);
	}
	fprintf_Log(fp_Alpha_fft, "%s", buf);
	
	/********************
	********************/
	double Lev = CalLev_from_ShortPattern(block.Bp_Pattern[BpInfo->Bp_Pattern_index].pShortPattern[BpInfo->Pattern_index], Progress, BpInfo->PhaseDeg_for_BlockPattern);
	
	/* */
	if	(	
			(!VjDataSet.get__b_GeneratedImage_on()) && 
			( (block.BpInfo.AlphaChType == VJ_ALPHA_CH_TYPE__INDICATOR) || (block.BpInfo.AlphaChType == VJ_ALPHA_CH_TYPE__PARTICLE) )
		)
	{
		Lev = 0;
	}
	
	/* */
	if	(
			(b_SmoothingOnPatternChange) ||
			( (block.BpInfo.AlphaChType == VJ_ALPHA_CH_TYPE__INDICATOR) || (block.BpInfo.AlphaChType == VJ_ALPHA_CH_TYPE__PARTICLE) )
		)
	{
		int dt = now_ms - block.BpInfo.t_NewPatternStart;
		
		if(dt < 0) { ERROR_MSG(); ofExit(); return; }
		
		if(500 < dt){
			// no touch.
		}else{
			const double alpha = 0.28;
			Lev = block.BpInfo.LastOutputLevel * (1 - alpha) + Lev * alpha;
		}
	}
	
	/* */
	block.BpInfo.LastOutputLevel = Lev;
	
	/* */
	switch(BpInfo->AlphaChType){
		case VJ_ALPHA_CH_TYPE__MOV_0_12:
			VjDataSet.set__mov_a_0_12(Lev);
			break;
			
		case VJ_ALPHA_CH_TYPE__MOV_1_2:
			VjDataSet.set__mov_a_1_2(Lev);
			break;
			
		case VJ_ALPHA_CH_TYPE__INDICATOR:
			VjDataSet.set__a_indicator(Lev);
			break;
			
		case VJ_ALPHA_CH_TYPE__PARTICLE:
			VjDataSet.set__a_particle(Lev);
			break;
			
		case VJ_ALPHA_CH_TYPE__STROBE:
			VjDataSet.set__a_Strobe(Lev);
			break;
			
		default:
			break;
	}
	
	/********************
	********************/
	if(BpInfo->PlayMode == SELF_PROPULSION){
		/* if finish pattern, go to next. */
		if( FUNC_SP_VJ::MAXPROGRESS_ANIM_KEY <= Progress ){
			PatternIndex_next(block.Bp_Pattern[BpInfo->Bp_Pattern_index], BpInfo->Pattern_index);
			
			BpInfo->SelfPropulsion.LastBeat_ms = now_ms;
		}
	}
	
	fprintf_Log(fp_Alpha_fft, "}, ");
}

/******************************
******************************/
int VJ::CalProgress(int Beat_interval, int LastBeat_ms, double Speed)
{
	if( LastBeat_ms == -1 ){ // SOUND_TO_BEATIN -> 1st Beat in STATE_BEAT_IN
		ERROR_MSG(); ofExit(); return;
		
	}else if(Beat_interval == 0){
		ERROR_MSG(); ofExit(); return;
		
	}else if(now_ms <= LastBeat_ms){
		return 0;
		
	}else if( Beat_interval <= (int)((now_ms - LastBeat_ms) * Speed) ){
		return FUNC_SP_VJ::MAXPROGRESS_ANIM_KEY;
		
	}else{
		return (int)( (now_ms - LastBeat_ms) * Speed * FUNC_SP_VJ::MAXPROGRESS_ANIM_KEY / Beat_interval );
	}
}

/******************************
******************************/
void VJ::PatternIndex_next(const BLOCK_PATTERN& BlockPattern, int& Pattern_index)
{
	Pattern_index++;
	
	if(BlockPattern.pShortPattern[Pattern_index] == NULL){
		Pattern_index = 0;
	}
}

/******************************
******************************/
double VJ::CalLev_from_ShortPattern(PFUNC_VJ_SHORTPATTERN pFunc_sp, int Progress, double phase_deg)
{
	/********************
	********************/
	if(Progress < 0)	{ ERROR_MSG(); ofExit(); return; }
	
	return pFunc_sp(Progress, phase_deg);
}

/******************************
******************************/
void VJ::draw(double Vol_SoundSync)
{
	/********************
	********************/
	fprintf_Log(fp_Alpha_fft, "==========\n");
	fprintf_Vj_Alpha_fft(fp_Alpha_fft, "<time_ms> %d\n", now_ms);
	
	fprintf_Vj_Alpha_fft(fp_Alpha_fft, "%f\n", VjDataSet.get__mov_a());
	fprintf_Vj_Alpha_fft(fp_Alpha_fft, "%d\n", VjDataSet.get__b_mov_Effect_On());
	fprintf_Vj_Alpha_fft(fp_Alpha_fft, "%f\n", VjDataSet.get__mov_a_0_12());
	fprintf_Vj_Alpha_fft(fp_Alpha_fft, "%d\n", VjDataSet.get__b_mov0_Effect_On());
	fprintf_Vj_Alpha_fft(fp_Alpha_fft, "%f\n", VjDataSet.get__mov_a_1_2());
	fprintf_Vj_Alpha_fft(fp_Alpha_fft, "%f\n", VjDataSet.get__a_indicator());
	fprintf_Vj_Alpha_fft(fp_Alpha_fft, "%f\n", VjDataSet.get__a_particle());
	fprintf_Vj_Alpha_fft(fp_Alpha_fft, "%d\n", VjDataSet.get__b_GeneratedImage_on());
	fprintf_Vj_Alpha_fft(fp_Alpha_fft, "%d\n", VjDataSet.get__b_text_on());
	fprintf_Vj_Alpha_fft(fp_Alpha_fft, "%f\n", VjDataSet.get__a_Strobe());
	
	fprintf_Log(fp_Alpha_fft, "==========\n");

	/********************
	********************/
	fprintf_Log(fp_test, "%d,", now_ms);
	fprintf_Log(fp_test, "%f,", VjDataSet.get__mov_a());
	fprintf_Log(fp_test, "%d,", VjDataSet.get__b_mov_Effect_On());
	fprintf_Log(fp_test, "%f,", VjDataSet.get__mov_a_0_12());
	fprintf_Log(fp_test, "%d,", VjDataSet.get__b_mov0_Effect_On());
	fprintf_Log(fp_test, "%f,", VjDataSet.get__mov_a_1_2());
	fprintf_Log(fp_test, "%f,", VjDataSet.get__a_indicator());
	fprintf_Log(fp_test, "%f,", VjDataSet.get__a_particle());
	fprintf_Log(fp_test, "%d,", VjDataSet.get__b_GeneratedImage_on());
	fprintf_Log(fp_test, "%d,", VjDataSet.get__b_text_on());
	fprintf_Log(fp_test, "%f\n", VjDataSet.get__a_Strobe());
	
	/********************
	********************/
	string message = "";
	message +=	ofToString(VjDataSet.get__mov_a())					+ "," + 
				ofToString(VjDataSet.get__b_mov_Effect_On())		+ "," + 
				ofToString(VjDataSet.get__mov_a_0_12())				+ "," + 
				ofToString(VjDataSet.get__b_mov0_Effect_On())		+ "," + 
				ofToString(VjDataSet.get__mov_a_1_2())				+ "," + 
				ofToString(VjDataSet.get__a_indicator())			+ "," + 
				ofToString(VjDataSet.get__a_particle())				+ "," + 
				ofToString(VjDataSet.get__b_GeneratedImage_on())	+ "," + 
				ofToString(VjDataSet.get__b_text_on())				+ "," + 
				ofToString(VjDataSet.get__a_Strobe())				+ "|";
				
	const int N_SPECTRUM = 256;
	for(int i = 0; i < N_SPECTRUM; i++){
		if(i == 1)	message += ofToString(Vol_SoundSync) + ",";
		else		message += ofToString(0) + ",";
	}
	
	if(b_Demo && b_VjExist){
		/********************
		送り先のIPが不在だと、Errorとなり、関数の向こう側でError message表示し続けるので。
		********************/
		if(udpConnection.Send(message.c_str(),message.length()) == -1){
			ERROR_MSG();
			b_VjExist = false;
		}
	}
}
	
/******************************
******************************/
bool VJ::Is_PeriodOfBlockGroup(BLOCK& Block)
{
	if(Block.Bp_Pattern == NULL)	return true;
	else							return false;
}


/******************************
******************************/
void VJ::Dice_StartPatternId(BP_INFO *BpInfo, int StartPatternId_Candidate)
{
	BpInfo->Pattern_index = rand() % (StartPatternId_Candidate + 1);
}

/******************************
******************************/
int VJ::get_num_PatternTypes_in_Bp(const BLOCK_PATTERN *Bp_Pattern)
{
	int num;
	for( num = 0; strcmp(Bp_Pattern[num].name, "BP_END") != 0; num++ ){
	}
	
	return num;
}

/************************************************************************************************************************/
} // namespace SPACE_VJ{
	
	
