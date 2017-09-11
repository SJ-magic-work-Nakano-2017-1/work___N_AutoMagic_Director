/************************************************************
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


#include "L_common.h"

#include "L_ShortPattern.h"
#include "L_BlockPattern.h"
#include "../DeviceCh.h"
#include "L_PhysicalLed.h"
#include "L_BlockGrouping.h"
#include "L_Weight.h"

#include "Light.h"



/************************************************************************************************************************/
namespace SPACE_LIGHT{


/************************************************************
************************************************************/
DEVICE_OUTPUT_CH DeviceOutputCh[NUM_PHYSICAL_LEDS];
COLOR LedEcho[NUM_PHYSICAL_LEDS];
ANGLE Last_LedAngle[NUM_PHYSICAL_LEDS/2]; // Pan/Tiltを動かさない時、前Frameの位置に保持するための仕組み.

/************************************************************
************************************************************/

/******************************
******************************/
LIGHT::LIGHT()
: BlockGrouping_id_InTangible(0)
, BlockGrouping_id_Tangible(0)
, StopWatch_TangiblePatternChange(6500)
, StopWatch_BlackoutClear(10000)
, b_echo(false)
, EchoStep(0)
, EchoDownRatio(0)
, b_1st(true)
, Blackout(BLACKOUT__NONE)
, t_Fadein_Tangible(-1)
, t_Fadein_InTangible(-1)
, fp_script(NULL)

, OscDmx("127.0.0.1", 12346, 12345)
, b_LightOperatorExist(true)
{
	/********************
	********************/
	fp_script = fopen("../../../StoryBoard.txt", "w");
	if(fp_script == NULL)		{ ERROR_MSG(); std::exit(1); }
	
	char buf[BUF_SIZE];
	
	sprintf(buf, "<NumLeds> %d\n\n", NUM_PHYSICAL_LEDS/2);
	fprintf_Log(fp_script, "%s", buf);
}

/******************************
******************************/
LIGHT::~LIGHT()
{
	close_all_LogFile();
}

/******************************
******************************/
void LIGHT::exit()
{
	ofxOscMessage m;
	m.setAddress("/Quit");
	m.addIntArg(1);
	
	OscDmx.OscSend.sendMessage(m);
}

/******************************
******************************/
void LIGHT::fprint(const char message[])
{
	fprintf_Log(fp_script, "%s", message);
}

/******************************
******************************/
void LIGHT::Reset_StopWatch_TangiblePatternChange()
{
	StopWatch_TangiblePatternChange.Reset();
}

/******************************
******************************/
void LIGHT::close_all_LogFile()
{
	if(fp_script) { fclose(fp_script); fp_script = NULL; }
}

/******************************
******************************/
int LIGHT::Dice_BlockGrouping(enum STATE State, int TangibleOrNot)
{
	if(TangibleOrNot == INTANGIBLE){
		/********************
		********************/
		int Weight[NUM_GROUPTYPES_INTANGIBLE];
		
		for(int i = 0; i < NUM_GROUPTYPES_INTANGIBLE; i++){
			Weight[i] = W_BlockGrouping_InTangible[State][get_BoostMode()][i];
		}
		
		int index = Dice_index(Weight, NUM_GROUPTYPES_INTANGIBLE);
		if(index == -1) { ERROR_MSG(); ofExit(); return; }
		
		/********************
		********************/
		char buf[BUF_SIZE];
		sprintf(buf, ";BlockGrouping_name = %s\n", BlockGrouping_InTangible[index].BlockName);
		fprintf_Log(fp_script, "%s", buf);

		return index;
		
	}else{
		/********************
		********************/
		int Weight[NUM_GROUPTYPES_TANGIBLE];
		
		for(int i = 0; i < NUM_GROUPTYPES_TANGIBLE; i++){
			Weight[i] = W_BlockGrouping_Tangible[State][get_BoostMode()][i];
		}
		
		int index = Dice_index(Weight, NUM_GROUPTYPES_TANGIBLE);
		if(index == -1) { ERROR_MSG(); ofExit(); return; }
		
		/********************
		********************/
		char buf[BUF_SIZE];
		sprintf(buf, ";BlockGrouping_name = %s\n", BlockGrouping_Tangible[index].BlockName);
		fprintf_Log(fp_script, "%s", buf);

		return index;
	}
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
void LIGHT::SetColorTheme(enum COLORPATTERNS ColorPattern, int OperationType)
{
	char buf[BUF_SIZE];
	sprintf(buf, ";Set Color set = %d\n", (int)ColorPattern);
	fprintf_Log(fp_script, "%s", buf);
	
	system_ColorTheme_palette = &Palette[ColorPattern];
	
	if(OperationType == 0){
		/********************
		for FLASH.
		********************/
		for(int i = 0; i < NUM_PHYSICAL_LEDS; i++){
			if(PhysicalLedColorCh[i].IsDynamicColor){
				
				// system does not change "PhysicalLedColorCh[i].LedColor".
				// So after FLASH pattern, system changed the color from FLASH color to the new palette color.
				
				PhysicalLedColorCh[i].LedFrom = PhysicalLedColorCh[i].LedColor; // FLASH color is in "PhysicalLedColorCh[i].LedColor".
				PhysicalLedColorCh[i].LedTo = system_ColorTheme_palette->LedBase[0].LedColor; // Color of new palette.
			}
		}
		
	}else if(OperationType == 1){
		/********************
		Quick color change.
		for example, User changed the color theme by the hardware button.
		********************/
		for(int i = 0; i < NUM_PHYSICAL_LEDS; i++){
			if(PhysicalLedColorCh[i].IsDynamicColor){
				
				PhysicalLedColorCh[i].LedColor = system_ColorTheme_palette->LedBase[0].LedColor;
				PhysicalLedColorCh[i].LedFrom = PhysicalLedColorCh[i].LedColor;
				PhysicalLedColorCh[i].LedTo = PhysicalLedColorCh[i].LedColor;
				PhysicalLedColorCh[i].f_ColorChange = COLOR_KEEP;
			}
		}
		
	}else if(OperationType == 2){
		/********************
		smooth color change.
		********************/
		for(int i = 0; i < NUM_PHYSICAL_LEDS; i++){
			if(PhysicalLedColorCh[i].IsDynamicColor){
				
				PhysicalLedColorCh[i].LedFrom = PhysicalLedColorCh[i].LedTo;
				PhysicalLedColorCh[i].LedTo = system_ColorTheme_palette->LedBase[0].LedColor;
				PhysicalLedColorCh[i].t_ColorChangeStart = now_ms;
				PhysicalLedColorCh[i].f_ColorChange = COLOR_CHANGE;
			}
		}
	}
}

/******************************
******************************/
bool LIGHT::IsChangeTangible(STATE State)
{
	return StopWatch_TangiblePatternChange.IsTimePassed(now_ms);
}

/******************************
******************************/
bool LIGHT::Is_PeriodOfBlockGroup(BLOCK& Block)
{
	if(Block.Bp_Pattern == NULL)	return true;
	else							return false;
}

/******************************
******************************/
void LIGHT::init_StateChart()
{
	/********************
	********************/
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock]); LedBlock++){
		BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].Set_AllBpInfo_SelfPropulsion_LastBeatms(now_ms);
	}
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock]); LedBlock++){
		BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].Set_AllBpInfo_SelfPropulsion_LastBeatms(now_ms);
	}
	
	/********************
	********************/
	StopWatch_TangiblePatternChange.Reset();
	
	/********************
	********************/
	t_Fadein_Tangible = -1;
	t_Fadein_InTangible = -1;
	
	Blackout = BLACKOUT__NONE;
}

/******************************
******************************/
int LIGHT::get_Num_LogicalChs_inThisBlock(BLOCK& Block)
{
	int num;
	for(num = 0; Block.LogicalCh[num].PhysicalCh[0] != -1; num++){
	}
	
	return num;
}

