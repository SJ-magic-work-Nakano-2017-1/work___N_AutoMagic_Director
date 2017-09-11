/************************************************************
namespaceごとのrole
	基本的には、am_coreで音楽解析し、これに基づいて各namespaceがDesignPatternを決めていく。
	一部相互作用のある所もあるが。。。
	
	global
		am_common
		
	am_core
		Role
			music analysis
			
		chage parameters
			Beat_interval
			self_Beat_interval
			LastBeat_ms
			
		files
			am_core
			DeviceCh.h
			HF_Analyze
			Perlin
			StopWatch
		
	SPACE_LIGHT
		files
			Light
			
			BlockPattern
			ShortPattern
			BlockGrouping.h
			Weight.h
			PhysicalLed.h
			L_common.h
		
	SPACE_VJ
		files
			vj
			
			BlockPattern
			ShortPattern
			BlockGrouping.h
			Weight.h
			vj_common.h

************************************************************/

/************************************************************
size : checked on Mac
	char		8
	short		16
	int			32
	long		64
	long long	64
************************************************************/
#pragma once


/************************************************************
************************************************************/
#include "ofxGui.h"

#include "../Graph.h"
#include "am_common.h"

/************************************************************
class
************************************************************/

enum COLORPATTERNS;

/**************************************************
**************************************************/
class AUTOMAGIC_CORE : public ofThread{
private:
	/****************************************
	enum
	****************************************/
	enum{
		DATA_VOL,
		DATA_VOL_LOW,
		DATA_VOL_HIGH,
		DATA_VOL_SOUNDSYNC,
	
		NUM_TYPE_OF_VOL_DATA,
	};
	
	enum STATE_SOUND_ONOFF{
		STATE_SOUND_OFF,
		STATE_SOUND_ON,
	};
	
	/****************************************
	param
	****************************************/
	/********************
	********************/
	ofxPanel gui;
	
	ofxToggle b_Enable_SoundOnOff_Vj;
	ofxToggle b_Enable_SoundOnOff_Light;
	
	/********************
	********************/
	FILE *fp_debug_state;
	
	const long long Boost_AGC;
	const long long ReverseBoostAGC_for_Log;
	const double ReverseBoostAGC_fft;
	
	long long VolLevel[NUM_TYPE_OF_VOL_DATA]; // is always boosted with Boost_AGC.
	long long Vol_max_assumed[NUM_TYPE_OF_VOL_DATA];
	long long Vol_min_assumed[NUM_TYPE_OF_VOL_DATA];
	
	const long MIN_BEAT_TIME_MS;
	
	short b_ColorAutoChange;
	short b_StopColorAutoChange;
	
	int c_INT;
	
	STATE__BEAT_DETECT State_IsLock;
	
	STATE_SOUND_ONOFF State_SoundOnOff;
	
	/********************
	********************/
	int debug_b_BeatDetect = 0;
	
	/****************************************
	****************************************/
	/********************
	singleton
	********************/
	AUTOMAGIC_CORE();
	~AUTOMAGIC_CORE();
	AUTOMAGIC_CORE(const AUTOMAGIC_CORE&); // Copy constructor. no define.
	AUTOMAGIC_CORE& operator=(const AUTOMAGIC_CORE&); // コピー代入演算子. no define.
	
	/********************
	********************/
	void setBootmode(int mode);
	void update(GRAPH& Graph, double Vol_Thtough, double Vol_Lpf, double Vol_Bpf, double Vol_SoundSync);
	void draw();
	
	void ParamErrorCheck();
	void close_all_LogFile();
	void On_ColorChange(enum COLORPATTERNS ColorPattern);
	void SetColorTheme(enum COLORPATTERNS ColorPattern, int OperationType);
	void MovingAve_vol(double vol, double vol_Low, double vol_High, double vol_SoundSync);
	void Set_vol_max_assumed();
	int MusicAnalysis(GRAPH& Graph);
	void fix_NumPatternChangeBeats(enum TRANSITION Transition, int Is_ColorChangeTo_Flash);
	int PlausibleOfArray(int* array, int num);
	void ColorPalette_AutoChange(int OperationType);
	void init_StateChart();
	bool IsVolDown_Enough_fromPeak(long long VolLowNow, long long VolLow_Peak);
	void StateChart_Transition(enum TRANSITION Transition, int *c_Beats_in_Flywheel, int *t_NoSound_NoBeat);
	int Is_Flywheel_Lock(long long& VolLow_Peak);
	int Is_Flywheel_UnLock(long long& VolLow_Peak, int *Counter_Beats);
	int Is_VolLpf_HighEnough();
	void StateChart_Sound_OnOff(double Vol_Raw);
	
	static int compare_int(const void *a, const void *b);
	
	
public:
	/****************************************
	****************************************/
	/********************
	********************/
	static AUTOMAGIC_CORE* getInstance(){
		static AUTOMAGIC_CORE inst;
		return &inst;
	}
	
	void exit();
	void setup(int mode);
	void test();
	void INT(GRAPH& Graph, double now_sec, double Vol_Raw, double Vol_Thtough, double Vol_Lpf, double Vol_Bpf, double Vol_SoundSync);
	
	void set__b_Fileout(bool flag);
	
	void draw_gui();
};

