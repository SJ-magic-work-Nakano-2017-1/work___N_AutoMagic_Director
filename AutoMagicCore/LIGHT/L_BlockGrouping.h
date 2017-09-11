/************************************************************
// test code
//		check if "Bp_Pattern" is correct(compare logical Chs and Bp_Pattern).
//		Physical ch setting check
//

void LIGHT::Check(FILE* fp, BLOCK_GROUP *BlockGrouping, int NUM_GROUPTYPES)
{
	for(int GroupId = 0; GroupId < NUM_GROUPTYPES; GroupId++){
		
		// check if "Bp_Pattern" is correct.
		for(int i = 0; !Is_PeriodOfBlockGroup(BlockGrouping[GroupId].Block[i]); i++){
			int NumLogicalChs = get_Num_LogicalChs_inThisBlock(BlockGrouping[GroupId].Block[i]);
			
			switch(NumLogicalChs){
				case 0:
					break;
				case 1:
					if(BlockGrouping[GroupId].Block[i].Bp_Pattern != Bp_1){
						ERROR_MSG();
						printf("Error in Group_%d %d[th] Block\n", GroupId, i);
						std::exit(1);
					}
					break;
				case 2:
					if(BlockGrouping[GroupId].Block[i].Bp_Pattern != Bp_2){
						ERROR_MSG();
						printf("Error in Group_%d %d[th] Block\n", GroupId, i);
						std::exit(1);
					}
					break;
				case 3:
					if(BlockGrouping[GroupId].Block[i].Bp_Pattern != Bp_3){
						ERROR_MSG();
						printf("Error in Group_%d %d[th] Block\n", GroupId, i);
						std::exit(1);
					}
					break;
				case 4:
					if(BlockGrouping[GroupId].Block[i].Bp_Pattern != Bp_4){
						ERROR_MSG();
						printf("Error in Group_%d %d[th] Block\n", GroupId, i);
						std::exit(1);
					}
					break;
				case 5:
					if(BlockGrouping[GroupId].Block[i].Bp_Pattern != Bp_5){
						ERROR_MSG();
						printf("Error in Group_%d %d[th] Block\n", GroupId, i);
						std::exit(1);
					}
					break;
				case 7:
					if(BlockGrouping[GroupId].Block[i].Bp_Pattern != Bp_7){
						ERROR_MSG();
						printf("Error in Group_%d %d[th] Block\n", GroupId, i);
						std::exit(1);
					}
					break;
				default:
					printf("Error in Group_%d %d[th] Block\n", GroupId, i);
					std::exit(1);
					break;
			}
			
		}
		
		
		// Physical ch setting check
		fprintf_Log_forTestCode(fp, "------------------------------------------------------------\n");
		fprintf_Log_forTestCode(fp, "[%d]:%s\n", GroupId, BlockGrouping[GroupId].BlockName);
		fprintf_Log_forTestCode(fp, "------------------------------------------------------------\n");
		
		for(int i = 0; !Is_PeriodOfBlockGroup(BlockGrouping[GroupId].Block[i]); i++){
			int NumLogicalChs = get_Num_LogicalChs_inThisBlock(BlockGrouping[GroupId].Block[i]);
			
			if(NumLogicalChs){
				fprintf_Log_forTestCode(fp, "Block_%d", i);
				
				if(BlockGrouping[GroupId].Block[i].b_PanTilt){
					fprintf_Log_forTestCode(fp, " (PanTilt)\n");
				}else{
					fprintf_Log_forTestCode(fp, "\n");
				}
				
				
				for(int j = 0; j < NumLogicalChs; j++){
					fprintf_Log_forTestCode(fp, "\tLogicalCh_%4d = ", j);
					
					int NumPhysicalChs = get_Num_PhysicalChs_inThisLogicalCh(BlockGrouping[GroupId].Block[i].LogicalCh[j]);
					
					for(int k = 0; k < NumPhysicalChs; k++){
						fprintf_Log_forTestCode(fp, "%4d, ", BlockGrouping[GroupId].Block[i].LogicalCh[j].PhysicalCh[k]);
					}
					fprintf_Log_forTestCode(fp, "\n");
				}
				fprintf_Log_forTestCode(fp, "\n");
			}
		}
		fprintf_Log_forTestCode(fp, "\n");
	}
}

void LIGHT::test()
{
	FILE* fp;
	
	fp = fopen("../../../SJ_Tangible.txt", "w");
	Check(fp, BlockGrouping_Tangible, NUM_GROUPTYPES_TANGIBLE);
	fclose(fp);
	
	fp = fopen("../../../SJ_InTangible.txt", "w");
	Check(fp, BlockGrouping_InTangible, NUM_GROUPTYPES_INTANGIBLE);
	fclose(fp);

	printf("Finish\n");
}
************************************************************/