/******************************
******************************/
void LIGHT::SelectPlayMode_Lum(STATE State, BLOCK_GROUP *BlockGrouping, int BlockGrouping_id)
{
	/********************
	********************/
	char buf[BUF_SIZE];
	sprintf(buf, ";PlaymodeLum = (");
	fprintf_Log(fp_script, "%s", buf);
	
	/********************
	********************/
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[LedBlock]); LedBlock++){
		if(0 < get_Num_LogicalChs_inThisBlock(BlockGrouping[BlockGrouping_id].Block[LedBlock])){
			if(DB_isDoubtSetInThisState()){
				BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Luminance.PlayMode = SELF_PROPULSION;
				
			}else{
				int Weight[NUM_PLAYMODES];
				for(int i = 0; i < NUM_PLAYMODES; i++){
					Weight[i] = BlockGrouping[BlockGrouping_id].Block[LedBlock].Weight_PlayMode_Lum[State][get_BoostMode()][i];
				}
				
				int index = Dice_index(Weight, NUM_PLAYMODES);
				if(index == -1) { ERROR_MSG(); ofExit(); return; }
				
				BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Luminance.PlayMode = (enum PLAYMODE)index;
			}
			
			sprintf(buf, "%d, ", (int)BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Luminance.PlayMode);
			
		}else{
			sprintf(buf, "-, ");
		}
		
		fprintf_Log(fp_script, "%s", buf);
	}
	
	sprintf(buf, ")\n");
	fprintf_Log(fp_script, "%s", buf);
	
	fprintf_Log(fp_script, ")\n");
}

/******************************
return
	Is_Flash
******************************/
bool LIGHT::Dice_ColorChange(enum STATE State)
{
	/********************
	********************/
	for(int i = 0; i < NUM_PHYSICAL_LEDS; i++){
		if( PhysicalLedColorCh[i].IsDynamicColor && (PhysicalLedColorCh[i].f_ColorChange == COLOR_CHANGE) ) return false;
	}
	
	/********************
	********************/
	int Is_pre_is_Flash = 0;
	for(int i = 0; i < NUM_PHYSICAL_LEDS; i++){
		if( PhysicalLedColorCh[i].IsDynamicColor && (PhysicalLedColorCh[i].f_ColorChange == COLOR_FLASH) ){
			/********************
			When system entered FLASH mode,
			system has set "LedFrom" and "LedTo" in the function of SetColorTheme().
			So just need to set COLOR_CHANGE.
			Then "LedColor" will be changed smoothly.
			********************/
			Is_pre_is_Flash++;
			PhysicalLedColorCh[i].f_ColorChange = COLOR_CHANGE;
			PhysicalLedColorCh[i].t_ColorChangeStart = now_ms;
		}
	}
	if(0 < Is_pre_is_Flash) return false;
	
	/************************************************************************************************************************/
	
	/********************
	Copy from original.
	********************/
	bool Is_Flash = false;
	int index;
	
	int Weight[NUM_COLOR_CHANGE_KEEP];
	for(int i = 0; i < NUM_COLOR_CHANGE_KEEP; i++){
		Weight[i] = W_ColorChange[State][get_BoostMode()][i];
	}
	index = Dice_index(Weight, NUM_COLOR_CHANGE_KEEP);
	if(index == -1) { ERROR_MSG(); ofExit(); return; }
	else if(index == COLOR_FLASH) {Is_Flash = true;}
	

	/********************
	One color for One Block.
	********************/
	if((enum COLOR_CHANGE_KEEP)index == COLOR_KEEP){
		fprintf_Log(fp_script, ";ColorKeep\n");
		
		for(int i = 0; i < NUM_PHYSICAL_LEDS; i++){
			if(PhysicalLedColorCh[i].IsDynamicColor){
				PhysicalLedColorCh[i].LedColor = PhysicalLedColorCh[i].LedTo;
				PhysicalLedColorCh[i].f_ColorChange = COLOR_KEEP;
			}
		}
		
	}else if((enum COLOR_CHANGE_KEEP)index == COLOR_CHANGE){
		fprintf_Log(fp_script, ";ColorChange start\n");
		fprintf_Log(fp_script, ";Target color of Block 0, 1, ... = \n");
		
		ColorChange_inTheTheme_AllBlock(BlockGrouping_InTangible, BlockGrouping_id_InTangible);
		ColorChange_inTheTheme_AllBlock(BlockGrouping_Tangible, BlockGrouping_id_Tangible);
		
		fprintf_Log(fp_script, "\n");
		
	}else if((enum COLOR_CHANGE_KEEP)index == COLOR_FLASH){
		fprintf_Log(fp_script, ";ColorChange Flash\n");
		
		ColorFlash_inTheTheme_AllBlock(BlockGrouping_InTangible, BlockGrouping_id_InTangible);
		ColorFlash_inTheTheme_AllBlock(BlockGrouping_Tangible, BlockGrouping_id_Tangible);
		
		// set the Palette.
		// Then after FLASH, next color palette will appear.
		// if(b_ColorAutoChange)	ColorPalette_AutoChange(0);
	}

	return Is_Flash;
}

/******************************
******************************/
int LIGHT::Dice_LedColor_in_Palette(const struct COLOR_AND_WEIGHT *LedColor)
{
	/***********************
	cal sum of Weight
	***********************/
	int TotalWeight = 0;
	for(int i = 0; LedColor[i].Weight != -1; i++){
		TotalWeight += LedColor[i].Weight;
	}
	
	if(TotalWeight == 0) { ERROR_MSG(); ofExit(); return; }
	
	
	/***********************
	random number
	***********************/
	int RandomNumber = (rand() % TotalWeight) + 1;
	
	/***********************
	define
	***********************/
	int index;
	for(TotalWeight = 0, index = 0; LedColor[index].Weight != -1; index++){
		TotalWeight += LedColor[index].Weight;
		if(RandomNumber <= TotalWeight) break;
	}
	
	return index;
}

/******************************
******************************/
int LIGHT::get_Num_PhysicalChs_inThisLogicalCh(PHYSICAL_CH_SET& LogicalCh)
{
	int num;
	for(num = 0; num < LogicalCh.MAX_CHS_IN_1LOGICAL_CH && LogicalCh.PhysicalCh[num] != -1; num++){
	}
	
	if(LogicalCh.MAX_CHS_IN_1LOGICAL_CH <= num)	{ ERROR_MSG(); ofExit(); return; }
	
	return num;
}

/******************************
******************************/
void LIGHT::ColorChange_inTheTheme_AllBlock(BLOCK_GROUP *BlockGrouping, int BlockGrouping_id)
{
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[LedBlock]); LedBlock++){
		
		int index_Base = Dice_LedColor_in_Palette(system_ColorTheme_palette->LedBase);
		
		int NUM_LOGICAL_CHS = get_Num_LogicalChs_inThisBlock(BlockGrouping[BlockGrouping_id].Block[LedBlock]);
		for(int LogicalCh = 0; LogicalCh < NUM_LOGICAL_CHS; LogicalCh++){
			int NUM_PHYSICAL_CHS = get_Num_PhysicalChs_inThisLogicalCh(BlockGrouping[BlockGrouping_id].Block[LedBlock].LogicalCh[LogicalCh]);
			for(int i = 0; i < NUM_PHYSICAL_CHS; i++){
				int id_PhysicalLed = BlockGrouping[BlockGrouping_id].Block[LedBlock].LogicalCh[LogicalCh].PhysicalCh[i];
				if(PhysicalLedColorCh[id_PhysicalLed].IsDynamicColor){
					PhysicalLedColorCh[id_PhysicalLed].LedFrom				= PhysicalLedColorCh[id_PhysicalLed].LedColor;
					PhysicalLedColorCh[id_PhysicalLed].LedTo				= system_ColorTheme_palette->LedBase[index_Base].LedColor;
					PhysicalLedColorCh[id_PhysicalLed].t_ColorChangeStart	= now_ms;
					PhysicalLedColorCh[id_PhysicalLed].f_ColorChange		= COLOR_CHANGE;
				}
			}
		}
		
		// Log
		char buf[BUF_SIZE];
		sprintf(buf, "(%d, %d, %d), ",
					system_ColorTheme_palette->LedBase[index_Base].LedColor.R,
					system_ColorTheme_palette->LedBase[index_Base].LedColor.G,
					system_ColorTheme_palette->LedBase[index_Base].LedColor.B
					);
		fprintf_Log(fp_script, "%s", buf);
	}
}

