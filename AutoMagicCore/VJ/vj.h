/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxNetwork.h"

#include "../am_common.h"
#include "../StopWatch.h"

#include "vj_common.h"

/************************************************************************************************************************/
namespace SPACE_VJ{



/************************************************************
************************************************************/
class VJ_DATASET{
private:
	double	mov_a;
	bool	b_mov_Effect_On;
	double	mov_a_0_12;
	bool	b_mov0_Effect_On;
	double	mov_a_1_2;
	double	a_indicator;
	double	a_particle;
	bool	b_GeneratedImage_on;
	bool	b_text_on;
	double	a_Strobe;
	
	
	
public:
	VJ_DATASET();
	~VJ_DATASET();
	
	void set__mov_a(double val)	{ mov_a = val; }
	double get__mov_a()			{ return mov_a; }
	
	void set__mov_a_0_12(double val)	{ mov_a_0_12 = val; }
	double get__mov_a_0_12()			{ return mov_a_0_12; }
	
	void set__mov_a_1_2(double val)	{ mov_a_1_2 = val; }
	double get__mov_a_1_2()			{ return mov_a_1_2; }
	
	void set__a_indicator(double val)	{ a_indicator = val; }
	double get__a_indicator()			{ return a_indicator; }
	
	void set__a_particle(double val)	{ a_particle = val; }
	double get__a_particle()			{ return a_particle; }

	void set__a_Strobe(double val)		{ a_Strobe = val; }
	double get__a_Strobe()				{ return a_Strobe; }
	
	/********************
	********************/
	void set__b_mov_Effect_On(bool val)	{ b_mov_Effect_On = val; }
	bool get__b_mov_Effect_On()			{ return b_mov_Effect_On; }

	void set__b_mov0_Effect_On(bool val)	{ b_mov0_Effect_On = val; }
	bool get__b_mov0_Effect_On()			{ return b_mov0_Effect_On; }
	
	void set__b_GeneratedImage_on(bool val)	{ b_GeneratedImage_on = val; }
	bool get__b_GeneratedImage_on()			{ return b_GeneratedImage_on; }
	
	void set__b_text_on(bool val)	{ b_text_on = val; }
	bool get__b_text_on()			{ return b_text_on; }
};


/**************************************************
**************************************************/
struct BLOCK;
struct BLOCK_PATTERN;
struct BP_INFO;

class VJ{
private:
	/****************************************
	****************************************/
	typedef void(VJ_DATASET::*pFunc_Set_bool)(bool val);
	
	/****************************************
	****************************************/
	FILE *fp_ColorTheme;
	FILE *fp_ContentsChangeTiming;
	FILE *fp_BpmInfo;
	
	FILE *fp_test;
	
	STOP_WATCH StopWatch_AddGenerativeImage;
	STOP_WATCH StopWatch_AddText;
	STOP_WATCH StopWatch_AddEffectToMov;
	STOP_WATCH StopWatch_AddEffectToMov_0;
	
	STOP_WATCH StopWatch_ContentsChangeTiming;
	STOP_WATCH StopWatch_EnterSOUND;
	bool b_ContentsChange;
	
	

	FILE *fp_Alpha_fft;
	VJ_DATASET VjDataSet;
	
	
	const int t_Transition_mov_a;
	int t__From_mov_a;
	
	bool b_SmoothingOnPatternChange;
	
	/********************
	********************/
	bool b_VjExist;
	
	OSC_TARGET OscVj;
	OSC_TARGET OscCg;
	
	enum { UDP_SEND_PORT = 12350, };
	ofxUDPManager udpConnection;
	

	/****************************************
	****************************************/
	/********************
	singleton
	********************/
	VJ();
	~VJ();
	VJ(const VJ&); // Copy constructor. no define.
	VJ& operator=(const VJ&); // コピー代入演算子. no define.
	
	/********************
	********************/
	void init_StateChart();
	void Process_in_Transition(STATE State);
	void SelectPlayMode(STATE State);
	// void Dice_ifAddEffect(const int (*W_Table)[NUM_BOOSTMODE][NUM_ADD_EFFECT], STATE State, BOOSTMODE BoostMode, pFunc_Set_bool pFunc);
	void Dice_ifAddEffect(const int (*W_Table)[NUM_BOOSTMODE][NUM_ADD_EFFECT], STATE State, BOOSTMODE BoostMode, pFunc_Set_bool pFunc, bool b_Current, STOP_WATCH& StopWatch);
	void SelectBlockPattern(enum STATE State, BOOSTMODE BoostMode);
	bool Is_PeriodOfBlockGroup(BLOCK& Block);
	void update_OneBlock(BLOCK& block);
	double CalLev_from_ShortPattern(PFUNC_VJ_SHORTPATTERN pFunc_sp, int Progress, double phase_deg);
	int CalProgress(int Beat_interval, int LastBeat_ms, double Speed);
	void PatternIndex_next(const BLOCK_PATTERN& BlockPattern, int& Pattern_index);
	void Dice_StartPatternId(BP_INFO *BpInfo, int StartPatternId_Candidate);
	int get_num_PatternTypes_in_Bp(const BLOCK_PATTERN *Bp_Pattern);
	
public:
	/****************************************
	****************************************/
	/********************
	********************/
	static VJ* getInstance(){
		static VJ inst;
		return &inst;
	}
	
	/********************
	********************/
	void test();
	
	void close_all_LogFile();
	void SetColorTheme(int ThemeId);
	void ContentsChange();
	void SetBpmInfo(int self_Beat_interval);
	
	void setup();
	void update();
	void draw(double Vol_SoundSync);
	void exit();
	
	void StateChart_Transition(TRANSITION Transition);
	void Beat_PatternIndex_next_AllBlock();
};


/************************************************************************************************************************/
} // namespace SPACE_VJ{



