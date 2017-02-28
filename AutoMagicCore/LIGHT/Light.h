#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxNetwork.h"

#include "../am_common.h"
#include "L_common.h"
#include "../StopWatch.h"


/************************************************************************************************************************/
namespace SPACE_LIGHT{


/************************************************************
************************************************************/

struct BLOCK;
struct BLOCK_PATTERN;
struct BLOCK_GROUP;
struct PHYSICAL_CH_SET;
struct BP_INFO;
struct PHYSICAL_LED_COLOR_CH;

/**************************************************
**************************************************/
class LIGHT{
private:
	/****************************************
	****************************************/
	enum BLACKOUT{
		BLACKOUT__NONE,
		BLACKOUT__MOVING_ONLY,
		BLACKOUT__BLACK,
		
		NUM_BLACKOUT_TYPES,
	};
	enum{
		TIMEOUT_MOVING_ONLY	= 20000, // 間が持つので.
		TIMEOUT_BLACK		= 10000,
	};
	
	BLACKOUT Blackout;
	
	/****************************************
	****************************************/
	FILE *fp_script;
	
	int BlockGrouping_id_InTangible;
	int BlockGrouping_id_Tangible;
	
	STOP_WATCH StopWatch_TangiblePatternChange;
	STOP_WATCH StopWatch_BlackoutClear;
	
	bool b_echo;
	int EchoStep;
	double EchoDownRatio;
	
	
	bool b_1st;
	
	/********************
	********************/
	int t_Fadein_Tangible;
	int t_Fadein_InTangible;
	
	/********************
	********************/
	bool b_LightOperatorExist;
	
	OSC_TARGET OscDmx;
	
	enum{ UDP_SEND_PORT = 12347, };
	ofxUDPManager udpConnection;

	
	
	/****************************************
	****************************************/
	/********************
	singleton
	********************/
	LIGHT();
	~LIGHT();
	LIGHT(const LIGHT&); // Copy constructor. no define.
	LIGHT& operator=(const LIGHT&); // コピー代入演算子. no define.
	
	/********************
	********************/
	bool IsChangeTangible(STATE State);
	bool Is_PeriodOfBlockGroup(BLOCK& Block);
	void init_StateChart();
	bool Select_Playmode_BlockPattern_ColorChange(STATE State);
	void SelectPlayMode_Lum(STATE State, BLOCK_GROUP *BlockGrouping, int BlockGrouping_id);
	int get_Num_LogicalChs_inThisBlock(BLOCK& Block);
	int Dice_BlockGrouping(enum STATE State, int TangibleOrNot);
	bool Dice_ColorChange(enum STATE State);
	void ColorChange_inTheTheme_AllBlock(BLOCK_GROUP *BlockGrouping, int BlockGrouping_id);
	void ColorFlash_inTheTheme_AllBlock(BLOCK_GROUP *BlockGrouping, int BlockGrouping_id);
	int Dice_LedColor_in_Palette(const struct COLOR_AND_WEIGHT *LedColor);
	int get_Num_PhysicalChs_inThisLogicalCh(PHYSICAL_CH_SET& LogicalCh);
	void SelectPlayMode_PanTilt(STATE State, BLOCK_GROUP *BlockGrouping, int BlockGrouping_id);	
	void SelectBlockPattern(enum STATE State, BLOCK_GROUP *BlockGrouping, int BlockGrouping_id);
	int get_num_PatternTypes_in_Bp(const BLOCK_PATTERN *Bp_Pattern);
	void Set_LedTrackID_by_SymmetricType(BP_INFO *BpInfo, SYMMETRIC_TYPE SymmetricType, int NumLogicalChs);
	void Dice_LedTrackOrder_Random(BP_INFO *BpInfo, int NumLogicalChs);
	void Dice_LedTrackOrder_Line(BP_INFO *BpInfo, int NumLogicalChs);
	void Dice_StartPatternId(BP_INFO *BpInfo, int StartPatternId_Candidate);
	void set_AllBlock_AllBpInfo_Luminance_SelfPropulsion_bFin1Loop_false();
	int CalLev_from_ShortPattern(PFUNC_SHORTPATTERN pFunc_sp, int Progress);
	void update_OneBlock(BLOCK& block, DEVICE_OUTPUT_CH* DeviceOutputCh);
	void MakeColorFromPalette(PHYSICAL_LED_COLOR_CH *Led);
	void CalColor(struct COLOR LedColor, int Lev, struct COLOR *outColor);
	void PatternIndex_next(const BLOCK_PATTERN& BlockPattern, int& Pattern_index);
	int Select_BlackoutPattern(const BLOCK& Block, const CH_TO_SET DeviceChType);
	int FixTreatType_by_Blackoutmode_SelectBlockPattern(STATE State, bool b_PanTilt, int ChToSet);
	
	void Clear_Blackout();
	void Dice_Blackout();
	
	double Cal_FadeinRatio(int& t_Fadein);
	
public:
	/****************************************
	****************************************/
	/********************
	********************/
	static LIGHT* getInstance(){
		static LIGHT inst;
		return &inst;
	}
	
	/********************
	********************/
	void test();
	
	void setup();
	void update();
	void draw();
	void exit();

	void close_all_LogFile();
	void StateChart_Transition(TRANSITION Transition, bool& Is_Flash);
	
	void Beat_PatternIndex_next_AllBlock();
	
	int Is_StayTooLong_PatternChange(enum STATE State);
	int Is_SelfPropultion_Finish();
	int CalProgress(int Beat_interval, int LastBeat_ms, double Speed);
	void SetColorTheme(enum COLORPATTERNS ColorPattern, int OperationType);
	
	void fprint(const char message[]);
	
	void Reset_StopWatch_TangiblePatternChange();
};


/************************************************************************************************************************/
} // namespace SPACE_LIGHT{