/******************************
******************************/
void LIGHT::ColorFlash_inTheTheme_AllBlock(BLOCK_GROUP *BlockGrouping, int BlockGrouping_id)
{
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[LedBlock]); LedBlock++){
		int index_Flash	= Dice_LedColor_in_Palette(system_ColorTheme_palette->LedFlash);
		
		int NUM_LOGICAL_CHS = get_Num_LogicalChs_inThisBlock(BlockGrouping[BlockGrouping_id].Block[LedBlock]);
		for(int LogicalCh = 0; LogicalCh < NUM_LOGICAL_CHS; LogicalCh++){
			int NUM_PHYSICAL_CHS = get_Num_PhysicalChs_inThisLogicalCh(BlockGrouping[BlockGrouping_id].Block[LedBlock].LogicalCh[LogicalCh]);
			for(int i = 0; i < NUM_PHYSICAL_CHS; i++){
				int id_PhysicalLed = BlockGrouping[BlockGrouping_id].Block[LedBlock].LogicalCh[LogicalCh].PhysicalCh[i];
				if(PhysicalLedColorCh[id_PhysicalLed].IsDynamicColor){
					PhysicalLedColorCh[id_PhysicalLed].LedTo			= PhysicalLedColorCh[id_PhysicalLed].LedColor; // return to original color after Flashing
					PhysicalLedColorCh[id_PhysicalLed].LedColor			= system_ColorTheme_palette->LedFlash[index_Flash].LedColor;
					PhysicalLedColorCh[id_PhysicalLed].f_ColorChange	= COLOR_FLASH;
					PhysicalLedColorCh[id_PhysicalLed].LedFrom			= PhysicalLedColorCh[id_PhysicalLed].LedColor; // Flash color which was set this time.
				}
			}
		}
	}
}

/******************************
******************************/
void LIGHT::SelectPlayMode_PanTilt(STATE State, BLOCK_GROUP *BlockGrouping, int BlockGrouping_id)
{
	/********************
	********************/
	char buf[BUF_SIZE];
	sprintf(buf, ";PlaymodePanTilt(SameValue) = (");
	fprintf_Log(fp_script, "%s", buf);
	
	/********************
	********************/
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[LedBlock]); LedBlock++){
		if( (0 < get_Num_LogicalChs_inThisBlock(BlockGrouping[BlockGrouping_id].Block[LedBlock])) && (BlockGrouping[BlockGrouping_id].Block[LedBlock].b_PanTilt) ){
			if(DB_isDoubtSetInThisState()){
				BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Pan.PlayMode = SELF_PROPULSION;
				BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Tilt.PlayMode = SELF_PROPULSION;
				
			}else{
				int Weight[NUM_PLAYMODES];
				for(int i = 0; i < NUM_PLAYMODES; i++){
					Weight[i] = BlockGrouping[BlockGrouping_id].Block[LedBlock].Weight_PlayMode_PanTilt[State][get_BoostMode()][i];
				}
				
				int index = Dice_index(Weight, NUM_PLAYMODES);
				if(index == -1) { ERROR_MSG(); ofExit(); return; }
				
				// 現状、PanもTiltもどうせSelfしかないので、同じ値を格納してしまう.
				BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Pan.PlayMode = (enum PLAYMODE)index;
				BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Tilt.PlayMode = (enum PLAYMODE)index;
			}
			
			sprintf(buf, "%d, ", (int)BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Pan.PlayMode);
			fprintf_Log(fp_script, "%s", buf);
		}else{
			fprintf_Log(fp_script, "-, ");
		}
	}
	
	fprintf_Log(fp_script, ")\n\n");
}

/******************************
******************************/
void LIGHT::set_AllBlock_AllBpInfo_Luminance_SelfPropulsion_bFin1Loop_false()
{
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock]); LedBlock++){
		BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Luminance.SelfPropulsion.b_Fin_1Loop = false;
	}
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock]); LedBlock++){
		BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Luminance.SelfPropulsion.b_Fin_1Loop = false;
	}
}

/******************************
******************************/
int LIGHT::get_num_PatternTypes_in_Bp(const BLOCK_PATTERN *Bp_Pattern)
{
	int num;
	for( num = 0; strcmp(Bp_Pattern[num].name, "BP_END") != 0; num++ ){
	}
	
	return num;
}

/******************************
******************************/
void LIGHT::Dice_LedTrackOrder_Line(BP_INFO *BpInfo, int NumLogicalChs)
{
	int RandomNumber = rand() % 2;
	
	if(RandomNumber == 0){
		/* そのまま */
	}else{
		/* Reverse */
		int i;
		for(i = 0; i < NumLogicalChs; i++){
			BpInfo->ChId[i] = NumLogicalChs - i - 1;
		}
	}
}

/******************************
******************************/
void LIGHT::Dice_StartPatternId(BP_INFO *BpInfo, int StartPatternId_Candidate)
{
	BpInfo->Pattern_index = rand() % (StartPatternId_Candidate + 1);
}

/******************************
description
	fisher yates法
	偏りをなくすため、回を追うごとに乱数範囲を狭めていくのがコツ
	http://www.fumiononaka.com/TechNotes/Flash/FN0212003.html
******************************/
void LIGHT::Dice_LedTrackOrder_Random(BP_INFO *BpInfo, int NumLogicalChs)
{
	int i= NumLogicalChs;
	
	while(i--){
		int j = rand() % (i + 1);
		
		int temp = BpInfo->ChId[i];
		BpInfo->ChId[i] = BpInfo->ChId[j];
		BpInfo->ChId[j] = temp;
	}
}

/******************************
******************************/
void LIGHT::Set_LedTrackID_by_SymmetricType(BP_INFO *BpInfo, SYMMETRIC_TYPE SymmetricType, int NumLogicalChs)
{
	/********************
	まず順序通り並べる.
	********************/
	for(int i = 0; i < NumLogicalChs; i++){
		BpInfo->ChId[i] = i;
	}
	
	/********************
	********************/
	if(SymmetricType == SYMMETRY_RIGID){
		/* nothing. */
	}else if( SymmetricType == SYMMETRY_RANDOM ){
		Dice_LedTrackOrder_Random(BpInfo, NumLogicalChs);
		
	}else if(SymmetricType == SYMMETRY_LINE){
		Dice_LedTrackOrder_Line(BpInfo, NumLogicalChs);
		
	}else{
		ERROR_MSG(); ofExit(); return;
	}
}

/******************************
******************************/
void LIGHT::test()
{
}

/******************************
******************************/
int LIGHT::Select_BlackoutPattern(const BLOCK& Block, const CH_TO_SET DeviceChType)
{
	char BpName[BUF_SIZE];
	
	int NumCandidates = get_num_PatternTypes_in_Bp(Block.Bp_Pattern);
	
	if(DeviceChType == CH_PAN){
		if(Block.Bp_Pattern == Bp_1)		{ ERROR_MSG(); ofExit(); return; }
		else if(Block.Bp_Pattern == Bp_2)	{ ERROR_MSG(); ofExit(); return; }
		else if(Block.Bp_Pattern == Bp_3)	sprintf(BpName, "BP_3_PAN__POSE__UNITY_1");
		else if(Block.Bp_Pattern == Bp_4)	{ ERROR_MSG(); ofExit(); return; }
		else if(Block.Bp_Pattern == Bp_5)	{ ERROR_MSG(); ofExit(); return; }
		else if(Block.Bp_Pattern == Bp_7)	sprintf(BpName, "BP_7_PAN__POSE__UNITY_3");
		else								{ ERROR_MSG(); ofExit(); return; }
		
	}else if(DeviceChType == CH_TILT){
		if(Block.Bp_Pattern == Bp_1)		{ ERROR_MSG(); ofExit(); return; }
		else if(Block.Bp_Pattern == Bp_2)	{ ERROR_MSG(); ofExit(); return; }
		else if(Block.Bp_Pattern == Bp_3)	sprintf(BpName, "BP_3_TILT__POSE__UNITY_1");
		else if(Block.Bp_Pattern == Bp_4)	{ ERROR_MSG(); ofExit(); return; }
		else if(Block.Bp_Pattern == Bp_5)	{ ERROR_MSG(); ofExit(); return; }
		else if(Block.Bp_Pattern == Bp_7)	sprintf(BpName, "BP_7_TILT__POSE__UNITY_3");
		else								{ ERROR_MSG(); ofExit(); return; }
		
	}else{ // CH_LUM
		if(Block.Bp_Pattern == Bp_1)		sprintf(BpName, "BP_1_LUM__STILL__OFF");
		else if(Block.Bp_Pattern == Bp_2)	sprintf(BpName, "BP_2_LUM__STILL__OFF");
		else if(Block.Bp_Pattern == Bp_3)	sprintf(BpName, "BP_3_LUM__STILL__OFF");
		else if(Block.Bp_Pattern == Bp_4)	sprintf(BpName, "BP_4_LUM__STILL__OFF");
		else if(Block.Bp_Pattern == Bp_5)	sprintf(BpName, "BP_5_LUM__STILL__OFF");
		else if(Block.Bp_Pattern == Bp_7)	sprintf(BpName, "BP_7_LUM__STILL__OFF");
		else								{ ERROR_MSG(); ofExit(); return; }
	}
	
	int id;
	for(id = 0; id < NumCandidates; id++){
		if( strcmp(Block.Bp_Pattern[id].name, BpName) == 0 ) break;
	}
	if(NumCandidates <= id) { ERROR_MSG(); ofExit(); return; }
	
	return id;
}

