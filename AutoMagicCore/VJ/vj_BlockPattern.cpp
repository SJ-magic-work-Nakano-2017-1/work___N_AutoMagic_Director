/************************************************************
// test code
// check if "StartPatternId_Candidate" is correct in all the Bp_x class object.
int cal_Num_StartPatternId_Candidate(BLOCK_PATTERN BlockPattern)
{
	int i;
	for(i = 0; BlockPattern.pShortPattern[i] != NULL; i++){
	}
	
	return i - 1;
}

void VJ::test()
{
	for(int i = 0; vjBp_1[i].pShortPattern[0] != NULL; i++){
		int StartPatternId_Candidate_caled = cal_Num_StartPatternId_Candidate(vjBp_1[i]);
		if(StartPatternId_Candidate_caled < vjBp_1[i].StartPatternId_Candidate){
			printf("Error in:Bp_1[%d]\n", i);
		}
	}
}
************************************************************/
	

/************************************************************
// test code

// printout All Block pattern name
void VJ::test()
{
	FILE* fp;
	
	fp = fopen("../../../Bp_1.txt", "w");
	for(int i = 0; strcmp(vjBp_1[i].name, "BP_END") != 0; i++ ){
		fprintf_Log_forTestCode(fp, "%s\n", vjBp_1[i].name);
	}
	fclose(fp);
}
************************************************************/

/************************************************************
// test code
// print out : DeviceType/State/PlayMode/BoostMode ごと : BlockPattern候補と選択される確率
// 各Patternが、狙った所に候補として挙がっていることを確認

void VJ::test()
{
	enum{
		BUF_SIZE = 2000,
	};
	
	const BLOCK_PATTERN *Bp_Pattern = &vjBp_1[0];
	char LogFileName[BUF_SIZE];
	sprintf(LogFileName, "../../../Bp_%d.txt", 1);
	
	int NumPatterns = get_num_PatternTypes_in_Bp(Bp_Pattern);
	
	
	FILE* fp;
	fp = fopen(LogFileName, "w");
	
	for(int DeviceChType = VJ_ALPHA_CH_TYPE__MOV_0_12; DeviceChType < int(NUM_VJ_ALPHA_CH_TYPE); DeviceChType++){
		fprintf_Log_forTestCode(fp, "--------------------------------------------------\n");
		for(int State = STATE_NOSOUND; State < int(NUM_STATES); State++){
			for(int PlayMode = BEAT_PROPULSION; PlayMode < int(NUM_PLAYMODES); PlayMode++){
				for(int BoostMode = BOOSTMODE_NORMAL; BoostMode < int(NUM_BOOSTMODE); BoostMode++){
					
					int TotalWeight = 0;
					for(int i = 0; i < NumPatterns; i++){
						TotalWeight += Bp_Pattern[i].Weight[DeviceChType][State][PlayMode][BoostMode];
					}
					
					// 
					switch(DeviceChType){
						case VJ_ALPHA_CH_TYPE__MOV_0_12:		fprintf_Log_forTestCode(fp, "mov_0_12 ");	break;
						case VJ_ALPHA_CH_TYPE__MOV_1_2:			fprintf_Log_forTestCode(fp, "mov_1_2 ");	break;
						case VJ_ALPHA_CH_TYPE__INDICATOR:		fprintf_Log_forTestCode(fp, "indicator ");	break;
						case VJ_ALPHA_CH_TYPE__PARTICLE:		fprintf_Log_forTestCode(fp, "particle ");	break;
						case VJ_ALPHA_CH_TYPE__STROBE:			fprintf_Log_forTestCode(fp, "strobe ");		break;
					}
					
					switch(State){
						case STATE_NOSOUND:			fprintf_Log_forTestCode(fp, "NOSOUND ");		break;
						case STATE_SOUND:			fprintf_Log_forTestCode(fp, "SOUND ");			break;
						case STATE_SOUND_DROP:		fprintf_Log_forTestCode(fp, "SOUNDDROP ");		break;
						case STATE_BEAT_IN:			fprintf_Log_forTestCode(fp, "BEATIN ");			break;
						case STATE_BEAT_IN_DROP:	fprintf_Log_forTestCode(fp, "BEATINDROP ");		break;
						case STATE_FLYWHEEL:		fprintf_Log_forTestCode(fp, "FLYWHEEL ");		break;
						case STATE_FLYWHEEL_DROP:	fprintf_Log_forTestCode(fp, "FLYWHEELDROP ");	break;
					}
					
					switch(PlayMode){
						case BEAT_PROPULSION:	fprintf_Log_forTestCode(fp, "BEAT_PROPULSION ");	break;
						case SELF_PROPULSION:	fprintf_Log_forTestCode(fp, "SELF_PROPULSION ");	break;
					}
					
					switch(BoostMode){
						case BOOSTMODE_NORMAL:	fprintf_Log_forTestCode(fp, "NORMAL ");	break;
						case BOOSTMODE_BOOST:	fprintf_Log_forTestCode(fp, "BOOST ");	break;
					}
					
					// 
					fprintf_Log_forTestCode(fp, "\n");
					if(TotalWeight == 0){
						fprintf_Log_forTestCode(fp, "\tXXXXX no chance to select pattern XXXXX\n");
					}else{
						for(int i = 0; i < NumPatterns; i++){
							if(Bp_Pattern[i].Weight[DeviceChType][State][PlayMode][BoostMode]){
								fprintf_Log_forTestCode(fp, "\t%-50s\t%.1f[%%]\n", Bp_Pattern[i].name, double(Bp_Pattern[i].Weight[DeviceChType][State][PlayMode][BoostMode]) * 100 / TotalWeight);
							}
						}
					}
					fprintf_Log_forTestCode(fp, "\n");
				}
			}
		}
	}
	
	fclose(fp);
}
************************************************************/


