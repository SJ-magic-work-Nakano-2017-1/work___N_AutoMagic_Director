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
		MAX_CHS_IN_1LOGICAL_CH = 100,
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

/************************************************************
šššššššššššššššššššššššššššššš
Copy from Excel below.
šššššššššššššššššššššššššššššš
************************************************************/
BLOCK_GROUP BlockGrouping_InTangible[] = {						
	{					
		"GP0__NOSOUND_NORMAL__SEPARATE__SYMMETRY",				
		{				
			{ // Block	Box Fix RGB 4ch		
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{11, 23, -1},	// CH0
					{12, 22, -1},	// CH1
					{13, 21, -1},	// CH2
					{14, 20, -1},	// CH3
					{15, 19, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{16, 26, -1},	// CH0
					{17, 25, -1},	// CH1
					{18, 24, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
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
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
		"GP0__SOUND_NORMAL__SEPARATE__DIRECTION",				
		{				
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{7, -1},	// CH0
					{8, -1},	// CH1
					{9, -1},	// CH2
					{10, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{11, 19, -1},	// CH0
					{12, 20, -1},	// CH1
					{13, 21, -1},	// CH2
					{14, 22, -1},	// CH3
					{15, 23, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{16, 24, -1},	// CH0
					{17, 25, -1},	// CH1
					{18, 26, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{27, 30, -1},	// CH0
					{28, 31, -1},	// CH1
					{29, 32, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
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
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
		"GP0__SOUND_NORMAL__SEPARATE__SYMMETRY",				
		{				
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{7, -1},	// CH0
					{8, -1},	// CH1
					{9, -1},	// CH2
					{10, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{11, 23, -1},	// CH0
					{12, 22, -1},	// CH1
					{13, 21, -1},	// CH2
					{14, 20, -1},	// CH3
					{15, 19, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{16, 26, -1},	// CH0
					{17, 25, -1},	// CH1
					{18, 24, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{27, 32, -1},	// CH0
					{28, 31, -1},	// CH1
					{29, 30, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
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
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
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
			{ // Block	Upper x LR Fix RGB 5ch		
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{40, -1},	// CH0
					{41, -1},	// CH1
					{42, -1},	// CH2
					{43, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{44, 52, -1},	// CH0
					{45, 53, -1},	// CH1
					{46, 54, -1},	// CH2
					{47, 55, -1},	// CH3
					{48, 56, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{49, 57, -1},	// CH0
					{50, 58, -1},	// CH1
					{51, 59, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{60, 63, -1},	// CH0
					{61, 64, -1},	// CH1
					{62, 65, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
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
			{ // Block	Upper x LR Fix RGB 5ch		
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{40, -1},	// CH0
					{41, -1},	// CH1
					{42, -1},	// CH2
					{43, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{44, 56, -1},	// CH0
					{45, 55, -1},	// CH1
					{46, 54, -1},	// CH2
					{47, 53, -1},	// CH3
					{48, 52, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{49, 59, -1},	// CH0
					{50, 58, -1},	// CH1
					{51, 57, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{60, 65, -1},	// CH0
					{61, 64, -1},	// CH1
					{62, 63, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
		"GP0__BEAT_NORMAL__SEPARATE__DIRECTION",				
		{				
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{7, -1},	// CH0
					{8, -1},	// CH1
					{9, -1},	// CH2
					{10, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{11, 19, -1},	// CH0
					{12, 20, -1},	// CH1
					{13, 21, -1},	// CH2
					{14, 22, -1},	// CH3
					{15, 23, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{27, 30, -1},	// CH0
					{28, 31, -1},	// CH1
					{29, 32, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
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
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{49, 57, -1},	// CH0
					{50, 58, -1},	// CH1
					{51, 59, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
		"GP0__BEAT_NORMAL__SEPARATE__SYMMETRY",				
		{				
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{7, -1},	// CH0
					{8, -1},	// CH1
					{9, -1},	// CH2
					{10, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{11, 23, -1},	// CH0
					{12, 22, -1},	// CH1
					{13, 21, -1},	// CH2
					{14, 20, -1},	// CH3
					{15, 19, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{27, 32, -1},	// CH0
					{28, 31, -1},	// CH1
					{29, 30, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
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
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{49, 59, -1},	// CH0
					{50, 58, -1},	// CH1
					{51, 57, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{7, -1},	// CH0
					{8, -1},	// CH1
					{9, -1},	// CH2
					{10, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
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
			{ // Block	Upper x LR Fix RGB 5ch		
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
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
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{44, 52, -1},	// CH0
					{45, 53, -1},	// CH1
					{46, 54, -1},	// CH2
					{47, 55, -1},	// CH3
					{48, 56, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{49, 57, -1},	// CH0
					{50, 58, -1},	// CH1
					{51, 59, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{60, 63, -1},	// CH0
					{61, 64, -1},	// CH1
					{62, 65, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{7, -1},	// CH0
					{8, -1},	// CH1
					{9, -1},	// CH2
					{10, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
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
			{ // Block	Upper x LR Fix RGB 5ch		
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
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
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{44, 56, -1},	// CH0
					{45, 55, -1},	// CH1
					{46, 54, -1},	// CH2
					{47, 53, -1},	// CH3
					{48, 52, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{49, 59, -1},	// CH0
					{50, 58, -1},	// CH1
					{51, 57, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{60, 65, -1},	// CH0
					{61, 64, -1},	// CH1
					{62, 63, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
		"GP0__FLYWHEEL_NORMAL__SEPARATE__DIRECTION",				
		{				
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{7, -1},	// CH0
					{8, -1},	// CH1
					{9, -1},	// CH2
					{10, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{11, 19, -1},	// CH0
					{12, 20, -1},	// CH1
					{13, 21, -1},	// CH2
					{14, 22, -1},	// CH3
					{15, 23, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{16, 24, -1},	// CH0
					{17, 25, -1},	// CH1
					{18, 26, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{27, 30, -1},	// CH0
					{28, 31, -1},	// CH1
					{29, 32, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
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
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{44, 52, -1},	// CH0
					{45, 53, -1},	// CH1
					{46, 54, -1},	// CH2
					{47, 55, -1},	// CH3
					{48, 56, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
		"GP0__FLYWHEEL_NORMAL__SEPARATE__SYMMETRY",				
		{				
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{7, -1},	// CH0
					{8, -1},	// CH1
					{9, -1},	// CH2
					{10, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{11, 23, -1},	// CH0
					{12, 22, -1},	// CH1
					{13, 21, -1},	// CH2
					{14, 20, -1},	// CH3
					{15, 19, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{16, 26, -1},	// CH0
					{17, 25, -1},	// CH1
					{18, 24, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{27, 32, -1},	// CH0
					{28, 31, -1},	// CH1
					{29, 30, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
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
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{44, 56, -1},	// CH0
					{45, 55, -1},	// CH1
					{46, 54, -1},	// CH2
					{47, 53, -1},	// CH3
					{48, 52, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{7, -1},	// CH0
					{8, -1},	// CH1
					{9, -1},	// CH2
					{10, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{11, 19, -1},	// CH0
					{12, 20, -1},	// CH1
					{13, 21, -1},	// CH2
					{14, 22, -1},	// CH3
					{15, 23, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{27, 30, -1},	// CH0
					{28, 31, -1},	// CH1
					{29, 32, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{40, -1},	// CH0
					{41, -1},	// CH1
					{42, -1},	// CH2
					{43, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{44, 52, -1},	// CH0
					{45, 53, -1},	// CH1
					{46, 54, -1},	// CH2
					{47, 55, -1},	// CH3
					{48, 56, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{49, 57, -1},	// CH0
					{50, 58, -1},	// CH1
					{51, 59, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{60, 63, -1},	// CH0
					{61, 64, -1},	// CH1
					{62, 65, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{7, -1},	// CH0
					{8, -1},	// CH1
					{9, -1},	// CH2
					{10, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{11, 23, -1},	// CH0
					{12, 22, -1},	// CH1
					{13, 21, -1},	// CH2
					{14, 20, -1},	// CH3
					{15, 19, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
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
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{27, 32, -1},	// CH0
					{28, 31, -1},	// CH1
					{29, 30, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_RGB,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	Box Fix RGB 4ch		
				{ // LogicalCh:Physical ch set		
					{40, -1},	// CH0
					{41, -1},	// CH1
					{42, -1},	// CH2
					{43, -1},	// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_4,	// Bp_Pattern	
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
			{ // Block	Upper x LR Fix RGB 5ch		
				{ // LogicalCh:Physical ch set		
					{44, 56, -1},	// CH0
					{45, 55, -1},	// CH1
					{46, 54, -1},	// CH2
					{47, 53, -1},	// CH3
					{48, 52, -1},	// CH4
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
			{ // Block	Lower x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{49, 59, -1},	// CH0
					{50, 58, -1},	// CH1
					{51, 57, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
			{ // Block	SideTable x LR Fix RGB 3ch		
				{ // LogicalCh:Physical ch set		
					{60, 65, -1},	// CH0
					{61, 64, -1},	// CH1
					{62, 63, -1},	// CH2
						// CH3
						// CH4
						// CH5
						// CH6
					{-1},	
				},		
				Weight_PlayMode_Fix_Strobe,		
				Weight_PlayMode_PanTilt,		
				false,	// b_PanTilt	
				Bp_3,	// Bp_Pattern	
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
		"GP1__SOUND_BOOST",				
		{				
			{ // Block	LR Fix RGB 2ch		
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
				Bp_2,	// Bp_Pattern	
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
			{ // Block	SideTable Fix RGB 1ch		
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
			{ // Block	LR Fix Strobe 2ch		
				{ // LogicalCh:Physical ch set		
					{40, 41, 44, 45, 46, 47, 48, 49, 50, 51, -1},	// CH0
					{42, 43, 52, 53, 54, 55, 56, 57, 58, 59, -1},	// CH1
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
				Bp_2,	// Bp_Pattern	
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
			{ // Block	SideTable Fix Strobe 1ch		
				{ // LogicalCh:Physical ch set		
					{60, 61, 62, 63, 64, 65, -1},	// CH0
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
				Bp_1,	// Bp_Pattern	
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
		"GP1__BEAT_NORMAL",				
		{				
			{ // Block	LR Fix RGB 2ch		
				{ // LogicalCh:Physical ch set		
					{7, 8, 11, 12, 13, 14, 15, 16, 17, 18, -1},	// CH0
					{9, 10, 19, 20, 21, 22, 23, 24, 25, 26, -1},	// CH1
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
				Bp_2,	// Bp_Pattern	
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
			{ // Block	SideTable Fix RGB 1ch		
				{ // LogicalCh:Physical ch set		
					{27, 28, 29, 30, 31, 32, -1},	// CH0
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
			{ // Block	LR Fix Strobe 2ch		
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
				Bp_2,	// Bp_Pattern	
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
			{ // Block	SideTable Fix Strobe 1ch		
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
				Bp_1,	// Bp_Pattern	
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
		"GP1__FLYWHEEL_NORMAL",				
		{				
			{ // Block	LR Fix RGB 2ch		
				{ // LogicalCh:Physical ch set		
					{7, 8, 11, 12, 13, 14, 15, 16, 17, 18, -1},	// CH0
					{9, 10, 19, 20, 21, 22, 23, 24, 25, 26, -1},	// CH1
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
				Bp_2,	// Bp_Pattern	
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
			{ // Block	SideTable Fix RGB 1ch		
				{ // LogicalCh:Physical ch set		
					{27, 28, 29, 30, 31, 32, -1},	// CH0
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
			{ // Block	LR Fix Strobe 2ch		
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
				Bp_2,	// Bp_Pattern	
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
			{ // Block	SideTable Fix Strobe 1ch		
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
				Bp_1,	// Bp_Pattern	
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
		"GP1__FLYWHEEL_BOOST__RGB",				
		{				
			{ // Block	LR Fix RGB 2ch		
				{ // LogicalCh:Physical ch set		
					{7, 8, 11, 12, 13, 14, 15, 16, 17, 18, -1},	// CH0
					{9, 10, 19, 20, 21, 22, 23, 24, 25, 26, -1},	// CH1
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
				Bp_2,	// Bp_Pattern	
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
			{ // Block	SideTable Fix RGB 1ch		
				{ // LogicalCh:Physical ch set		
					{27, 28, 29, 30, 31, 32, -1},	// CH0
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
				Bp_1,	// Bp_Pattern	
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
			{ // Block	LR Fix Strobe 2ch		
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
				Bp_2,	// Bp_Pattern	
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
			{ // Block	SideTable Fix Strobe 1ch		
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
				Bp_1,	// Bp_Pattern	
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
		"GP1__FLYWHEEL_BOOST__W",				
		{				
			{ // Block	LR Fix RGB 2ch		
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
				Bp_2,	// Bp_Pattern	
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
			{ // Block	SideTable Fix RGB 1ch		
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
				Bp_1,	// Bp_Pattern	
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
			{ // Block	LR Fix Strobe 2ch		
				{ // LogicalCh:Physical ch set		
					{40, 41, 44, 45, 46, 47, 48, 49, 50, 51, -1},	// CH0
					{42, 43, 52, 53, 54, 55, 56, 57, 58, 59, -1},	// CH1
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
				Bp_2,	// Bp_Pattern	
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
			{ // Block	SideTable Fix Strobe 1ch		
				{ // LogicalCh:Physical ch set		
					{60, 61, 62, 63, 64, 65, -1},	// CH0
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
				Bp_1,	// Bp_Pattern	
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
		"GP2__SOUND_BOOST",				
		{				
			{ // Block	All Fix RGB 1ch		
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
			{ // Block	All Fix Strobe 1ch		
				{ // LogicalCh:Physical ch set		
					{40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, -1},	// CH0
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
				Bp_1,	// Bp_Pattern	
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
		"GP2__FLYWHEEL_NORMAL",				
		{				
			{ // Block	All Fix RGB 1ch		
				{ // LogicalCh:Physical ch set		
					{7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, -1},	// CH0
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
			{ // Block	All Fix Strobe 1ch		
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
				Bp_1,	// Bp_Pattern	
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
		"GP2__FLYWHEEL_BOOST_RGB",				
		{				
			{ // Block	All Fix RGB 1ch		
				{ // LogicalCh:Physical ch set		
					{7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, -1},	// CH0
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
				Bp_1,	// Bp_Pattern	
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
			{ // Block	All Fix Strobe 1ch		
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
				Bp_1,	// Bp_Pattern	
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
		"GP2__FLYWHEEL_BOOST_W",				
		{				
			{ // Block	All Fix RGB 1ch		
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
				Bp_1,	// Bp_Pattern	
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
			{ // Block	All Fix Strobe 1ch		
				{ // LogicalCh:Physical ch set		
					{40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, -1},	// CH0
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
				Bp_1,	// Bp_Pattern	
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
		"TANGIBLE_GP0__NOSOUND",				
		{				
			{ // Block	Center moving RGB 7ch		
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
				Weight_PlayMode_Mov_RGB,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
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
			{ // Block	Center moving Strobe 7ch		
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
				Weight_PlayMode_Mov_Strobe,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_STROBE,	
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
		"TANGIBLE_GP0__SOUND",				
		{				
			{ // Block	Center moving RGB 7ch		
				{ // LogicalCh:Physical ch set		
					{0, -1},	// CH0
					{1, -1},	// CH1
					{2, -1},	// CH2
					{3, -1},	// CH3
					{4, -1},	// CH4
					{5, -1},	// CH5
					{6, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_Mov_RGB,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
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
			{ // Block	Center moving Strobe 7ch		
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
				Weight_PlayMode_Mov_Strobe,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_STROBE,	
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
		"TANGIBLE_GP0__BEAT_NORMAL",				
		{				
			{ // Block	Center moving RGB 7ch		
				{ // LogicalCh:Physical ch set		
					{0, -1},	// CH0
					{1, -1},	// CH1
					{2, -1},	// CH2
					{3, -1},	// CH3
					{4, -1},	// CH4
					{5, -1},	// CH5
					{6, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_Mov_RGB,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
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
			{ // Block	Center moving Strobe 7ch		
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
				Weight_PlayMode_Mov_Strobe,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_STROBE,	
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
		"TANGIBLE_GP0__BEAT_BOOST",				
		{				
			{ // Block	Center moving RGB 7ch		
				{ // LogicalCh:Physical ch set		
					{0, -1},	// CH0
					{1, -1},	// CH1
					{2, -1},	// CH2
					{3, -1},	// CH3
					{4, -1},	// CH4
					{5, -1},	// CH5
					{6, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_Mov_RGB,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
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
			{ // Block	Center moving Strobe 7ch		
				{ // LogicalCh:Physical ch set		
					{33, -1},	// CH0
					{34, -1},	// CH1
					{35, -1},	// CH2
					{36, -1},	// CH3
					{37, -1},	// CH4
					{38, -1},	// CH5
					{39, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_Mov_Strobe,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_STROBE,	
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
		"TANGIBLE_GP0__FLYWHEEL_NORMAL",				
		{				
			{ // Block	Center moving RGB 7ch		
				{ // LogicalCh:Physical ch set		
					{0, -1},	// CH0
					{1, -1},	// CH1
					{2, -1},	// CH2
					{3, -1},	// CH3
					{4, -1},	// CH4
					{5, -1},	// CH5
					{6, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_Mov_RGB,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
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
			{ // Block	Center moving Strobe 7ch		
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
				Weight_PlayMode_Mov_Strobe,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_STROBE,	
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
		"TANGIBLE_GP0__FLYWHEEL_BOOST",				
		{				
			{ // Block	Center moving RGB 7ch		
				{ // LogicalCh:Physical ch set		
					{0, -1},	// CH0
					{1, -1},	// CH1
					{2, -1},	// CH2
					{3, -1},	// CH3
					{4, -1},	// CH4
					{5, -1},	// CH5
					{6, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_Mov_RGB,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
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
			{ // Block	Center moving Strobe 7ch		
				{ // LogicalCh:Physical ch set		
					{33, -1},	// CH0
					{34, -1},	// CH1
					{35, -1},	// CH2
					{36, -1},	// CH3
					{37, -1},	// CH4
					{38, -1},	// CH5
					{39, -1},	// CH6
					{-1},	
				},		
				Weight_PlayMode_Mov_Strobe,		
				Weight_PlayMode_PanTilt,		
				true,	// b_PanTilt	
				Bp_7,	// Bp_Pattern	
				{ // BpInfo_Luminance		
					DEVICE_CH_TYPE__MOV_LUM_STROBE,	
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
						
const int NUM_GROUPTYPES_TANGIBLE = sizeof(BlockGrouping_Tangible) / sizeof(BlockGrouping_Tangible[0]);						


/************************************************************************************************************************/
} // namespace SPACE_LIGHT{