/******************************
******************************/
int LIGHT::FixTreatType_by_Blackoutmode_SelectBlockPattern(STATE State, bool b_PanTilt, int ChToSet)
{
	enum TREAT_TYPE{
		TREAT_TYPE__NORMAL,
		TREAT_TYPE__BLACKOUT,
		TREAT_TYPE__NOTOUCH,
	};
	TREAT_TYPE TreatType = TREAT_TYPE__NORMAL;
	
	if(Blackout == BLACKOUT__NONE){
		if(b_PanTilt){
			if(IsChangeTangible(State)){
				switch(ChToSet){
					case CH_LUM:
						TreatType = TREAT_TYPE__NORMAL;
						break;
					case CH_PAN:
					case CH_TILT:
						TreatType = TREAT_TYPE__NORMAL;
						break;
				}
			}else{
				switch(ChToSet){
					case CH_LUM:
						TreatType = TREAT_TYPE__NORMAL;
						break;
					case CH_PAN:
					case CH_TILT:
						TreatType = TREAT_TYPE__NOTOUCH;
						break;
				}
			}
		}else{
			switch(ChToSet){
				case CH_LUM:
					TreatType = TREAT_TYPE__NORMAL;
					break;
				case CH_PAN:
				case CH_TILT:
					TreatType = TREAT_TYPE__NOTOUCH;
					break;
			}
		}
	}else if(Blackout == BLACKOUT__MOVING_ONLY){
		if(b_PanTilt){
			if(IsChangeTangible(State)){
				switch(ChToSet){
					case CH_LUM:
						TreatType = TREAT_TYPE__NORMAL;
						break;
					case CH_PAN:
					case CH_TILT:
						TreatType = TREAT_TYPE__NORMAL;
						break;
				}
			}else{
				switch(ChToSet){
					case CH_LUM:
						TreatType = TREAT_TYPE__NORMAL;
						break;
					case CH_PAN:
					case CH_TILT:
						TreatType = TREAT_TYPE__NOTOUCH;
						break;
				}
			}
		}else{
			switch(ChToSet){
				case CH_LUM:
					TreatType = TREAT_TYPE__BLACKOUT;
					break;
				case CH_PAN:
				case CH_TILT:
					TreatType = TREAT_TYPE__NOTOUCH;
					break;
			}
		}
	}else if(Blackout == BLACKOUT__BLACK){
		if(b_PanTilt){
			if(IsChangeTangible(State)){
				switch(ChToSet){
					case CH_LUM:
						TreatType = TREAT_TYPE__BLACKOUT;
						break;
					case CH_PAN:
					case CH_TILT:
						TreatType = TREAT_TYPE__BLACKOUT;
						break;
				}
			}else{
				switch(ChToSet){
					case CH_LUM:
						TreatType = TREAT_TYPE__BLACKOUT;
						break;
					case CH_PAN:
					case CH_TILT:
						TreatType = TREAT_TYPE__NOTOUCH;
						break;
				}
			}
		}else{
			switch(ChToSet){
				case CH_LUM:
					TreatType = TREAT_TYPE__BLACKOUT;
					break;
				case CH_PAN:
				case CH_TILT:
					TreatType = TREAT_TYPE__NOTOUCH;
					break;
			}
		}
	}
	
	return int(TreatType);
}

/******************************
******************************/
void LIGHT::SelectBlockPattern(enum STATE State, BLOCK_GROUP *BlockGrouping, int BlockGrouping_id)
{
	/********************
	set Bp_Pattern_index of BpInfo_Luminance, BpInfo_Pan, BpInfo_Tilt
	********************/
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[LedBlock]); LedBlock++){
		int NumLogicalChs = get_Num_LogicalChs_inThisBlock(BlockGrouping[BlockGrouping_id].Block[LedBlock]);
		
		if(0 < NumLogicalChs){
			int NumCandidates = get_num_PatternTypes_in_Bp(BlockGrouping[BlockGrouping_id].Block[LedBlock].Bp_Pattern);
			int* Weight = (int*)malloc(sizeof(int) * NumCandidates);
			
			for(int ChToSet = CH_LUM; ChToSet < NUM_CH_TO_SET; ChToSet++){
				BP_INFO *BpInfo = NULL;
				
				/********************
				********************/
				switch(ChToSet){
					case CH_LUM:
						BpInfo = &BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Luminance;
						break;
						
					case CH_PAN:
						BpInfo = &BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Pan;
						break;
						
					case CH_TILT:
						BpInfo = &BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Tilt;
						break;
				}
				enum DEVICE_CH_TYPE DeviceChType = BpInfo->DeviceChType;
				enum PLAYMODE PlayMode = BpInfo->PlayMode;
				
				/********************
				enum TREAT_TYPE{
					TREAT_TYPE__NORMAL,
					TREAT_TYPE__BLACKOUT,
					TREAT_TYPE__NOTOUCH,
				};
				********************/
				int type = FixTreatType_by_Blackoutmode_SelectBlockPattern(State, BlockGrouping[BlockGrouping_id].Block[LedBlock].b_PanTilt, ChToSet);
				if(type != 2){
					if(type == 0){
						for(int i = 0; i < NumCandidates; i++){
							Weight[i] = BlockGrouping[BlockGrouping_id].Block[LedBlock].Bp_Pattern[i].Weight[DeviceChType][State][PlayMode][get_BoostMode()];
						}
						
						BpInfo->Bp_Pattern_index = Dice_index(Weight, NumCandidates);
						if(BpInfo->Bp_Pattern_index == -1) { ERROR_MSG(); ofExit(); return; }
						
					}else if(type == 1){
						BpInfo->Bp_Pattern_index = Select_BlackoutPattern(BlockGrouping[BlockGrouping_id].Block[LedBlock], CH_TO_SET(ChToSet));
					}
					
					/* */
					Set_LedTrackID_by_SymmetricType(BpInfo, BlockGrouping[BlockGrouping_id].Block[LedBlock].Bp_Pattern[BpInfo->Bp_Pattern_index].SymmetricType, NumLogicalChs);
					
					Dice_StartPatternId(BpInfo, BlockGrouping[BlockGrouping_id].Block[LedBlock].Bp_Pattern[BpInfo->Bp_Pattern_index].StartPatternId_Candidate);
				}
			}
			
			/********************
			********************/
			free(Weight);
		}
	}
	
	/********************
	log
	********************/
	char buf[BUF_SIZE];
	
	HF_debug_log(fp_script, now_ms);
	if( get_BoostMode() == BOOSTMODE_BOOST )	sprintf(buf, ";Boost mode\n");
	else										sprintf(buf, ";Normal mode(No Boost)\n");
	fprintf_Log(fp_script, "%s", buf);

	if( Blackout == BLACKOUT__NONE )				fprintf_Log(fp_script, ";BlackoutMode = None (IsChangeTangible = %d)\n", IsChangeTangible(State));
	else if( Blackout == BLACKOUT__MOVING_ONLY )	fprintf_Log(fp_script, ";BlackoutMode = MovingOnly (IsChangeTangible = %d)\n", IsChangeTangible(State));
	else if( Blackout == BLACKOUT__BLACK )			fprintf_Log(fp_script, ";BlackoutMode = Black (IsChangeTangible = %d)\n", IsChangeTangible(State));
	
	
	sprintf(buf, ";Pattern = (\n");
	fprintf_Log(fp_script, "%s", buf);
	
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping[BlockGrouping_id].Block[LedBlock]); LedBlock++){
		
		int NumLogicalChs = get_Num_LogicalChs_inThisBlock(BlockGrouping[BlockGrouping_id].Block[LedBlock]);
		
		if(0 < NumLogicalChs){
			for(int ChToSet = CH_LUM; ChToSet < NUM_CH_TO_SET; ChToSet++){
				BP_INFO *BpInfo = NULL;
				
				switch(ChToSet){
					case CH_LUM:
						BpInfo = &BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Luminance;
						break;
						
					case CH_PAN:
						BpInfo = &BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Pan;
						break;
						
					case CH_TILT:
						BpInfo = &BlockGrouping[BlockGrouping_id].Block[LedBlock].BpInfo_Tilt;
						break;
				}
				
				if( (ChToSet == int(CH_LUM)) ||
					( IsChangeTangible(State) && BlockGrouping[BlockGrouping_id].Block[LedBlock].b_PanTilt) )
				{
					sprintf(buf, "\t[%5d]%50s, start id = %5d, ",
							LedBlock, BlockGrouping[BlockGrouping_id].Block[LedBlock].Bp_Pattern[BpInfo->Bp_Pattern_index].name, BpInfo->Pattern_index);
					fprintf_Log(fp_script, "%s", buf);
					
					switch(BlockGrouping[BlockGrouping_id].Block[LedBlock].Bp_Pattern[BpInfo->Bp_Pattern_index].SymmetricType){
						case SYMMETRY_RANDOM:
							sprintf(buf, "SYMMETRY_RANDOM( ");
							break;
							
						case SYMMETRY_LINE:
							sprintf(buf, "SYMMETRY_LINE( ");
							break;
							
						case SYMMETRY_RIGID:
							sprintf(buf, "SYMMETRY_RIGID( ");
							break;
					}
					fprintf_Log(fp_script, "%s", buf);
					
					for(int i = 0; i < NumLogicalChs; i++){
						sprintf(buf, "%d, ", (int)BpInfo->ChId[i]);
						fprintf_Log(fp_script, "%s", buf);
					}
					
					fprintf_Log(fp_script, ")\n");
				}
			}
		}
	}
	sprintf(buf, ")\n\n");
	fprintf_Log(fp_script, "%s", buf);
}