/************************************************************
************************************************************/
#include <stdio.h>

#include "vj_ShortPattern.h"
#include "vj_BlockPattern.h"



/************************************************************************************************************************/
namespace SPACE_VJ{



/************************************************************
Block Pattern data

// Still -----------------------------------------------------------------------------------------------------------------------
// Sin-----------------------------------------------------------------------------------------------------------------------------
// Flash Bl-----------------------------------------------------------------------------------------------------------------------------
// Strobe-----------------------------------------------------------------------------------------------------------------------------
// Strobe BL-----------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------

★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
Copy from Excel below.
★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
************************************************************/
const struct BLOCK_PATTERN vjBp_1[] = {																																																																				
	// Still -------------------------------------------------------------------------------------------------------------------																																																																			
	{	"VBP_1_STILL__OFF",																																																																		
		1	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__const_Zero	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	60	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	5	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
	{	"VBP_1_STILL__ON",																																																																		
		1	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__const_Max	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	15	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	7	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
	{	"VBP_1_STILL__ON_OFF",																																																																		
		1	,	// Speed																																																																
		1	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__const_Max	,																																																															
				FUNC_SP_VJ::FuncSp__const_Zero	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	3	,	3	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
	{	"VBP_1_TRAPE__ON_OFF_x1",																																																																		
		1	,	// Speed																																																																
		1	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__Trape_On	,																																																															
				FUNC_SP_VJ::FuncSp__Trape_Off	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
	{	"VBP_1_TRAPE__ON_OFF_x05",																																																																		
		0.5	,	// Speed																																																																
		1	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__Trape_On	,																																																															
				FUNC_SP_VJ::FuncSp__Trape_Off	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
	{	"VBP_1_TRAPE__ON_OFF_x025",																																																																		
		0.25	,	// Speed																																																																
		1	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__Trape_On	,																																																															
				FUNC_SP_VJ::FuncSp__Trape_Off	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
																																																																				
	// Sin-----------------------------------------------------------------------------------------------------------------------------																																																																			
	{	"VBP_1_SIN_x05",																																																																		
		0.5	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__sin	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	5	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	5	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
	{	"VBP_1_SIN_x025",																																																																		
		0.25	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__sin	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	3	,	5	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	3	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	3	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
	{	"VBP_1_SIN_x0125",																																																																		
		0.125	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__sin	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	3	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	3	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
	{	"VBP_1_SIN_x00625",																																																																		
		0.0625	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__sin	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	3	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	3	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
																																																																				
	// Square-----------------------------------------------------------------------------------------------------------------------------																																																																			
	{	"VBP_1_SQUARE_High",																																																																		
		1	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__Square_x2	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
	{	"VBP_1_SQUARE_x1",																																																																		
		1	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__Square_x1	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
																																																																				
	// Square Bl-----------------------------------------------------------------------------------------------------------------------------																																																																			
	{	"VBP_1_SQUARE_High_BL",																																																																		
		1	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__Square_x2_Bl	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
	{	"VBP_1_SQUARE__x1_BL",																																																																		
		1	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__Square_x1_Bl	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
																																																																				
	// Flash Bl-----------------------------------------------------------------------------------------------------------------------------																																																																			
	{	"VBP_1_FLASH_BL",																																																																		
		1	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__Flash_Bl	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
																																																																				
	// Strobe-----------------------------------------------------------------------------------------------------------------------------																																																																			
	{	"VBP_1_STROBE",																																																																		
		1	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__Flash_x4	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
																																																																				
	// Strobe BL-----------------------------------------------------------------------------------------------------------------------------																																																																			
	{	"VBP_1_STROBE_BL",																																																																		
		1	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				FUNC_SP_VJ::FuncSp__Flash_x4_Bl	,																																																															
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
																																																																				
	// -----------------------------------------------------------------------------------------------------------------------------																																																																			
	{	"BP_END",																																																																		
		1	,	// Speed																																																																
		0	,	// StartPatternId_Candidate																																																																
		{																																																																		
				NULL	,																																																															
																																																																				
		},																																																																		
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP										
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					
/*mov 0_12*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*mov 1_2*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*indicator*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*particle*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
/*strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},	
		},																																																																		
	},																																																																			
};																																																																				

/************************************************************************************************************************/
} //namespace SPACE_VJ{