#pragma once

/************************************************************
************************************************************/
#include "../am_common.h"


/************************************************************************************************************************/
namespace SPACE_LIGHT{




/************************************************************
************************************************************/

struct PHYSICAL_CH_SET{
	enum{
		MAX_CHS_IN_1LOGICAL_CH = 150,
	};
	int PhysicalCh[MAX_CHS_IN_1LOGICAL_CH];
};

struct ANIM_SELF_PROPULSION{
	int LastBeat_ms;
	int counter_Loop;
	bool b_Fin_1Loop;
};

struct BP_INFO{
	/********************
	********************/
	enum DEVICE_CH_TYPE DeviceChType;
	
	/********************
	********************/
	enum PLAYMODE PlayMode;
	int Bp_Pattern_index;
	int Pattern_index;
	ANIM_SELF_PROPULSION SelfPropulsion;
	int ChId[MAX_CHS_IN_A_BLOCK];
};

struct BLOCK{
	/********************
	********************/
	PHYSICAL_CH_SET LogicalCh[MAX_CHS_IN_A_BLOCK + 1];
	
	// int Weight_PlayMode_Lum[NUM_STATES][NUM_BOOSTMODE][NUM_PLAYMODES];
	int (*Weight_PlayMode_Lum)[NUM_BOOSTMODE][NUM_PLAYMODES];
	int (*Weight_PlayMode_PanTilt)[NUM_BOOSTMODE][NUM_PLAYMODES];
	
	bool b_PanTilt;
	
	const BLOCK_PATTERN *Bp_Pattern;
	
	/********************
	********************/
	BP_INFO BpInfo_Luminance;
	BP_INFO BpInfo_Pan;
	BP_INFO BpInfo_Tilt;
	
	
	/********************
	********************/
	void Set_AllBpInfo_SelfPropulsion_LastBeatms(int now_ms)
	{
		BpInfo_Luminance.SelfPropulsion.LastBeat_ms = now_ms;
		BpInfo_Pan.SelfPropulsion.LastBeat_ms = now_ms;
		BpInfo_Tilt.SelfPropulsion.LastBeat_ms = now_ms;
	}
	
	void Reset_AllBpInfo_SelfPropulsion(int now_ms)
	{
		Set_AllBpInfo_SelfPropulsion_LastBeatms(now_ms);
		
		BpInfo_Luminance.SelfPropulsion.counter_Loop = 0;
		BpInfo_Luminance.SelfPropulsion.b_Fin_1Loop = false;

		BpInfo_Pan.SelfPropulsion.counter_Loop = 0;
		BpInfo_Pan.SelfPropulsion.b_Fin_1Loop = false;

		BpInfo_Tilt.SelfPropulsion.counter_Loop = 0;
		BpInfo_Tilt.SelfPropulsion.b_Fin_1Loop = false;
	}
};

struct BLOCK_GROUP{
	enum{
		MAX_BLOCKS = 100,
	};
	