/******************************
******************************/
int LIGHT::Is_SelfPropultion_Finish()
{
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock]); LedBlock++){
		if(0 < get_Num_LogicalChs_inThisBlock(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock])){
			if( (BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Luminance.PlayMode == SELF_PROPULSION) && (BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Luminance.SelfPropulsion.b_Fin_1Loop == false) ){
				return false;
			}
		}
	}
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock]); LedBlock++){
		if(0 < get_Num_LogicalChs_inThisBlock(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock])){
			if( (BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Luminance.PlayMode == SELF_PROPULSION) && (BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Luminance.SelfPropulsion.b_Fin_1Loop == false) ){
				return false;
			}
		}
	}
	
	return true;
}

/******************************
******************************/
int LIGHT::Is_StayTooLong_PatternChange(enum STATE State)
{
	if( (State == STATE_NOSOUND) || (State == STATE_SOUND) || (State == STATE_BEAT_IN) ){
		
		for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock]); LedBlock++){
			if( (0 < get_Num_LogicalChs_inThisBlock(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock])) && (BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Luminance.PlayMode == SELF_PROPULSION) ){
				/********************
				- LogicalChsが1以上
				- SELF_PROPULSION
				********************/
				int intervals = (int) (BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Luminance.SelfPropulsion.counter_Loop / BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].Bp_Pattern[BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Luminance.Bp_Pattern_index].Speed);
				
				if(PATTERN_CHANGE_BEATS <= intervals)	return true;
				else									return false;
			}
		}
		for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock]); LedBlock++){
			if( (0 < get_Num_LogicalChs_inThisBlock(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock])) && (BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Luminance.PlayMode == SELF_PROPULSION) ){
				/********************
				- LogicalChsが1以上
				- SELF_PROPULSION
				********************/
				int intervals = (int) (BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Luminance.SelfPropulsion.counter_Loop / BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].Bp_Pattern[BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Luminance.Bp_Pattern_index].Speed);
				
				if(PATTERN_CHANGE_BEATS <= intervals)	return true;
				else									return false;
			}
		}
		
		return false; // FALSE when no "SELF_PROPULSION" pattern.
		
	}else{
		
		return false;
	}
}

/******************************
******************************/
bool LIGHT::Select_Playmode_BlockPattern_ColorChange(STATE State)
{
	char buf[BUF_SIZE];
	
	/********************
	********************/
	debug_PatternChange[1] = 7.5;
	
	if(IsChangeTangible(State))	{ debug_PatternChange[0] = 7.0; }
	else						{ fprintf_Log(fp_script, ";Tangible Pattern No change\n"); }
	
	/********************
	********************/
	// const double ONE_FRAME_MS = 33.3667;
	const double ONE_FRAME_MS = 11;
	b_echo = true;
	EchoStep = int(255 * ONE_FRAME_MS / self_Beat_interval);
	EchoDownRatio = pow(1.0/255.0, ONE_FRAME_MS / self_Beat_interval);

	sprintf(buf, ";EchoDownRatio = %f\n\n", EchoDownRatio);
	fprintf_Log(fp_script, "%s", buf);

	/********************
	********************/
	SelectPlayMode_Lum(State, BlockGrouping_InTangible, BlockGrouping_id_InTangible);
	if(IsChangeTangible(State))	SelectPlayMode_PanTilt(State, BlockGrouping_InTangible, BlockGrouping_id_InTangible);

	SelectPlayMode_Lum(State, BlockGrouping_Tangible, BlockGrouping_id_Tangible);
	if(IsChangeTangible(State))	SelectPlayMode_PanTilt(State, BlockGrouping_Tangible, BlockGrouping_id_Tangible);
	
	/********************
	********************/
	SelectBlockPattern(State, BlockGrouping_InTangible, BlockGrouping_id_InTangible);
	SelectBlockPattern(State, BlockGrouping_Tangible, BlockGrouping_id_Tangible);
	
	/********************
	********************/
	bool Is_Flash = Dice_ColorChange(State);
	
	/********************
	********************/
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock]); LedBlock++){
		BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].Set_AllBpInfo_SelfPropulsion_LastBeatms(now_ms);
	}
	
	if(IsChangeTangible(State)){
		for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock]); LedBlock++){
			BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].Set_AllBpInfo_SelfPropulsion_LastBeatms(now_ms);
		}
	}else{
		for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock]); LedBlock++){
			BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Luminance.SelfPropulsion.LastBeat_ms = now_ms;
		}
	}

	/********************
	********************/
	return Is_Flash;
}

/******************************
description
	各BlockのBp_Patternを変更.
	Beat_interval, self_Beat_interval, LastBeat_msは、main側で、
	SelfPropulsion.LastBeat_msはclass側、update()にて更新.
	
	上記情報から、各BlockのLevelを計算できる状況が整う,
	→update()にてcal.
******************************/
void LIGHT::StateChart_Transition(TRANSITION Transition, bool& Is_Flash)
{
	/********************
	********************/
	char buf[BUF_SIZE];
	sprintf(buf, "\n;%10d[ms] Transition = %d-------------------------------------------------------------------------------------------------\n", (int)now_ms, (int)Transition);
	fprintf_Log(fp_script, "%s", buf);
	
	/********************
	********************/
	Is_Flash = false;

	/********************
	********************/
	switch(Transition){
		case BOOT_TO_NOSOUND:
		{
			BlockGrouping_id_InTangible = Dice_BlockGrouping(STATE_NOSOUND, INTANGIBLE);
			if(IsChangeTangible(STATE_NOSOUND))	BlockGrouping_id_Tangible = Dice_BlockGrouping(STATE_NOSOUND, TANGIBLE);
			
			init_StateChart();
			Is_Flash = Select_Playmode_BlockPattern_ColorChange(STATE_NOSOUND);
			
			break;
		}
		case NOSOUND_TO_NOSOUND:
		{
			BlockGrouping_id_InTangible = Dice_BlockGrouping(STATE_NOSOUND, INTANGIBLE);
			if(IsChangeTangible(STATE_NOSOUND))	BlockGrouping_id_Tangible = Dice_BlockGrouping(STATE_NOSOUND, TANGIBLE);
			
			Is_Flash = Select_Playmode_BlockPattern_ColorChange(STATE_NOSOUND);
			break;
		}
		case NOSOUND_TO_SOUND:
		{
			fprintf_Log(fp_script, ";No pattern change.\n");
			break;
		}
		case SOUND_TO_SOUND:
		{
			BlockGrouping_id_InTangible = Dice_BlockGrouping(STATE_SOUND, INTANGIBLE);
			if(IsChangeTangible(STATE_SOUND))	BlockGrouping_id_Tangible = Dice_BlockGrouping(STATE_SOUND, TANGIBLE);
			
			if( (Blackout != BLACKOUT__NONE) &&  (StopWatch_BlackoutClear.IsTimePassed(now_ms)) ){
				if(Blackout == BLACKOUT__MOVING_ONLY){
					t_Fadein_Tangible = -1;
					t_Fadein_InTangible = now_ms;
				}else if(Blackout == BLACKOUT__BLACK){
					t_Fadein_Tangible = now_ms;
					t_Fadein_InTangible = now_ms;
				}
				
				Clear_Blackout();
			}
			
			Is_Flash = Select_Playmode_BlockPattern_ColorChange(STATE_SOUND);
			break;
		}
		case SOUND_TO_BEATIN:
		{
			StopWatch_TangiblePatternChange.Reset();
			fprintf_Log(fp_script, ";No pattern change.\n");
			
			break;
		}
		case SOUND_TO_SOUNDDROP:
		{
			fprintf_Log(fp_script, ";No pattern change.\n");
			set_AllBlock_AllBpInfo_Luminance_SelfPropulsion_bFin1Loop_false();
			
			break;
		}
		case SOUNDDROP_TO_NOSOUND:
		{
			init_StateChart();
			
			BlockGrouping_id_InTangible = Dice_BlockGrouping(STATE_NOSOUND, INTANGIBLE);
			if(IsChangeTangible(STATE_NOSOUND))	BlockGrouping_id_Tangible = Dice_BlockGrouping(STATE_NOSOUND, TANGIBLE);

			Is_Flash = Select_Playmode_BlockPattern_ColorChange(STATE_NOSOUND);
			break;
		}
		case SOUNDDROP_TO_SOUND:
		{
			fprintf_Log(fp_script, ";No pattern change.\n");
			break;
		}
		case BEATIN_TO_BEATIN:
		{
			BlockGrouping_id_InTangible = Dice_BlockGrouping(STATE_BEAT_IN, INTANGIBLE);
			if(IsChangeTangible(STATE_BEAT_IN))	BlockGrouping_id_Tangible = Dice_BlockGrouping(STATE_BEAT_IN, TANGIBLE);
			
			/* */
			t_Fadein_Tangible = -1;
			t_Fadein_InTangible = -1;
			
			Clear_Blackout();
			
			/* */
			Is_Flash = Select_Playmode_BlockPattern_ColorChange(STATE_BEAT_IN);
			break;
		}
		case BEATIN_TO_FLYWHEEL:
		{
			BlockGrouping_id_InTangible = Dice_BlockGrouping(STATE_FLYWHEEL, INTANGIBLE);
			if(IsChangeTangible(STATE_FLYWHEEL))	BlockGrouping_id_Tangible = Dice_BlockGrouping(STATE_FLYWHEEL, TANGIBLE);
			
			Is_Flash = Select_Playmode_BlockPattern_ColorChange(STATE_FLYWHEEL);
			break;
		}
		case BEATIN_TO_BEATINDROP:
		{
			fprintf_Log(fp_script, ";No pattern change.\n");
			set_AllBlock_AllBpInfo_Luminance_SelfPropulsion_bFin1Loop_false();
			break;
		}
		case BEATINDROP_TO_NOSOUND:
		{
			init_StateChart();
			
			BlockGrouping_id_InTangible = Dice_BlockGrouping(STATE_NOSOUND, INTANGIBLE);
			if(IsChangeTangible(STATE_NOSOUND))	BlockGrouping_id_Tangible = Dice_BlockGrouping(STATE_NOSOUND, TANGIBLE);
			
			Is_Flash = Select_Playmode_BlockPattern_ColorChange(STATE_NOSOUND);
			break;
		}
		case BEATINDROP_TO_SOUND:
		{
			BlockGrouping_id_InTangible = Dice_BlockGrouping(STATE_SOUND, INTANGIBLE);
			if(IsChangeTangible(STATE_SOUND))	BlockGrouping_id_Tangible = Dice_BlockGrouping(STATE_SOUND, TANGIBLE);

			Is_Flash = Select_Playmode_BlockPattern_ColorChange(STATE_SOUND);
			break;
		}
		case BEATINDROP_TO_BEATIN:
		{
			fprintf_Log(fp_script, ";No pattern change.\n");
			break;
		}
		case FLYWHEEL_TO_FLYWHEEL:
		{
			BlockGrouping_id_InTangible = Dice_BlockGrouping(STATE_FLYWHEEL, INTANGIBLE);
			if(IsChangeTangible(STATE_FLYWHEEL))	BlockGrouping_id_Tangible = Dice_BlockGrouping(STATE_FLYWHEEL, TANGIBLE);
			
			Is_Flash = Select_Playmode_BlockPattern_ColorChange(STATE_FLYWHEEL);
			break;
		}
		case FLYWHEEL_TO_FLYWHEELDROP:
		{
			fprintf_Log(fp_script, ";No pattern change.\n");
			set_AllBlock_AllBpInfo_Luminance_SelfPropulsion_bFin1Loop_false();
			break;
		}
		case FLYWHEELDROP_TO_NOSOUND:
		{
			init_StateChart();
			
			BlockGrouping_id_InTangible = Dice_BlockGrouping(STATE_NOSOUND, INTANGIBLE);
			if(IsChangeTangible(STATE_NOSOUND))	BlockGrouping_id_Tangible = Dice_BlockGrouping(STATE_NOSOUND, TANGIBLE);
			
			Is_Flash = Select_Playmode_BlockPattern_ColorChange(STATE_NOSOUND);
			break;
		}
		case FLYWHEELDROP_TO_SOUND:
		{
			BlockGrouping_id_InTangible = Dice_BlockGrouping(STATE_SOUND, INTANGIBLE);
			if(IsChangeTangible(STATE_SOUND))	BlockGrouping_id_Tangible = Dice_BlockGrouping(STATE_SOUND, TANGIBLE);
			
			Dice_Blackout();
			if(Blackout == BLACKOUT__MOVING_ONLY)	StopWatch_BlackoutClear.start(now_ms, TIMEOUT_MOVING_ONLY);
			else if(Blackout == BLACKOUT__BLACK)	StopWatch_BlackoutClear.start(now_ms, TIMEOUT_BLACK);
			else									{ /* no need to set. */ }
			
			Is_Flash = Select_Playmode_BlockPattern_ColorChange(STATE_SOUND);
			break;
		}
		
		default:
			break;
	}

	/***********************
	***********************/
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock]); LedBlock++){
		BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Luminance.SelfPropulsion.counter_Loop = 0;
	}
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock]); LedBlock++){
		BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Luminance.SelfPropulsion.counter_Loop = 0;
	}
	
	
	/***********************
	***********************/
	sprintf(buf, ";self_Beat_interval = %d\n\n", (int)self_Beat_interval);
	fprintf_Log(fp_script, "%s", buf);
}

/******************************
******************************/
void LIGHT::Clear_Blackout()
{
	Blackout = BLACKOUT__NONE;
}

/******************************
	enum BLACKOUT{
		BLACKOUT__NONE,
		BLACKOUT__MOVING_ONLY,
		BLACKOUT__BLACK,
		
		NUM_BLACKOUT_TYPES,
	};
******************************/
void LIGHT::Dice_Blackout()
{
	return BLACKOUT__NONE;
	
	
	/*
	int Weight[NUM_BLACKOUT_TYPES]	= {4, 4, 1};
	
	int index = Dice_index(Weight, NUM_BLACKOUT_TYPES);
	if(index == -1) { ERROR_MSG(); ofExit(); return; }
	
	Blackout = BLACKOUT(index);
	*/
}

/******************************
******************************/
void LIGHT::setup()
{
	/********************
	********************/
	udpConnection.Create();
	// udpConnection.Connect("10.0.0.2", UDP_SEND_PORT);
	udpConnection.Connect("127.0.0.1", UDP_SEND_PORT);
	udpConnection.SetNonBlocking(true);
}