	char BlockName[BUF_SIZE];
	BLOCK Block[MAX_BLOCKS];
};

/************************************************************
************************************************************/

static int Weight_PlayMode_PanTilt[NUM_STATES][NUM_BOOSTMODE][NUM_PLAYMODES] = {
	{ // STATE_NOSOUND, 
		// Normal{Beat, Self}, Boost{Beat, Self}
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND, 
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND_DROP, 
	},
	{ // STATE_BEAT_IN, 
		{0, 1}, {0, 1},
	},
	{ // STATE_BEAT_IN_DROP, 
	},
	{ // STATE_FLYWHEEL, 
		{0, 1}, {0, 1},
	},
	{ // STATE_FLYWHEEL_DROP, 
	},
};

static int Weight_PlayMode_Mov_RGB[NUM_STATES][NUM_BOOSTMODE][NUM_PLAYMODES] = {
	{ // STATE_NOSOUND, 
		// Normal{Beat, Self}, Boost{Beat, Self}
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND, 
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND_DROP, 
	},
	{ // STATE_BEAT_IN, 
		{3, 1}, {1, 1},
	},
	{ // STATE_BEAT_IN_DROP, 
	},
	{ // STATE_FLYWHEEL, 
		{1, 1}, {1, 1},
	},
	{ // STATE_FLYWHEEL_DROP, 
	},
};

static int Weight_PlayMode_Mov_Strobe[NUM_STATES][NUM_BOOSTMODE][NUM_PLAYMODES] = {
	{ // STATE_NOSOUND, 
		// Normal{Beat, Self}, Boost{Beat, Self}
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND, 
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND_DROP, 
	},
	{ // STATE_BEAT_IN, 
		{3, 1}, {1, 1},
	},
	{ // STATE_BEAT_IN_DROP, 
	},
	{ // STATE_FLYWHEEL, 
		{2, 1}, {2, 1},
	},
	{ // STATE_FLYWHEEL_DROP, 
	},
};

static int Weight_PlayMode_Fix_RGB[NUM_STATES][NUM_BOOSTMODE][NUM_PLAYMODES] = {
	{ // STATE_NOSOUND, 
		// Normal{Beat, Self}, Boost{Beat, Self}
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND, 
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND_DROP, 
	},
	{ // STATE_BEAT_IN, 
		{5, 1}, {1, 1},
	},
	{ // STATE_BEAT_IN_DROP, 
	},
	{ // STATE_FLYWHEEL, 
		{3, 1}, {2, 1},
	},
	{ // STATE_FLYWHEEL_DROP, 
	},
};

static int Weight_PlayMode_Fix_Strobe[NUM_STATES][NUM_BOOSTMODE][NUM_PLAYMODES] = {
	{ // STATE_NOSOUND, 
		// Normal{Beat, Self}, Boost{Beat, Self}
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND, 
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND_DROP, 
	},
	{ // STATE_BEAT_IN, 
		{5, 1}, {1, 1},
	},
	{ // STATE_BEAT_IN_DROP, 
	},
	{ // STATE_FLYWHEEL, 
		{2, 1}, {2, 1},
	},
	{ // STATE_FLYWHEEL_DROP, 
	},
};

static int Weight_PlayMode_WallWasher[NUM_STATES][NUM_BOOSTMODE][NUM_PLAYMODES] = {
	{ // STATE_NOSOUND, 
		// Normal{Beat, Self}, Boost{Beat, Self}
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND, 
		{0, 1}, {0, 1},
	},
	{ // STATE_SOUND_DROP, 
	},
	{ // STATE_BEAT_IN, 
		{0, 1}, {0, 1},
	},
	{ // STATE_BEAT_IN_DROP, 
	},
	{ // STATE_FLYWHEEL, 
		{0, 1}, {0, 1},
	},
	{ // STATE_FLYWHEEL_DROP, 
	},
};


/************************************************************
šššššššššššššššššššššššššššššš
Copy from Excel below.
šššššššššššššššššššššššššššššš
************************************************************/
BLOCK_GROUP BlockGrouping_InTangible[] = {						
	{					
		"GP0__NOSOUND",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 5, 49, -1},	// CH0
					{1, 45, 6, 50, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 8, 52, -1},	// CH3
					{4, 48, 9, 53, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__SOUND_NORMAL__SYNC__STRAIGHT",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 5, 49, -1},	// CH0
					{1, 45, 6, 50, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 8, 52, -1},	// CH3
					{4, 48, 9, 53, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 23, 67, 30, 74, 37, 81, -1},	// CH0
					{17, 61, 24, 68, 31, 75, 38, 82, -1},	// CH1
					{18, 62, 25, 69, 32, 76, 39, 83, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 27, 71, 34, 78, 41, 85, -1},	// CH4
					{21, 65, 28, 72, 35, 79, 42, 86, -1},	// CH5
					{22, 66, 29, 73, 36, 80, 43, 87, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, 93, 98, -1},	// CH0
					{89, 94, 99, -1},	// CH1
					{90, 95, 100, -1},	// CH2
					{91, 96, 101, -1},	// CH3
					{92, 97, 102, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
					{103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__SOUND_NORMAL__SYNC__TWIST",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 9, 53, -1},	// CH0
					{1, 45, 8, 52, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 6, 50, -1},	// CH3
					{4, 48, 5, 49, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 29, 73, 30, 74, 43, 87, -1},	// CH0
					{17, 61, 28, 72, 31, 75, 42, 86, -1},	// CH1
					{18, 62, 27, 71, 32, 76, 41, 85, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 25, 69, 34, 78, 39, 83, -1},	// CH4
					{21, 65, 24, 68, 35, 79, 38, 82, -1},	// CH5
					{22, 66, 23, 67, 36, 80, 37, 81, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, 97, 98, -1},	// CH0
					{89, 96, 99, -1},	// CH1
					{90, 95, 100, -1},	// CH2
					{91, 94, 101, -1},	// CH3
					{92, 93, 102, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
					{103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__SOUND_BOOST__SEPARATE__DIRECTION",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, -1},	// CH0
					{1, 45, -1},	// CH1
					{2, 46, -1},	// CH2
					{3, 47, -1},	// CH3
					{4, 48, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
					{5, 49, -1},	// CH0
					{6, 50, -1},	// CH1
					{7, 51, -1},	// CH2
					{8, 52, -1},	// CH3
					{9, 53, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, -1},	// CH0
					{17, 61, -1},	// CH1
					{18, 62, -1},	// CH2
					{19, 63, -1},	// CH3
					{20, 64, -1},	// CH4
					{21, 65, -1},	// CH5
					{22, 66, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
					{23, 67, -1},	// CH0
					{24, 68, -1},	// CH1
					{25, 69, -1},	// CH2
					{26, 70, -1},	// CH3
					{27, 71, -1},	// CH4
					{28, 72, -1},	// CH5
					{29, 73, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
					{30, 74, -1},	// CH0
					{31, 75, -1},	// CH1
					{32, 76, -1},	// CH2
					{33, 77, -1},	// CH3
					{34, 78, -1},	// CH4
					{35, 79, -1},	// CH5
					{36, 80, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
					{37, 81, -1},	// CH0
					{38, 82, -1},	// CH1
					{39, 83, -1},	// CH2
					{40, 84, -1},	// CH3
					{41, 85, -1},	// CH4
					{42, 86, -1},	// CH5
					{43, 87, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
					{192, -1},	// CH0
					{193, -1},	// CH1
					{194, -1},	// CH2
					{195, -1},	// CH3
					{196, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
					{197, -1},	// CH0
					{198, -1},	// CH1
					{199, -1},	// CH2
					{200, -1},	// CH3
					{201, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
					{202, -1},	// CH0
					{203, -1},	// CH1
					{204, -1},	// CH2
					{205, -1},	// CH3
					{206, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__SOUND_BOOST__SEPARATE__SYMMETRY",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 48, -1},	// CH0
					{1, 47, -1},	// CH1
					{2, 46, -1},	// CH2
					{3, 45, -1},	// CH3
					{4, 44, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
					{5, 53, -1},	// CH0
					{6, 52, -1},	// CH1
					{7, 51, -1},	// CH2
					{8, 50, -1},	// CH3
					{9, 49, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 58, -1},	// CH0
					{12, 57, -1},	// CH1
					{13, 56, -1},	// CH2
					{14, 55, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 66, -1},	// CH0
					{17, 65, -1},	// CH1
					{18, 64, -1},	// CH2
					{19, 63, -1},	// CH3
					{20, 62, -1},	// CH4
					{21, 61, -1},	// CH5
					{22, 60, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
					{23, 73, -1},	// CH0
					{24, 72, -1},	// CH1
					{25, 71, -1},	// CH2
					{26, 70, -1},	// CH3
					{27, 69, -1},	// CH4
					{28, 68, -1},	// CH5
					{29, 67, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
					{30, 80, -1},	// CH0
					{31, 79, -1},	// CH1
					{32, 78, -1},	// CH2
					{33, 77, -1},	// CH3
					{34, 76, -1},	// CH4
					{35, 75, -1},	// CH5
					{36, 74, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
					{37, 87, -1},	// CH0
					{38, 86, -1},	// CH1
					{39, 85, -1},	// CH2
					{40, 84, -1},	// CH3
					{41, 83, -1},	// CH4
					{42, 82, -1},	// CH5
					{43, 81, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
					{192, -1},	// CH0
					{193, -1},	// CH1
					{194, -1},	// CH2
					{195, -1},	// CH3
					{196, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
					{197, -1},	// CH0
					{198, -1},	// CH1
					{199, -1},	// CH2
					{200, -1},	// CH3
					{201, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
					{202, -1},	// CH0
					{203, -1},	// CH1
					{204, -1},	// CH2
					{205, -1},	// CH3
					{206, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__BEAT_NORMAL__SYNC__STRAIGHT",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 5, 49, -1},	// CH0
					{1, 45, 6, 50, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 8, 52, -1},	// CH3
					{4, 48, 9, 53, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 23, 67, 30, 74, 37, 81, -1},	// CH0
					{17, 61, 24, 68, 31, 75, 38, 82, -1},	// CH1
					{18, 62, 25, 69, 32, 76, 39, 83, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 27, 71, 34, 78, 41, 85, -1},	// CH4
					{21, 65, 28, 72, 35, 79, 42, 86, -1},	// CH5
					{22, 66, 29, 73, 36, 80, 43, 87, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__BEAT_NORMAL__SYNC__TWIST",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 9, 53, -1},	// CH0
					{1, 45, 8, 52, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 6, 50, -1},	// CH3
					{4, 48, 5, 49, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 29, 73, 30, 74, 43, 87, -1},	// CH0
					{17, 61, 28, 72, 31, 75, 42, 86, -1},	// CH1
					{18, 62, 27, 71, 32, 76, 41, 85, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 25, 69, 34, 78, 39, 83, -1},	// CH4
					{21, 65, 24, 68, 35, 79, 38, 82, -1},	// CH5
					{22, 66, 23, 67, 36, 80, 37, 81, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__BEAT_BOOST__SYNC__STRAIGHT",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 5, 49, -1},	// CH0
					{1, 45, 6, 50, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 8, 52, -1},	// CH3
					{4, 48, 9, 53, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 23, 67, 30, 74, 37, 81, -1},	// CH0
					{17, 61, 24, 68, 31, 75, 38, 82, -1},	// CH1
					{18, 62, 25, 69, 32, 76, 39, 83, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 27, 71, 34, 78, 41, 85, -1},	// CH4
					{21, 65, 28, 72, 35, 79, 42, 86, -1},	// CH5
					{22, 66, 29, 73, 36, 80, 43, 87, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, 93, 98, -1},	// CH0
					{89, 94, 99, -1},	// CH1
					{90, 95, 100, -1},	// CH2
					{91, 96, 101, -1},	// CH3
					{92, 97, 102, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
					{103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__BEAT_BOOST__SYNC__TWIST",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 9, 53, -1},	// CH0
					{1, 45, 8, 52, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 6, 50, -1},	// CH3
					{4, 48, 5, 49, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 29, 73, 30, 74, 43, 87, -1},	// CH0
					{17, 61, 28, 72, 31, 75, 42, 86, -1},	// CH1
					{18, 62, 27, 71, 32, 76, 41, 85, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 25, 69, 34, 78, 39, 83, -1},	// CH4
					{21, 65, 24, 68, 35, 79, 38, 82, -1},	// CH5
					{22, 66, 23, 67, 36, 80, 37, 81, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, 97, 98, -1},	// CH0
					{89, 96, 99, -1},	// CH1
					{90, 95, 100, -1},	// CH2
					{91, 94, 101, -1},	// CH3
					{92, 93, 102, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
					{103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__BEAT_BOOST__SEPARATE__DIRECTION",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, -1},	// CH0
					{1, 45, -1},	// CH1
					{2, 46, -1},	// CH2
					{3, 47, -1},	// CH3
					{4, 48, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
					{5, 49, -1},	// CH0
					{6, 50, -1},	// CH1
					{7, 51, -1},	// CH2
					{8, 52, -1},	// CH3
					{9, 53, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, -1},	// CH0
					{17, 61, -1},	// CH1
					{18, 62, -1},	// CH2
					{19, 63, -1},	// CH3
					{20, 64, -1},	// CH4
					{21, 65, -1},	// CH5
					{22, 66, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
					{23, 67, -1},	// CH0
					{24, 68, -1},	// CH1
					{25, 69, -1},	// CH2
					{26, 70, -1},	// CH3
					{27, 71, -1},	// CH4
					{28, 72, -1},	// CH5
					{29, 73, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
					{30, 74, -1},	// CH0
					{31, 75, -1},	// CH1
					{32, 76, -1},	// CH2
					{33, 77, -1},	// CH3
					{34, 78, -1},	// CH4
					{35, 79, -1},	// CH5
					{36, 80, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
					{37, 81, -1},	// CH0
					{38, 82, -1},	// CH1
					{39, 83, -1},	// CH2
					{40, 84, -1},	// CH3
					{41, 85, -1},	// CH4
					{42, 86, -1},	// CH5
					{43, 87, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, -1},	// CH0
					{89, -1},	// CH1
					{90, -1},	// CH2
					{91, -1},	// CH3
					{92, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
					{93, -1},	// CH0
					{94, -1},	// CH1
					{95, -1},	// CH2
					{96, -1},	// CH3
					{97, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
					{98, -1},	// CH0
					{99, -1},	// CH1
					{100, -1},	// CH2
					{101, -1},	// CH3
					{102, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
					{103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__BEAT_BOOST__SEPARATE__SYMMETRY",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 48, -1},	// CH0
					{1, 47, -1},	// CH1
					{2, 46, -1},	// CH2
					{3, 45, -1},	// CH3
					{4, 44, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
					{5, 53, -1},	// CH0
					{6, 52, -1},	// CH1
					{7, 51, -1},	// CH2
					{8, 50, -1},	// CH3
					{9, 49, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 58, -1},	// CH0
					{12, 57, -1},	// CH1
					{13, 56, -1},	// CH2
					{14, 55, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 66, -1},	// CH0
					{17, 65, -1},	// CH1
					{18, 64, -1},	// CH2
					{19, 63, -1},	// CH3
					{20, 62, -1},	// CH4
					{21, 61, -1},	// CH5
					{22, 60, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
					{23, 73, -1},	// CH0
					{24, 72, -1},	// CH1
					{25, 71, -1},	// CH2
					{26, 70, -1},	// CH3
					{27, 69, -1},	// CH4
					{28, 68, -1},	// CH5
					{29, 67, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
					{30, 80, -1},	// CH0
					{31, 79, -1},	// CH1
					{32, 78, -1},	// CH2
					{33, 77, -1},	// CH3
					{34, 76, -1},	// CH4
					{35, 75, -1},	// CH5
					{36, 74, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
					{37, 87, -1},	// CH0
					{38, 86, -1},	// CH1
					{39, 85, -1},	// CH2
					{40, 84, -1},	// CH3
					{41, 83, -1},	// CH4
					{42, 82, -1},	// CH5
					{43, 81, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, -1},	// CH0
					{89, -1},	// CH1
					{90, -1},	// CH2
					{91, -1},	// CH3
					{92, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
					{93, -1},	// CH0
					{94, -1},	// CH1
					{95, -1},	// CH2
					{96, -1},	// CH3
					{97, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
					{98, -1},	// CH0
					{99, -1},	// CH1
					{100, -1},	// CH2
					{101, -1},	// CH3
					{102, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
					{103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__FLYWHEEL_NORMAL__SYNC__STRAIGHT",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 5, 49, -1},	// CH0
					{1, 45, 6, 50, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 8, 52, -1},	// CH3
					{4, 48, 9, 53, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 23, 67, 30, 74, 37, 81, -1},	// CH0
					{17, 61, 24, 68, 31, 75, 38, 82, -1},	// CH1
					{18, 62, 25, 69, 32, 76, 39, 83, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 27, 71, 34, 78, 41, 85, -1},	// CH4
					{21, 65, 28, 72, 35, 79, 42, 86, -1},	// CH5
					{22, 66, 29, 73, 36, 80, 43, 87, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, 93, 98, -1},	// CH0
					{89, 94, 99, -1},	// CH1
					{90, 95, 100, -1},	// CH2
					{91, 96, 101, -1},	// CH3
					{92, 97, 102, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
					{103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__FLYWHEEL_NORMAL__SYNC__TWIST",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 9, 53, -1},	// CH0
					{1, 45, 8, 52, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 6, 50, -1},	// CH3
					{4, 48, 5, 49, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 29, 73, 30, 74, 43, 87, -1},	// CH0
					{17, 61, 28, 72, 31, 75, 42, 86, -1},	// CH1
					{18, 62, 27, 71, 32, 76, 41, 85, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 25, 69, 34, 78, 39, 83, -1},	// CH4
					{21, 65, 24, 68, 35, 79, 38, 82, -1},	// CH5
					{22, 66, 23, 67, 36, 80, 37, 81, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, 97, 98, -1},	// CH0
					{89, 96, 99, -1},	// CH1
					{90, 95, 100, -1},	// CH2
					{91, 94, 101, -1},	// CH3
					{92, 93, 102, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
					{103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__FLYWHEEL_BOOST__SEPARATE__DIRECTION",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, -1},	// CH0
					{1, 45, -1},	// CH1
					{2, 46, -1},	// CH2
					{3, 47, -1},	// CH3
					{4, 48, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
					{5, 49, -1},	// CH0
					{6, 50, -1},	// CH1
					{7, 51, -1},	// CH2
					{8, 52, -1},	// CH3
					{9, 53, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, -1},	// CH0
					{17, 61, -1},	// CH1
					{18, 62, -1},	// CH2
					{19, 63, -1},	// CH3
					{20, 64, -1},	// CH4
					{21, 65, -1},	// CH5
					{22, 66, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
					{23, 67, -1},	// CH0
					{24, 68, -1},	// CH1
					{25, 69, -1},	// CH2
					{26, 70, -1},	// CH3
					{27, 71, -1},	// CH4
					{28, 72, -1},	// CH5
					{29, 73, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
					{30, 74, -1},	// CH0
					{31, 75, -1},	// CH1
					{32, 76, -1},	// CH2
					{33, 77, -1},	// CH3
					{34, 78, -1},	// CH4
					{35, 79, -1},	// CH5
					{36, 80, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
					{37, 81, -1},	// CH0
					{38, 82, -1},	// CH1
					{39, 83, -1},	// CH2
					{40, 84, -1},	// CH3
					{41, 85, -1},	// CH4
					{42, 86, -1},	// CH5
					{43, 87, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, -1},	// CH0
					{89, -1},	// CH1
					{90, -1},	// CH2
					{91, -1},	// CH3
					{92, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
					{93, -1},	// CH0
					{94, -1},	// CH1
					{95, -1},	// CH2
					{96, -1},	// CH3
					{97, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
					{98, -1},	// CH0
					{99, -1},	// CH1
					{100, -1},	// CH2
					{101, -1},	// CH3
					{102, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
					{103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
					{192, -1},	// CH0
					{193, -1},	// CH1
					{194, -1},	// CH2
					{195, -1},	// CH3
					{196, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
					{197, -1},	// CH0
					{198, -1},	// CH1
					{199, -1},	// CH2
					{200, -1},	// CH3
					{201, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
					{202, -1},	// CH0
					{203, -1},	// CH1
					{204, -1},	// CH2
					{205, -1},	// CH3
					{206, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP0__FLYWHEEL_BOOST__SEPARATE__SYMMETRY",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 48, -1},	// CH0
					{1, 47, -1},	// CH1
					{2, 46, -1},	// CH2
					{3, 45, -1},	// CH3
					{4, 44, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
					{5, 53, -1},	// CH0
					{6, 52, -1},	// CH1
					{7, 51, -1},	// CH2
					{8, 50, -1},	// CH3
					{9, 49, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 58, -1},	// CH0
					{12, 57, -1},	// CH1
					{13, 56, -1},	// CH2
					{14, 55, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 66, -1},	// CH0
					{17, 65, -1},	// CH1
					{18, 64, -1},	// CH2
					{19, 63, -1},	// CH3
					{20, 62, -1},	// CH4
					{21, 61, -1},	// CH5
					{22, 60, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
					{23, 73, -1},	// CH0
					{24, 72, -1},	// CH1
					{25, 71, -1},	// CH2
					{26, 70, -1},	// CH3
					{27, 69, -1},	// CH4
					{28, 68, -1},	// CH5
					{29, 67, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
					{30, 80, -1},	// CH0
					{31, 79, -1},	// CH1
					{32, 78, -1},	// CH2
					{33, 77, -1},	// CH3
					{34, 76, -1},	// CH4
					{35, 75, -1},	// CH5
					{36, 74, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
					{37, 87, -1},	// CH0
					{38, 86, -1},	// CH1
					{39, 85, -1},	// CH2
					{40, 84, -1},	// CH3
					{41, 83, -1},	// CH4
					{42, 82, -1},	// CH5
					{43, 81, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, -1},	// CH0
					{89, -1},	// CH1
					{90, -1},	// CH2
					{91, -1},	// CH3
					{92, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
					{93, -1},	// CH0
					{94, -1},	// CH1
					{95, -1},	// CH2
					{96, -1},	// CH3
					{97, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
					{98, -1},	// CH0
					{99, -1},	// CH1
					{100, -1},	// CH2
					{101, -1},	// CH3
					{102, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
					{103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
					{192, -1},	// CH0
					{193, -1},	// CH1
					{194, -1},	// CH2
					{195, -1},	// CH3
					{196, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
					{197, -1},	// CH0
					{198, -1},	// CH1
					{199, -1},	// CH2
					{200, -1},	// CH3
					{201, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
					{202, -1},	// CH0
					{203, -1},	// CH1
					{204, -1},	// CH2
					{205, -1},	// CH3
					{206, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP1__SOUND_NORMAL__SYNC__STRAIGHT",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 5, 49, -1},	// CH0
					{1, 45, 6, 50, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 8, 52, -1},	// CH3
					{4, 48, 9, 53, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 23, 67, 30, 74, 37, 81, -1},	// CH0
					{17, 61, 24, 68, 31, 75, 38, 82, -1},	// CH1
					{18, 62, 25, 69, 32, 76, 39, 83, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 27, 71, 34, 78, 41, 85, -1},	// CH4
					{21, 65, 28, 72, 35, 79, 42, 86, -1},	// CH5
					{22, 66, 29, 73, 36, 80, 43, 87, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP1__SOUND_NORMAL__SYNC__TWIST",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 9, 53, -1},	// CH0
					{1, 45, 8, 52, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 6, 50, -1},	// CH3
					{4, 48, 5, 49, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 29, 73, 30, 74, 43, 87, -1},	// CH0
					{17, 61, 28, 72, 31, 75, 42, 86, -1},	// CH1
					{18, 62, 27, 71, 32, 76, 41, 85, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 25, 69, 34, 78, 39, 83, -1},	// CH4
					{21, 65, 24, 68, 35, 79, 38, 82, -1},	// CH5
					{22, 66, 23, 67, 36, 80, 37, 81, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP1__FLYWHEEL_NORMAL__SYNC__STRAIGHT",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 5, 49, -1},	// CH0
					{1, 45, 6, 50, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 8, 52, -1},	// CH3
					{4, 48, 9, 53, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 23, 67, 30, 74, 37, 81, -1},	// CH0
					{17, 61, 24, 68, 31, 75, 38, 82, -1},	// CH1
					{18, 62, 25, 69, 32, 76, 39, 83, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 27, 71, 34, 78, 41, 85, -1},	// CH4
					{21, 65, 28, 72, 35, 79, 42, 86, -1},	// CH5
					{22, 66, 29, 73, 36, 80, 43, 87, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP1__FLYWHEEL_NORMAL__SYNC__TWIST",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 44, 9, 53, -1},	// CH0
					{1, 45, 8, 52, -1},	// CH1
					{2, 46, 7, 51, -1},	// CH2
					{3, 47, 6, 50, -1},	// CH3
					{4, 48, 5, 49, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
					{11, 55, -1},	// CH0
					{12, 56, -1},	// CH1
					{13, 57, -1},	// CH2
					{14, 58, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
					{16, 60, 29, 73, 30, 74, 43, 87, -1},	// CH0
					{17, 61, 28, 72, 31, 75, 42, 86, -1},	// CH1
					{18, 62, 27, 71, 32, 76, 41, 85, -1},	// CH2
					{19, 63, 26, 70, 33, 77, 40, 84, -1},	// CH3
					{20, 64, 25, 69, 34, 78, 39, 83, -1},	// CH4
					{21, 65, 24, 68, 35, 79, 38, 82, -1},	// CH5
					{22, 66, 23, 67, 36, 80, 37, 81, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
	{					
		"GP2__FLYWHEEL_BOOST__SEPARATE",				
		{				
			{ // Block	wall 0 RGB		
				{ // LogicalCh:Physical ch set		
					{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 1 RGB		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall center		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 2		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 3		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 4		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	wall 5		
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_WallWasher,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0		
				{ // LogicalCh:Physical ch set		
					{88, -1},	// CH0
					{89, -1},	// CH1
					{90, -1},	// CH2
					{91, -1},	// CH3
					{92, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1		
				{ // LogicalCh:Physical ch set		
					{93, -1},	// CH0
					{94, -1},	// CH1
					{95, -1},	// CH2
					{96, -1},	// CH3
					{97, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2		
				{ // LogicalCh:Physical ch set		
					{98, -1},	// CH0
					{99, -1},	// CH1
					{100, -1},	// CH2
					{101, -1},	// CH3
					{102, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 3		
				{ // LogicalCh:Physical ch set		
					{103, -1},	// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_1,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_PANEL,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 0 strobe		
				{ // LogicalCh:Physical ch set		
					{192, -1},	// CH0
					{193, -1},	// CH1
					{194, -1},	// CH2
					{195, -1},	// CH3
					{196, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 1 strobe		
				{ // LogicalCh:Physical ch set		
					{197, -1},	// CH0
					{198, -1},	// CH1
					{199, -1},	// CH2
					{200, -1},	// CH3
					{201, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // Block	ball 2 strobe		
				{ // LogicalCh:Physical ch set		
					{202, -1},	// CH0
					{203, -1},	// CH1
					{204, -1},	// CH2
					{205, -1},	// CH3
					{206, -1},	// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_5,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__FIX_LUM_STROBE,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
};						
						
const int NUM_GROUPTYPES_INTANGIBLE = sizeof(BlockGrouping_InTangible) / sizeof(BlockGrouping_InTangible[0]);						


BLOCK_GROUP BlockGrouping_Tangible[] = {						
	{					
		"TANGIBLE_GP__DUMMY",				
		{				
			{ // END			
				{ // LogicalCh:Physical ch set		
						// CH0
						// CH1
						// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				NULL,		
				NULL,		
				false,	// b_PanTilt	
				NULL,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_RGB,	
				},		
				{ // BpInfo_Pan		
					DEVICE_CH_TYPE__MOV_ANGLE_PAN,	
				},		
				{ // BpInfo_Tilt		
					DEVICE_CH_TYPE__MOV_ANGLE_TILT,	
				},		
			},			
		},				
	},					
};						
						
const int NUM_GROUPTYPES_TANGIBLE = sizeof(BlockGrouping_Tangible) / sizeof(BlockGrouping_Tangible[0]);						

/************************************************************************************************************************/
} // namespace SPACE_LIGHT{