/******************************
******************************/
void LIGHT::update()
{
	/********************
	一度、DeviceOutputChに全ての出力data(RGB)を格納.
	BeatGeneratorの仕様に合わせ、PhysicalLedColorChの順に出力する必要があるため.
	********************/
	for(int i = 0; i < NUM_PHYSICAL_LEDS; i++)	DeviceOutputCh[i].Reset();
	
	/* */
	if(t_Fadein_Tangible != -1)		fprintf_Log(fp_script, "Fadein:Tangible: %f\n", Cal_FadeinRatio(t_Fadein_Tangible));
	if(t_Fadein_InTangible != -1)	fprintf_Log(fp_script, "Fadein:InTangible: %f\n", Cal_FadeinRatio(t_Fadein_InTangible));
		
	/* */
	fprintf_Log(fp_script, "(Self or Beat, Progress) of Block 0, 1, ... = \n");
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock]); LedBlock++){
		update_OneBlock(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock], DeviceOutputCh);
	}
	fprintf_Log(fp_script, "\n\n");

	/* */
	fprintf_Log(fp_script, "(Self or Beat, Progress) of Block 0, 1, ... = \n");
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock]); LedBlock++){
		update_OneBlock(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock], DeviceOutputCh);
	}
	fprintf_Log(fp_script, "\n\n");
	
	
	/********************
	********************/
	if(b_1st){
		b_1st = false;
		for(int i = 0; i < NUM_PHYSICAL_LEDS; i++)	{ LedEcho[i].R = 0;	LedEcho[i].G = 0;	LedEcho[i].B = 0; }
		
		for(int i = 0; i < NUM_PHYSICAL_LEDS/2; i++){ Last_LedAngle[i].Pan = 0; Last_LedAngle[i].Tilt = 0; }
	}
	
	if(b_echo){
		char buf[BUF_SIZE];
		
		fprintf_Log(fp_script, ";Echo-ing\n");
		
		
		int count = 0;
		
		for(int i = 0; i < NUM_PHYSICAL_LEDS; i++){
			// LedEcho[i].Minus(EchotStep); // with Limit check.
			LedEcho[i].xRatio(EchoDownRatio);
			
			if(LedEcho[i].IsZero()) count++;
			
			DeviceOutputCh[i].Lum += LedEcho[i]; // with Limit check.
		}
		
		if(NUM_PHYSICAL_LEDS <= count){
			b_echo = false;
			
			fprintf_Log(fp_script, ";No Echo and Finish\n\n");
		}else{
			fprintf_Log(fp_script, ";Added Echo\n\n");
		}
		
	}else{
		for(int i = 0; i < NUM_PHYSICAL_LEDS; i++){
			LedEcho[i] = DeviceOutputCh[i].Lum;
		}
	}
}

/******************************
******************************/
void LIGHT::update_OneBlock(BLOCK& block, DEVICE_OUTPUT_CH* DeviceOutputCh)
{
	fprintf_Log(fp_script, "{ ");
	
	for(int ChToSet = CH_LUM; ChToSet < NUM_CH_TO_SET; ChToSet++){
		char buf[BUF_SIZE];
		
		BP_INFO *BpInfo = NULL;
		
		/********************
		********************/
		switch(ChToSet){
			case CH_LUM:
				BpInfo = &block.BpInfo_Luminance;
				break;
				
			case CH_PAN:
				BpInfo = &block.BpInfo_Pan;
				break;
				
			case CH_TILT:
				BpInfo = &block.BpInfo_Tilt;
				break;
		}
		
		/********************
		********************/
		int NUM_LOGICAL_CHS = get_Num_LogicalChs_inThisBlock(block);
		int Progress;
		
		if( (ChToSet == int(CH_LUM)) || (block.b_PanTilt) ){
			if(0 < NUM_LOGICAL_CHS){
				if(BpInfo->PlayMode == SELF_PROPULSION){
					Progress = CalProgress(self_Beat_interval, BpInfo->SelfPropulsion.LastBeat_ms, block.Bp_Pattern[BpInfo->Bp_Pattern_index].Speed);
					sprintf(buf, "(Self, %d), ", Progress);
				}else{
					Progress = CalProgress(Beat_interval, LastBeat_ms, block.Bp_Pattern[BpInfo->Bp_Pattern_index].Speed);
					sprintf(buf, "(Beat, %d), ", Progress);
				}
			}else{
				Progress = 0;
				sprintf(buf, "(xx, --), ");
			}
			
			fprintf_Log(fp_script, "%s", buf);
		}
		
		/********************
		********************/
		if( (ChToSet == int(CH_LUM)) || (block.b_PanTilt) ){
			for(int i = 0; i < NUM_LOGICAL_CHS; i++){
				/********************
				i番目のLed出力を算出.
				BlockPatternはtrack入れ替えがあるので注意.
				LedColorは入れ替えなどないので、そのまま.
				********************/
				int ChTrackId = BpInfo->ChId[i]; // LogicalChのi番目はどのBlockPattern trackを参照するか.
				
				int Lev = CalLev_from_ShortPattern(block.Bp_Pattern[BpInfo->Bp_Pattern_index].pShortPattern[BpInfo->Pattern_index][ChTrackId], Progress);
				
				/********************
				********************/
				if(	((ChToSet == int(CH_LUM)) && block.b_PanTilt) &&
					(t_Fadein_Tangible != -1) )
				{
					double ratio = Cal_FadeinRatio(t_Fadein_Tangible);
					Lev = int(Lev * ratio);
				}
				
				if(	((ChToSet == int(CH_LUM)) && !block.b_PanTilt) &&
					(t_Fadein_InTangible != -1) )
				{
					double ratio = Cal_FadeinRatio(t_Fadein_InTangible);
					Lev = int(Lev * ratio);
				}
				
				/********************
				********************/
				int NUM_PHYSICAL_CHS = get_Num_PhysicalChs_inThisLogicalCh(block.LogicalCh[i]);
				for(int j = 0; j < NUM_PHYSICAL_CHS; j++){
					struct COLOR color;
					
					int id_physicalLed = block.LogicalCh[i].PhysicalCh[j];
					
					if(ChToSet == int(CH_LUM)){
						MakeColorFromPalette(&PhysicalLedColorCh[id_physicalLed]);
						CalColor(PhysicalLedColorCh[id_physicalLed].LedColor, Lev, &color);
						
						DeviceOutputCh[id_physicalLed].Lum = color;
						
					}else if(ChToSet == int(CH_PAN)){
						DeviceOutputCh[id_physicalLed].Angle.Pan	= Lev;
						
					}else{
						DeviceOutputCh[id_physicalLed].Angle.Tilt	= Lev;
						
					}
				}
			}
		}
		
		/********************
		********************/
		if(BpInfo->PlayMode == SELF_PROPULSION){
			/* if finish pattern, go to next. */
			if( MAXPROGRESS_ANIM_KEY <= Progress ){
				PatternIndex_next(block.Bp_Pattern[BpInfo->Bp_Pattern_index], BpInfo->Pattern_index);
				
				BpInfo->SelfPropulsion.LastBeat_ms = now_ms;
				BpInfo->SelfPropulsion.counter_Loop++;
				BpInfo->SelfPropulsion.b_Fin_1Loop = true;
			}
		}
	}
	fprintf_Log(fp_script, "}, ");
}

/******************************
******************************/
double LIGHT::Cal_FadeinRatio(int& t_Fadein)
{
	double t_thresh_ms = 1000;
	
	if(t_thresh_ms <= now_ms - t_Fadein){
		
		t_Fadein = -1;
		return 1.0;
		
	}else{
		
		double tan = 1/t_thresh_ms;
		return tan * (now_ms - t_Fadein);
	}
}

/******************************
******************************/
int LIGHT::CalProgress(int Beat_interval, int LastBeat_ms, double Speed)
{
	if( LastBeat_ms == -1 ){
		ERROR_MSG(); ofExit(); return;
		
	}else if(Beat_interval == 0){
		ERROR_MSG(); ofExit(); return;
		
	}else if(now_ms <= LastBeat_ms){
		return 0;
		
	}else if( Beat_interval <= (int)((now_ms - LastBeat_ms) * Speed) ){
		return MAXPROGRESS_ANIM_KEY;
		
	}else{
		return (int)( (now_ms - LastBeat_ms) * Speed * MAXPROGRESS_ANIM_KEY / Beat_interval );
	}
}

/******************************
******************************/
int LIGHT::CalLev_from_ShortPattern(PFUNC_SHORTPATTERN pFunc_sp, int Progress)
{
	/********************
	********************/
	if(Progress < 0)	{ ERROR_MSG(); ofExit(); return; }
	
	if(MAXPROGRESS_ANIM_KEY <= Progress){
		return pFunc_sp(MAXPROGRESS_ANIM_KEY);
	}else{
		return pFunc_sp(Progress);
	}
}

/******************************
******************************/
void LIGHT::MakeColorFromPalette(PHYSICAL_LED_COLOR_CH *Led)
{
	/********************
	********************/
	if(!Led->IsDynamicColor){
		return;
		
	}else if( Led->f_ColorChange != COLOR_CHANGE){
		return;
		
	}
	
	/********************
	********************/
	enum{
		MAXPROGRESS = 10000,
	};

	int Progress;
	if(now_ms <= Led->t_ColorChangeStart){
		Progress = 0;
	}else if(system_ColorTheme_palette->interval_ms <= now_ms - Led->t_ColorChangeStart){
		Progress = MAXPROGRESS;
	}else{
		Progress = (now_ms - Led->t_ColorChangeStart) * MAXPROGRESS / system_ColorTheme_palette->interval_ms;
	}
	
	/******************************
	******************************/
	Led->LedColor.R = Led->LedFrom.R + (Led->LedTo.R - Led->LedFrom.R) * Progress / MAXPROGRESS;
	Led->LedColor.G = Led->LedFrom.G + (Led->LedTo.G - Led->LedFrom.G) * Progress / MAXPROGRESS;
	Led->LedColor.B = Led->LedFrom.B + (Led->LedTo.B - Led->LedFrom.B) * Progress / MAXPROGRESS;

	/******************************
	******************************/
	if(MAXPROGRESS <= Progress){
		Led->f_ColorChange = COLOR_KEEP;
	}
}

/******************************
******************************/
void LIGHT::PatternIndex_next(const BLOCK_PATTERN& BlockPattern, int& Pattern_index)
{
	Pattern_index++;
	
	if(BlockPattern.pShortPattern[Pattern_index][0] == NULL){
		Pattern_index = 0;
	}
}

/******************************
******************************/
void LIGHT::Beat_PatternIndex_next_AllBlock()
{
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock]); LedBlock++){
		if(0 < get_Num_LogicalChs_inThisBlock(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock])){
			if(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Luminance.PlayMode == BEAT_PROPULSION){
				PatternIndex_next(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].Bp_Pattern[BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Luminance.Bp_Pattern_index], BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Luminance.Pattern_index);
			}
			if(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Pan.PlayMode == BEAT_PROPULSION){
				PatternIndex_next(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].Bp_Pattern[BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Pan.Bp_Pattern_index], BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Pan.Pattern_index);
			}
			if(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Tilt.PlayMode == BEAT_PROPULSION){
				PatternIndex_next(BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].Bp_Pattern[BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Tilt.Bp_Pattern_index], BlockGrouping_InTangible[BlockGrouping_id_InTangible].Block[LedBlock].BpInfo_Tilt.Pattern_index);
			}
		}
	}
	
	for(int LedBlock = 0; !Is_PeriodOfBlockGroup(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock]); LedBlock++){
		if(0 < get_Num_LogicalChs_inThisBlock(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock])){
			if(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Luminance.PlayMode == BEAT_PROPULSION){
				PatternIndex_next(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].Bp_Pattern[BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Luminance.Bp_Pattern_index], BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Luminance.Pattern_index);
			}
			if(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Pan.PlayMode == BEAT_PROPULSION){
				PatternIndex_next(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].Bp_Pattern[BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Pan.Bp_Pattern_index], BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Pan.Pattern_index);
			}
			if(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Tilt.PlayMode == BEAT_PROPULSION){
				PatternIndex_next(BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].Bp_Pattern[BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Tilt.Bp_Pattern_index], BlockGrouping_Tangible[BlockGrouping_id_Tangible].Block[LedBlock].BpInfo_Tilt.Pattern_index);
			}
		}
	}
}

/******************************
******************************/
void LIGHT::CalColor(struct COLOR LedColor, int Lev, struct COLOR *outColor)
{
	outColor->R = Lev * LedColor.R / 255;
	outColor->G = Lev * LedColor.G / 255;
	outColor->B = Lev * LedColor.B / 255;
}

/******************************
******************************/
void LIGHT::draw(bool b_SoundOn)
{
	/********************
	LedOutputColorを一気に出力.
	********************/
	/* */
	fprintf_Log(fp_script, "==========\n");
	
	char buf[BUF_SIZE];
	sprintf(buf, "<time_ms> %d\n", now_ms);
	fprintf_Dmx(fp_script, "%s", buf);

	string message = "";
	for(int i = 0; i < NUM_PHYSICAL_LEDS/2; i++){
		if(DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Angle.Pan != -1){
			/* Log */
			sprintf(buf, "%5d %5d %5d %5d %5d %5d %5d\n", 
						i, DeviceOutputCh[i].Lum.R, DeviceOutputCh[i].Lum.G, DeviceOutputCh[i].Lum.B, DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Lum.R, 
						DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Angle.Pan, DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Angle.Tilt);
			
			Last_LedAngle[i] = DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Angle;
			
			/* UDP */
			if(b_SoundOn){
				message +=	ofToString(int(DeviceOutputCh[i].Lum.R))							+ "," + 
							ofToString(int(DeviceOutputCh[i].Lum.G))							+ "," +
							ofToString(int(DeviceOutputCh[i].Lum.B))							+ "," +
							ofToString(int(DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Lum.R))		+ "," + // W
							ofToString(int(DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Angle.Pan))	+ "," +
							ofToString(int(DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Angle.Tilt))	+ "|";
			}else{
				message +=	ofToString(0)														+ "," + 
							ofToString(0)														+ "," +
							ofToString(0)														+ "," +
							ofToString(0)														+ "," + // W
							ofToString(int(DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Angle.Pan))	+ "," +
							ofToString(int(DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Angle.Tilt))	+ "|";
			}
						
		}else if(DeviceOutputCh[i].Angle.Pan != -1){
			/* Log */
			sprintf(buf, "%5d %5d %5d %5d %5d %5d %5d\n", 
						i, DeviceOutputCh[i].Lum.R, DeviceOutputCh[i].Lum.G, DeviceOutputCh[i].Lum.B, DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Lum.R,
						DeviceOutputCh[i].Angle.Pan, DeviceOutputCh[i].Angle.Tilt);
						
			Last_LedAngle[i] = DeviceOutputCh[i].Angle;
			
			/* UDP */
			if(b_SoundOn){
				message +=	ofToString(int(DeviceOutputCh[i].Lum.R))							+ "," + 
							ofToString(int(DeviceOutputCh[i].Lum.G))							+ "," +
							ofToString(int(DeviceOutputCh[i].Lum.B))							+ "," +
							ofToString(int(DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Lum.R))		+ "," + // W
							ofToString(int(DeviceOutputCh[i].Angle.Pan))						+ "," +
							ofToString(int(DeviceOutputCh[i].Angle.Tilt))						+ "|";
			}else{
				message +=	ofToString(0)														+ "," + 
							ofToString(0)														+ "," +
							ofToString(0)														+ "," +
							ofToString(0)														+ "," + // W
							ofToString(int(DeviceOutputCh[i].Angle.Pan))						+ "," +
							ofToString(int(DeviceOutputCh[i].Angle.Tilt))						+ "|";
			}
						
		}else{
			/* Log */
			sprintf(buf, "%5d %5d %5d %5d %5d %5d %5d\n", 
						i, DeviceOutputCh[i].Lum.R, DeviceOutputCh[i].Lum.G, DeviceOutputCh[i].Lum.B, DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Lum.R, Last_LedAngle[i].Pan, Last_LedAngle[i].Tilt);
						
			/* UDP */
			if(b_SoundOn){
				message +=	ofToString(int(DeviceOutputCh[i].Lum.R))							+ "," + 
							ofToString(int(DeviceOutputCh[i].Lum.G))							+ "," +
							ofToString(int(DeviceOutputCh[i].Lum.B))							+ "," +
							ofToString(int(DeviceOutputCh[i + NUM_PHYSICAL_LEDS/2].Lum.R))		+ "," + // W
							ofToString(int(Last_LedAngle[i].Pan))								+ "," +
							ofToString(int(Last_LedAngle[i].Tilt))								+ "|";
			}else{
				message +=	ofToString(0)														+ "," + 
							ofToString(0)														+ "," +
							ofToString(0)														+ "," +
							ofToString(0)														+ "," + // W
							ofToString(int(Last_LedAngle[i].Pan))								+ "," +
							ofToString(int(Last_LedAngle[i].Tilt))								+ "|";
			}
		}
		
		fprintf_Dmx(fp_script, "%s", buf);
	}
	fprintf_Log(fp_script, "==========\n");
	
	/********************
	********************/
	if(b_Demo && b_LightOperatorExist){
		/********************
		送り先のIPが不在だと、Errorとなり、関数の向こう側でError message表示し続けるので。
		********************/
		if(udpConnection.Send(message.c_str(),message.length()) == -1){
			ERROR_MSG();
			b_LightOperatorExist = false;
		}
	}
}

/************************************************************************************************************************/
} // namespace SPACE_LIGHT{


