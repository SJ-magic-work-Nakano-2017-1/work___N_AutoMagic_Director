/************************************************************
// test code
// check if "StartPatternId_Candidate" is correct in all the Bp_x class object.

int cal_Num_StartPatternId_Candidate(BLOCK_PATTERN BlockPattern)
{
	int i;
	for(i = 0; BlockPattern.pShortPattern[i][0] != NULL; i++){
	}
	
	return i - 1;
}

void LIGHT::test()
{
	for(int i = 0; Bp_7[i].pShortPattern[0][0] != NULL; i++){
		int StartPatternId_Candidate_caled = cal_Num_StartPatternId_Candidate(Bp_7[i]);
		if(StartPatternId_Candidate_caled < Bp_7[i].StartPatternId_Candidate){
			printf("Error in:Bp_7[%d]\n", i);
		}
	}

	for(int i = 0; Bp_5[i].pShortPattern[0][0] != NULL; i++){
		int StartPatternId_Candidate_caled = cal_Num_StartPatternId_Candidate(Bp_5[i]);
		if(StartPatternId_Candidate_caled < Bp_5[i].StartPatternId_Candidate){
			printf("Error in:Bp_5[%d]\n", i);
		}
	}

	for(int i = 0; Bp_4[i].pShortPattern[0][0] != NULL; i++){
		int StartPatternId_Candidate_caled = cal_Num_StartPatternId_Candidate(Bp_4[i]);
		if(StartPatternId_Candidate_caled < Bp_4[i].StartPatternId_Candidate){
			printf("Error in:Bp_4[%d]\n", i);
		}
	}

	for(int i = 0; Bp_3[i].pShortPattern[0][0] != NULL; i++){
		int StartPatternId_Candidate_caled = cal_Num_StartPatternId_Candidate(Bp_3[i]);
		if(StartPatternId_Candidate_caled < Bp_3[i].StartPatternId_Candidate){
			printf("Error in:Bp_3[%d]\n", i);
		}
	}

	for(int i = 0; Bp_2[i].pShortPattern[0][0] != NULL; i++){
		int StartPatternId_Candidate_caled = cal_Num_StartPatternId_Candidate(Bp_2[i]);
		if(StartPatternId_Candidate_caled < Bp_2[i].StartPatternId_Candidate){
			printf("Error in:Bp_2[%d]\n", i);
		}
	}

	for(int i = 0; Bp_1[i].pShortPattern[0][0] != NULL; i++){
		int StartPatternId_Candidate_caled = cal_Num_StartPatternId_Candidate(Bp_1[i]);
		if(StartPatternId_Candidate_caled < Bp_1[i].StartPatternId_Candidate){
			printf("Error in:Bp_1[%d]\n", i);
		}
	}
	
	printf("Finish:checking\n");
}
************************************************************/
	

/************************************************************
// test code

// printout All Block pattern name
// Pattern定義が完了した後、重みをつけるために、作成済みpatternを列挙するのに使用
void LIGHT::test()
{
	FILE* fp;
	
	fp = fopen("../../../Bp_7.txt", "w");
	for(int i = 0; strcmp(Bp_7[i].name, "BP_END") != 0; i++ ){
		fprintf_Log_forTestCode(fp, "%s\n", Bp_7[i].name);
	}
	fclose(fp);

	fp = fopen("../../../Bp_5.txt", "w");
	for(int i = 0; strcmp(Bp_5[i].name, "BP_END") != 0; i++ ){
		fprintf_Log_forTestCode(fp, "%s\n", Bp_5[i].name);
	}
	fclose(fp);
	
	fp = fopen("../../../Bp_4.txt", "w");
	for(int i = 0; strcmp(Bp_4[i].name, "BP_END") != 0; i++ ){
		fprintf_Log_forTestCode(fp, "%s\n", Bp_4[i].name);
	}
	fclose(fp);
	
	fp = fopen("../../../Bp_3.txt", "w");
	for(int i = 0; strcmp(Bp_3[i].name, "BP_END") != 0; i++ ){
		fprintf_Log_forTestCode(fp, "%s\n", Bp_3[i].name);
	}
	fclose(fp);

	fp = fopen("../../../Bp_2.txt", "w");
	for(int i = 0; strcmp(Bp_2[i].name, "BP_END") != 0; i++ ){
		fprintf_Log_forTestCode(fp, "%s\n", Bp_2[i].name);
	}
	fclose(fp);

	fp = fopen("../../../Bp_1.txt", "w");
	for(int i = 0; strcmp(Bp_1[i].name, "BP_END") != 0; i++ ){
		fprintf_Log_forTestCode(fp, "%s\n", Bp_1[i].name);
	}
	fclose(fp);
}
************************************************************/

/************************************************************
// test code
// print out : DeviceType/State/PlayMode/BoostMode ごと : BlockPattern候補と選択される確率
// 各Patternが、狙った所に候補として挙がっていることを確認

int get_num_PatternTypes_in_Bp(const BLOCK_PATTERN *Bp_Pattern)
{
	int num;
	for( num = 0; strcmp(Bp_Pattern[num].name, "BP_END") != 0; num++ ){
	}
	
	return num;
}

void LIGHT::test()
{
	enum{
		BUF_SIZE = 2000,
	};
	
	for(int id = 0; id < 8; id++){
		const BLOCK_PATTERN *Bp_Pattern = NULL;
		char LogFileName[BUF_SIZE];
		
		if( (id == 0) || (id == 6) ){
			continue;
			
		}else{
			switch(id){
				case 1:	Bp_Pattern = &Bp_1[0];	break;
				case 2:	Bp_Pattern = &Bp_2[0];	break;
				case 3:	Bp_Pattern = &Bp_3[0];	break;
				case 4:	Bp_Pattern = &Bp_4[0];	break;
				case 5:	Bp_Pattern = &Bp_5[0];	break;
				case 7:	Bp_Pattern = &Bp_7[0];	break;
			}
			
			sprintf(LogFileName, "../../../Bp_%d.txt", id);
		}
		
		int NumPatterns = get_num_PatternTypes_in_Bp(Bp_Pattern);
		
		
		FILE* fp;
		fp = fopen(LogFileName, "w");
		
		for(int DeviceChType = DEVICE_CH_TYPE__FIX_LUM_PANEL; DeviceChType < int(NUM_DEVICE_CH_TYPE); DeviceChType++){
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
							case DEVICE_CH_TYPE__FIX_LUM_PANEL:		fprintf_Log_forTestCode(fp, "Panel ");		break;
							case DEVICE_CH_TYPE__FIX_LUM_STROBE:	fprintf_Log_forTestCode(fp, "Strobe ");		break;
							case DEVICE_CH_TYPE__MOV_LUM_RGB:		fprintf_Log_forTestCode(fp, "MovRGB ");		break;
							case DEVICE_CH_TYPE__MOV_LUM_STROBE:	fprintf_Log_forTestCode(fp, "MovStrobe ");	break;
							case DEVICE_CH_TYPE__MOV_ANGLE_PAN:		fprintf_Log_forTestCode(fp, "Pan ");		break;
							case DEVICE_CH_TYPE__MOV_ANGLE_TILT:	fprintf_Log_forTestCode(fp, "Tilt ");		break;
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
}
************************************************************/


/************************************************************
************************************************************/
#include <stdio.h>

#include "L_common.h"

#include "L_ShortPattern.h"
#include "L_BlockPattern.h"


/************************************************************************************************************************/
namespace SPACE_LIGHT{




/************************************************************
Block Pattern data

// Still -----------------------------------------------------------------------------------------------------------------------
// StillFlowBl -----------------------------------------------------------------------------------------------------------------
// StillFlow -------------------------------------------------------------------------------------------------------------------
// FlashBl ---------------------------------------------------------------------------------------------------------------------
// StrobeBl --------------------------------------------------------------------------------------------------------------------
// Strobe ----------------------------------------------------------------------------------------------------------------------
// Ambient ---------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------

★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
Copy from Excel below.
★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
************************************************************/
const struct BLOCK_PATTERN Bp_7[] = {																																																																			
	// LUM__Still -------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_7_LUM__STILL__OFF",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILL__ON",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	3	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	100	,	100	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	100	,	100	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILL__ON_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	20	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	20	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILL__ON_2CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	20	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	20	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILL__ON_3CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	20	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	20	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILL__ON_4CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	20	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	20	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILL__ON_5CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	20	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	20	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	20	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StillFlowBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_7_LUM__STILLFLOW_BL__FLOW",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_7_Bl	,	FuncSp__Lum_On_2_7_Bl	,	FuncSp__Lum_On_3_7_Bl	,	FuncSp__Lum_On_4_7_Bl	,	FuncSp__Lum_On_5_7_Bl	,	FuncSp__Lum_On_6_7_Bl	,	FuncSp__Lum_On_7_7_Bl	},																																																		
			{	FuncSp__Lum_Off_1_7_Bl	,	FuncSp__Lum_Off_2_7_Bl	,	FuncSp__Lum_Off_3_7_Bl	,	FuncSp__Lum_Off_4_7_Bl	,	FuncSp__Lum_Off_5_7_Bl	,	FuncSp__Lum_Off_6_7_Bl	,	FuncSp__Lum_Off_7_7_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILLFLOW_BL__OPEN",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_4_4_Bl	,	FuncSp__Lum_On_3_4_Bl	,	FuncSp__Lum_On_2_4_Bl	,	FuncSp__Lum_On_1_4_Bl	,	FuncSp__Lum_On_2_4_Bl	,	FuncSp__Lum_On_3_4_Bl	,	FuncSp__Lum_On_4_4_Bl	},																																																		
			{	FuncSp__Lum_Off_4_4_Bl	,	FuncSp__Lum_Off_3_4_Bl	,	FuncSp__Lum_Off_2_4_Bl	,	FuncSp__Lum_Off_1_4_Bl	,	FuncSp__Lum_Off_2_4_Bl	,	FuncSp__Lum_Off_3_4_Bl	,	FuncSp__Lum_Off_4_4_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILLFLOW_BL__CLOSE",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_4_Bl	,	FuncSp__Lum_On_2_4_Bl	,	FuncSp__Lum_On_3_4_Bl	,	FuncSp__Lum_On_4_4_Bl	,	FuncSp__Lum_On_3_4_Bl	,	FuncSp__Lum_On_2_4_Bl	,	FuncSp__Lum_On_1_4_Bl	},																																																		
			{	FuncSp__Lum_Off_1_4_Bl	,	FuncSp__Lum_Off_2_4_Bl	,	FuncSp__Lum_Off_3_4_Bl	,	FuncSp__Lum_Off_4_4_Bl	,	FuncSp__Lum_Off_3_4_Bl	,	FuncSp__Lum_Off_2_4_Bl	,	FuncSp__Lum_Off_1_4_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StillFlow -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_7_LUM__STILLFLOW__FLOW",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_7	,	FuncSp__Lum_On_2_7	,	FuncSp__Lum_On_3_7	,	FuncSp__Lum_On_4_7	,	FuncSp__Lum_On_5_7	,	FuncSp__Lum_On_6_7	,	FuncSp__Lum_On_7_7	},																																																		
			{	FuncSp__Lum_Off_1_7	,	FuncSp__Lum_Off_2_7	,	FuncSp__Lum_Off_3_7	,	FuncSp__Lum_Off_4_7	,	FuncSp__Lum_Off_5_7	,	FuncSp__Lum_Off_6_7	,	FuncSp__Lum_Off_7_7	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	13	,	13	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	13	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	17	,	17	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	17	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILLFLOW__FLOW_x3",																																																																	
		3	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_7	,	FuncSp__Lum_On_2_7	,	FuncSp__Lum_On_3_7	,	FuncSp__Lum_On_4_7	,	FuncSp__Lum_On_5_7	,	FuncSp__Lum_On_6_7	,	FuncSp__Lum_On_7_7	},																																																		
			{	FuncSp__Lum_Off_1_7	,	FuncSp__Lum_Off_2_7	,	FuncSp__Lum_Off_3_7	,	FuncSp__Lum_Off_4_7	,	FuncSp__Lum_Off_5_7	,	FuncSp__Lum_Off_6_7	,	FuncSp__Lum_Off_7_7	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	17	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	17	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILLFLOW__OPEN",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_4_4	,	FuncSp__Lum_On_3_4	,	FuncSp__Lum_On_2_4	,	FuncSp__Lum_On_1_4	,	FuncSp__Lum_On_2_4	,	FuncSp__Lum_On_3_4	,	FuncSp__Lum_On_4_4	},																																																		
			{	FuncSp__Lum_Off_4_4	,	FuncSp__Lum_Off_3_4	,	FuncSp__Lum_Off_2_4	,	FuncSp__Lum_Off_1_4	,	FuncSp__Lum_Off_2_4	,	FuncSp__Lum_Off_3_4	,	FuncSp__Lum_Off_4_4	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	13	,	13	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	13	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	17	,	17	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	17	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILLFLOW__OPEN_x3",																																																																	
		3	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_4_4	,	FuncSp__Lum_On_3_4	,	FuncSp__Lum_On_2_4	,	FuncSp__Lum_On_1_4	,	FuncSp__Lum_On_2_4	,	FuncSp__Lum_On_3_4	,	FuncSp__Lum_On_4_4	},																																																		
			{	FuncSp__Lum_Off_4_4	,	FuncSp__Lum_Off_3_4	,	FuncSp__Lum_Off_2_4	,	FuncSp__Lum_Off_1_4	,	FuncSp__Lum_Off_2_4	,	FuncSp__Lum_Off_3_4	,	FuncSp__Lum_Off_4_4	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	17	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	17	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILLFLOW__CLOSE",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_4	,	FuncSp__Lum_On_2_4	,	FuncSp__Lum_On_3_4	,	FuncSp__Lum_On_4_4	,	FuncSp__Lum_On_3_4	,	FuncSp__Lum_On_2_4	,	FuncSp__Lum_On_1_4	},																																																		
			{	FuncSp__Lum_Off_1_4	,	FuncSp__Lum_Off_2_4	,	FuncSp__Lum_Off_3_4	,	FuncSp__Lum_Off_4_4	,	FuncSp__Lum_Off_3_4	,	FuncSp__Lum_Off_2_4	,	FuncSp__Lum_Off_1_4	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	13	,	13	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	13	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	17	,	17	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	17	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STILLFLOW__CLOSE_x3",																																																																	
		3	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_4	,	FuncSp__Lum_On_2_4	,	FuncSp__Lum_On_3_4	,	FuncSp__Lum_On_4_4	,	FuncSp__Lum_On_3_4	,	FuncSp__Lum_On_2_4	,	FuncSp__Lum_On_1_4	},																																																		
			{	FuncSp__Lum_Off_1_4	,	FuncSp__Lum_Off_2_4	,	FuncSp__Lum_Off_3_4	,	FuncSp__Lum_Off_4_4	,	FuncSp__Lum_Off_3_4	,	FuncSp__Lum_Off_2_4	,	FuncSp__Lum_Off_1_4	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	17	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	17	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__FlashBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_7_LUM__FLASH_BL__FLASH",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__FLASH_BL__FLASH_2CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__FLASH_BL__FLASH_3CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__FLASH_BL__FLASH_4CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__FLASH_BL__FLASH_5CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__FLASH_BL__FLASH_2_7CH",																																																																	
		1	,	// Speed																																																															
		13	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__FLASH_BL__FLASH_3_7CH",																																																																	
		1	,	// Speed																																																															
		13	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__FLASH_BL__FLASH_OPEN",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__FLASH_BL__FLASH_CLOSE",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	11	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	6	,	6	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	11	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StrobeBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_7_LUM__STROBE_BL__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STROBE_BL__STROBE_x4_2CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	},																																																		
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STROBE_BL__STROBE_x4_3CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	},																																																		
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	},																																																		
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STROBE_BL__STROBE_x4_4CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	},																																																		
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	},																																																		
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	},																																																		
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STROBE_BL__ORDER_x7",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_1_7_Bl	,	FuncSp__Lum_Flash_2_7_Bl	,	FuncSp__Lum_Flash_3_7_Bl	,	FuncSp__Lum_Flash_4_7_Bl	,	FuncSp__Lum_Flash_5_7_Bl	,	FuncSp__Lum_Flash_6_7_Bl	,	FuncSp__Lum_Flash_7_7_Bl	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STROBE_BL__SPREAD_x7_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx7_Bl	,	FuncSp__Lum_Flashx7_2_Bl	,	FuncSp__Lum_Flashx7_3_Bl	,	FuncSp__Lum_Flashx7_4_Bl	,	FuncSp__Lum_Flashx7_5_Bl	,	FuncSp__Lum_Flashx7_6_Bl	,	FuncSp__Lum_Flashx7_7_Bl	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Strobe -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_7_LUM__STROBE__STROBE_x4",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STROBE__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STROBE__STROBE_x4_2CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	},																																																		
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STROBE__STROBE_x4_3CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	},																																																		
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	},																																																		
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STROBE__STROBE_x4_4CH",																																																																	
		1	,	// Speed																																																															
		6	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	},																																																		
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	},																																																		
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	},																																																		
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STROBE__ORDER_x7",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_1_7	,	FuncSp__Lum_Flash_2_7	,	FuncSp__Lum_Flash_3_7	,	FuncSp__Lum_Flash_4_7	,	FuncSp__Lum_Flash_5_7	,	FuncSp__Lum_Flash_6_7	,	FuncSp__Lum_Flash_7_7	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_LUM__STROBE__SPREAD_x7_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx7	,	FuncSp__Lum_Flashx7_2	,	FuncSp__Lum_Flashx7_3	,	FuncSp__Lum_Flashx7_4	,	FuncSp__Lum_Flashx7_5	,	FuncSp__Lum_Flashx7_6	,	FuncSp__Lum_Flashx7_7	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Ambient -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_7_LUM__AMBIENT__AMBIENT",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	3	,	0	}, },	{ {	0	,	0	}, {	30	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	30	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	100	,	100	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	100	,	100	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// PanTilt__Pose -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_7_PAN__POSE__OPEN_CLOSE",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_7ch_const_Angle_0	,	FuncSp__Pan_7ch_const_Angle_1	,	FuncSp__Pan_7ch_const_Angle_2	,	FuncSp__Pan_7ch_const_Angle_3	,	FuncSp__Pan_7ch_const_Angle_4	,	FuncSp__Pan_7ch_const_Angle_5	,	FuncSp__Pan_7ch_const_Angle_6	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__POSE__OPEN_CLOSE",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_7ch_const_Angle_0	,	FuncSp__Tilt_7ch_const_Angle_1	,	FuncSp__Tilt_7ch_const_Angle_2	,	FuncSp__Tilt_7ch_const_Angle_3	,	FuncSp__Tilt_7ch_const_Angle_4	,	FuncSp__Tilt_7ch_const_Angle_5	,	FuncSp__Tilt_7ch_const_Angle_6	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__POSE__V_LOW",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_7ch_const_Angle_0	,	FuncSp__Tilt_7ch_const_Angle_1	,	FuncSp__Tilt_7ch_const_Angle_2	,	FuncSp__Tilt_7ch_const_Angle_3	,	FuncSp__Tilt_7ch_const_Angle_2	,	FuncSp__Tilt_7ch_const_Angle_1	,	FuncSp__Tilt_7ch_const_Angle_0	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__POSE__V_HIGH",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_7ch_const_Angle_6	,	FuncSp__Tilt_7ch_const_Angle_5	,	FuncSp__Tilt_7ch_const_Angle_4	,	FuncSp__Tilt_7ch_const_Angle_3	,	FuncSp__Tilt_7ch_const_Angle_4	,	FuncSp__Tilt_7ch_const_Angle_5	,	FuncSp__Tilt_7ch_const_Angle_6	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__POSE__UNITY_0",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_7ch_const_Angle_0	,	FuncSp__Pan_7ch_const_Angle_0	,	FuncSp__Pan_7ch_const_Angle_0	,	FuncSp__Pan_7ch_const_Angle_0	,	FuncSp__Pan_7ch_const_Angle_0	,	FuncSp__Pan_7ch_const_Angle_0	,	FuncSp__Pan_7ch_const_Angle_0	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__POSE__UNITY_1",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_7ch_const_Angle_1	,	FuncSp__Pan_7ch_const_Angle_1	,	FuncSp__Pan_7ch_const_Angle_1	,	FuncSp__Pan_7ch_const_Angle_1	,	FuncSp__Pan_7ch_const_Angle_1	,	FuncSp__Pan_7ch_const_Angle_1	,	FuncSp__Pan_7ch_const_Angle_1	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__POSE__UNITY_2",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_7ch_const_Angle_2	,	FuncSp__Pan_7ch_const_Angle_2	,	FuncSp__Pan_7ch_const_Angle_2	,	FuncSp__Pan_7ch_const_Angle_2	,	FuncSp__Pan_7ch_const_Angle_2	,	FuncSp__Pan_7ch_const_Angle_2	,	FuncSp__Pan_7ch_const_Angle_2	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__POSE__UNITY_3",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_7ch_const_Angle_3	,	FuncSp__Pan_7ch_const_Angle_3	,	FuncSp__Pan_7ch_const_Angle_3	,	FuncSp__Pan_7ch_const_Angle_3	,	FuncSp__Pan_7ch_const_Angle_3	,	FuncSp__Pan_7ch_const_Angle_3	,	FuncSp__Pan_7ch_const_Angle_3	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__POSE__UNITY_4",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_7ch_const_Angle_4	,	FuncSp__Pan_7ch_const_Angle_4	,	FuncSp__Pan_7ch_const_Angle_4	,	FuncSp__Pan_7ch_const_Angle_4	,	FuncSp__Pan_7ch_const_Angle_4	,	FuncSp__Pan_7ch_const_Angle_4	,	FuncSp__Pan_7ch_const_Angle_4	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__POSE__UNITY_5",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_7ch_const_Angle_5	,	FuncSp__Pan_7ch_const_Angle_5	,	FuncSp__Pan_7ch_const_Angle_5	,	FuncSp__Pan_7ch_const_Angle_5	,	FuncSp__Pan_7ch_const_Angle_5	,	FuncSp__Pan_7ch_const_Angle_5	,	FuncSp__Pan_7ch_const_Angle_5	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__POSE__UNITY_6",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_7ch_const_Angle_6	,	FuncSp__Pan_7ch_const_Angle_6	,	FuncSp__Pan_7ch_const_Angle_6	,	FuncSp__Pan_7ch_const_Angle_6	,	FuncSp__Pan_7ch_const_Angle_6	,	FuncSp__Pan_7ch_const_Angle_6	,	FuncSp__Pan_7ch_const_Angle_6	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__POSE__UNITY_0",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_7ch_const_Angle_0	,	FuncSp__Tilt_7ch_const_Angle_0	,	FuncSp__Tilt_7ch_const_Angle_0	,	FuncSp__Tilt_7ch_const_Angle_0	,	FuncSp__Tilt_7ch_const_Angle_0	,	FuncSp__Tilt_7ch_const_Angle_0	,	FuncSp__Tilt_7ch_const_Angle_0	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__POSE__UNITY_1",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_7ch_const_Angle_1	,	FuncSp__Tilt_7ch_const_Angle_1	,	FuncSp__Tilt_7ch_const_Angle_1	,	FuncSp__Tilt_7ch_const_Angle_1	,	FuncSp__Tilt_7ch_const_Angle_1	,	FuncSp__Tilt_7ch_const_Angle_1	,	FuncSp__Tilt_7ch_const_Angle_1	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__POSE__UNITY_2",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_7ch_const_Angle_2	,	FuncSp__Tilt_7ch_const_Angle_2	,	FuncSp__Tilt_7ch_const_Angle_2	,	FuncSp__Tilt_7ch_const_Angle_2	,	FuncSp__Tilt_7ch_const_Angle_2	,	FuncSp__Tilt_7ch_const_Angle_2	,	FuncSp__Tilt_7ch_const_Angle_2	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__POSE__UNITY_3",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_7ch_const_Angle_3	,	FuncSp__Tilt_7ch_const_Angle_3	,	FuncSp__Tilt_7ch_const_Angle_3	,	FuncSp__Tilt_7ch_const_Angle_3	,	FuncSp__Tilt_7ch_const_Angle_3	,	FuncSp__Tilt_7ch_const_Angle_3	,	FuncSp__Tilt_7ch_const_Angle_3	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__POSE__UNITY_4",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_7ch_const_Angle_4	,	FuncSp__Tilt_7ch_const_Angle_4	,	FuncSp__Tilt_7ch_const_Angle_4	,	FuncSp__Tilt_7ch_const_Angle_4	,	FuncSp__Tilt_7ch_const_Angle_4	,	FuncSp__Tilt_7ch_const_Angle_4	,	FuncSp__Tilt_7ch_const_Angle_4	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__POSE__UNITY_5",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_7ch_const_Angle_5	,	FuncSp__Tilt_7ch_const_Angle_5	,	FuncSp__Tilt_7ch_const_Angle_5	,	FuncSp__Tilt_7ch_const_Angle_5	,	FuncSp__Tilt_7ch_const_Angle_5	,	FuncSp__Tilt_7ch_const_Angle_5	,	FuncSp__Tilt_7ch_const_Angle_5	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__POSE__UNITY_6",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_7ch_const_Angle_6	,	FuncSp__Tilt_7ch_const_Angle_6	,	FuncSp__Tilt_7ch_const_Angle_6	,	FuncSp__Tilt_7ch_const_Angle_6	,	FuncSp__Tilt_7ch_const_Angle_6	,	FuncSp__Tilt_7ch_const_Angle_6	,	FuncSp__Tilt_7ch_const_Angle_6	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__POSE__RANDOM",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_7ch_const_Angle_0	,	FuncSp__Pan_7ch_const_Angle_1	,	FuncSp__Pan_7ch_const_Angle_2	,	FuncSp__Pan_7ch_const_Angle_3	,	FuncSp__Pan_7ch_const_Angle_4	,	FuncSp__Pan_7ch_const_Angle_5	,	FuncSp__Pan_7ch_const_Angle_6	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	24	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__POSE__RANDOM",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_7ch_const_Angle_0	,	FuncSp__Tilt_7ch_const_Angle_1	,	FuncSp__Tilt_7ch_const_Angle_2	,	FuncSp__Tilt_7ch_const_Angle_3	,	FuncSp__Tilt_7ch_const_Angle_4	,	FuncSp__Tilt_7ch_const_Angle_5	,	FuncSp__Tilt_7ch_const_Angle_6	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	24	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// PanTilt__Triangle -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_7_PAN__TRIANGLE__1_2__PHASE_0",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_4__PHASE_0",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_8__PHASE_0",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_2__PHASE_0",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_4__PHASE_0",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_8__PHASE_0",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_2__PHASE_90__LINE",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_15	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_75	,	FuncSp__Pan_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_4__PHASE_90__LINE",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_15	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_75	,	FuncSp__Pan_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_8__PHASE_90__LINE",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_15	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_75	,	FuncSp__Pan_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_2__PHASE_90__RANDOM",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_15	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_75	,	FuncSp__Pan_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_4__PHASE_90__RANDOM",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_15	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_75	,	FuncSp__Pan_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_8__PHASE_90__RANDOM",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_15	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_75	,	FuncSp__Pan_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_2__PHASE_90__LINE",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_15	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_75	,	FuncSp__Tilt_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_4__PHASE_90__LINE",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_15	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_75	,	FuncSp__Tilt_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_8__PHASE_90__LINE",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_15	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_75	,	FuncSp__Tilt_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_2__PHASE_90__RANDOM",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_15	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_75	,	FuncSp__Tilt_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_4__PHASE_90__RANDOM",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_15	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_75	,	FuncSp__Tilt_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_8__PHASE_90__RANDOM",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_15	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_75	,	FuncSp__Tilt_Triangle_phase_90	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_2__PHASE_180__LINE",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_120	,	FuncSp__Pan_Triangle_phase_150	,	FuncSp__Pan_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_4__PHASE_180__LINE",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_120	,	FuncSp__Pan_Triangle_phase_150	,	FuncSp__Pan_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_8__PHASE_180__LINE",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_120	,	FuncSp__Pan_Triangle_phase_150	,	FuncSp__Pan_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_2__PHASE_180__RANDOM",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_120	,	FuncSp__Pan_Triangle_phase_150	,	FuncSp__Pan_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_4__PHASE_180__RANDOM",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_120	,	FuncSp__Pan_Triangle_phase_150	,	FuncSp__Pan_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_PAN__TRIANGLE__1_8__PHASE_180__RANDOM",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_30	,	FuncSp__Pan_Triangle_phase_60	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_120	,	FuncSp__Pan_Triangle_phase_150	,	FuncSp__Pan_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_2__PHASE_180__LINE",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_120	,	FuncSp__Tilt_Triangle_phase_150	,	FuncSp__Tilt_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_4__PHASE_180__LINE",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_120	,	FuncSp__Tilt_Triangle_phase_150	,	FuncSp__Tilt_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_8__PHASE_180__LINE",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_120	,	FuncSp__Tilt_Triangle_phase_150	,	FuncSp__Tilt_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_2__PHASE_180__RANDOM",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_120	,	FuncSp__Tilt_Triangle_phase_150	,	FuncSp__Tilt_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_4__PHASE_180__RANDOM",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_120	,	FuncSp__Tilt_Triangle_phase_150	,	FuncSp__Tilt_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	8	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_7_TILT__TRIANGLE__1_8__PHASE_180__RANDOM",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_30	,	FuncSp__Tilt_Triangle_phase_60	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_120	,	FuncSp__Tilt_Triangle_phase_150	,	FuncSp__Tilt_Triangle_phase_180	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	2	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	2	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// -----------------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_END",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
};																																																																			

const struct BLOCK_PATTERN Bp_5[] = {																																																																			
	// LUM__Still -------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_5_LUM__STILL__OFF",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STILL__ON",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STILL__ON_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STILL__ON_2CH",																																																																	
		1	,	// Speed																																																															
		4	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STILL__ON_3CH",																																																																	
		1	,	// Speed																																																															
		4	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StillFlowBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_5_LUM__STILLFLOW_BL__FLOW",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_5_Bl	,	FuncSp__Lum_On_2_5_Bl	,	FuncSp__Lum_On_3_5_Bl	,	FuncSp__Lum_On_4_5_Bl	,	FuncSp__Lum_On_5_5_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_5_Bl	,	FuncSp__Lum_Off_2_5_Bl	,	FuncSp__Lum_Off_3_5_Bl	,	FuncSp__Lum_Off_4_5_Bl	,	FuncSp__Lum_Off_5_5_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STILLFLOW_BL__OPEN",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_3_3_Bl	,	FuncSp__Lum_On_2_3_Bl	,	FuncSp__Lum_On_1_3_Bl	,	FuncSp__Lum_On_2_3_Bl	,	FuncSp__Lum_On_3_3_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_3_3_Bl	,	FuncSp__Lum_Off_2_3_Bl	,	FuncSp__Lum_Off_1_3_Bl	,	FuncSp__Lum_Off_2_3_Bl	,	FuncSp__Lum_Off_3_3_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STILLFLOW_BL__CLOSE",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_3_Bl	,	FuncSp__Lum_On_2_3_Bl	,	FuncSp__Lum_On_3_3_Bl	,	FuncSp__Lum_On_2_3_Bl	,	FuncSp__Lum_On_1_3_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_3_Bl	,	FuncSp__Lum_Off_2_3_Bl	,	FuncSp__Lum_Off_3_3_Bl	,	FuncSp__Lum_Off_2_3_Bl	,	FuncSp__Lum_Off_1_3_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StillFlow -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_5_LUM__STILLFLOW__FLOW",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_5	,	FuncSp__Lum_On_2_5	,	FuncSp__Lum_On_3_5	,	FuncSp__Lum_On_4_5	,	FuncSp__Lum_On_5_5	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_5	,	FuncSp__Lum_Off_2_5	,	FuncSp__Lum_Off_3_5	,	FuncSp__Lum_Off_4_5	,	FuncSp__Lum_Off_5_5	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	3	,	0	}, },	{ {	0	,	0	}, {	13	,	13	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	13	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STILLFLOW__FLOW_x3",																																																																	
		3	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_5	,	FuncSp__Lum_On_2_5	,	FuncSp__Lum_On_3_5	,	FuncSp__Lum_On_4_5	,	FuncSp__Lum_On_5_5	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_5	,	FuncSp__Lum_Off_2_5	,	FuncSp__Lum_Off_3_5	,	FuncSp__Lum_Off_4_5	,	FuncSp__Lum_Off_5_5	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STILLFLOW__OPEN",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_3_3	,	FuncSp__Lum_On_2_3	,	FuncSp__Lum_On_1_3	,	FuncSp__Lum_On_2_3	,	FuncSp__Lum_On_3_3	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_3_3	,	FuncSp__Lum_Off_2_3	,	FuncSp__Lum_Off_1_3	,	FuncSp__Lum_Off_2_3	,	FuncSp__Lum_Off_3_3	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	3	,	0	}, },	{ {	0	,	0	}, {	13	,	13	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	13	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STILLFLOW__OPEN_x3",																																																																	
		3	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_3_3	,	FuncSp__Lum_On_2_3	,	FuncSp__Lum_On_1_3	,	FuncSp__Lum_On_2_3	,	FuncSp__Lum_On_3_3	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_3_3	,	FuncSp__Lum_Off_2_3	,	FuncSp__Lum_Off_1_3	,	FuncSp__Lum_Off_2_3	,	FuncSp__Lum_Off_3_3	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STILLFLOW__CLOSE",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_3	,	FuncSp__Lum_On_2_3	,	FuncSp__Lum_On_3_3	,	FuncSp__Lum_On_2_3	,	FuncSp__Lum_On_1_3	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_3	,	FuncSp__Lum_Off_2_3	,	FuncSp__Lum_Off_3_3	,	FuncSp__Lum_Off_2_3	,	FuncSp__Lum_Off_1_3	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	3	,	0	}, },	{ {	0	,	0	}, {	13	,	13	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	33	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	13	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	33	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STILLFLOW__CLOSE_x3",																																																																	
		3	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_3	,	FuncSp__Lum_On_2_3	,	FuncSp__Lum_On_3_3	,	FuncSp__Lum_On_2_3	,	FuncSp__Lum_On_1_3	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_3	,	FuncSp__Lum_Off_2_3	,	FuncSp__Lum_Off_3_3	,	FuncSp__Lum_Off_2_3	,	FuncSp__Lum_Off_1_3	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__FlashBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_5_LUM__FLASH_BL__FLASH",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	14	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__FLASH_BL__FLASH_2CH",																																																																	
		1	,	// Speed																																																															
		4	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	14	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__FLASH_BL__FLASH_3CH",																																																																	
		1	,	// Speed																																																															
		4	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	14	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__FLASH_BL__FLASH_2_5CH",																																																																	
		1	,	// Speed																																																															
		9	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	14	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__FLASH_BL__FLASH_3_5CH",																																																																	
		1	,	// Speed																																																															
		9	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	14	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__FLASH_BL__FLASH_OPEN",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	14	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__FLASH_BL__FLASH_CLOSE",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	14	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	14	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StrobeBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_5_LUM__STROBE_BL__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STROBE_BL__STROBE_x4_2CH",																																																																	
		1	,	// Speed																																																															
		4	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STROBE_BL__STROBE_x4_3CH",																																																																	
		1	,	// Speed																																																															
		4	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STROBE_BL__ORDER_x5",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_1_5_Bl	,	FuncSp__Lum_Flash_2_5_Bl	,	FuncSp__Lum_Flash_3_5_Bl	,	FuncSp__Lum_Flash_4_5_Bl	,	FuncSp__Lum_Flash_5_5_Bl	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STROBE_BL__SPREAD_x5_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx5_Bl	,	FuncSp__Lum_Flashx5_2_Bl	,	FuncSp__Lum_Flashx5_3_Bl	,	FuncSp__Lum_Flashx5_4_Bl	,	FuncSp__Lum_Flashx5_5_Bl	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Strobe -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_5_LUM__STROBE__STROBE_x4",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	37	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STROBE__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STROBE__STROBE_x4_2CH",																																																																	
		1	,	// Speed																																																															
		4	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	37	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STROBE__STROBE_x4_3CH",																																																																	
		1	,	// Speed																																																															
		4	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	37	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STROBE__ORDER_x5",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_1_5	,	FuncSp__Lum_Flash_2_5	,	FuncSp__Lum_Flash_3_5	,	FuncSp__Lum_Flash_4_5	,	FuncSp__Lum_Flash_5_5	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	37	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_5_LUM__STROBE__SPREAD_x5_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx5	,	FuncSp__Lum_Flashx5_2	,	FuncSp__Lum_Flashx5_3	,	FuncSp__Lum_Flashx5_4	,	FuncSp__Lum_Flashx5_5	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Ambient -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_5_LUM__AMBIENT__AMBIENT",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	30	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	30	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// -----------------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_END",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
};																																																																			

const struct BLOCK_PATTERN Bp_4[] = {																																																																			
	// LUM__Still -------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_4_LUM__STILL__OFF",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STILL__ON",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STILL__ON_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STILL__ON_1CH",																																																																	
		1	,	// Speed																																																															
		3	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STILL__ON_2CH",																																																																	
		1	,	// Speed																																																															
		3	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StillFlowBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_4_LUM__STILLFLOW_BL__FLOW",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_4_Bl	,	FuncSp__Lum_On_2_4_Bl	,	FuncSp__Lum_On_3_4_Bl	,	FuncSp__Lum_On_4_4_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_4_Bl	,	FuncSp__Lum_Off_2_4_Bl	,	FuncSp__Lum_Off_3_4_Bl	,	FuncSp__Lum_Off_4_4_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	100	,	100	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	100	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StillFlow -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_4_LUM__STILLFLOW__FLOW",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_4	,	FuncSp__Lum_On_2_4	,	FuncSp__Lum_On_3_4	,	FuncSp__Lum_On_4_4	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_4	,	FuncSp__Lum_Off_2_4	,	FuncSp__Lum_Off_3_4	,	FuncSp__Lum_Off_4_4	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	4	,	4	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	4	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STILLFLOW__FLOW_x3",																																																																	
		3	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_4	,	FuncSp__Lum_On_2_4	,	FuncSp__Lum_On_3_4	,	FuncSp__Lum_On_4_4	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_4	,	FuncSp__Lum_Off_2_4	,	FuncSp__Lum_Off_3_4	,	FuncSp__Lum_Off_4_4	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	100	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__FlashBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_4_LUM__FLASH_BL__FLASH",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__FLASH_BL__FLASH_1CH",																																																																	
		1	,	// Speed																																																															
		3	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__FLASH_BL__FLASH_2CH",																																																																	
		1	,	// Speed																																																															
		3	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__FLASH_BL__FLASH_1_4CH",																																																																	
		1	,	// Speed																																																															
		7	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	4	,	4	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StrobeBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_4_LUM__STROBE_BL__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STROBE_BL__STROBE_x4_1CH",																																																																	
		1	,	// Speed																																																															
		3	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STROBE_BL__STROBE_x4_2CH",																																																																	
		1	,	// Speed																																																															
		3	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STROBE_BL__ORDER_x4",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_1_4_Bl	,	FuncSp__Lum_Flash_2_4_Bl	,	FuncSp__Lum_Flash_3_4_Bl	,	FuncSp__Lum_Flash_4_4_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STROBE_BL__SPREAD_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_2_Bl	,	FuncSp__Lum_Flashx4_3_Bl	,	FuncSp__Lum_Flashx4_4_Bl	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Strobe -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_4_LUM__STROBE__STROBE_x4",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STROBE__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STROBE__STROBE_x4_1CH",																																																																	
		1	,	// Speed																																																															
		3	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STROBE__STROBE_x4_2CH",																																																																	
		1	,	// Speed																																																															
		3	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STROBE__ORDER_x4",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_1_4	,	FuncSp__Lum_Flash_2_4	,	FuncSp__Lum_Flash_3_4	,	FuncSp__Lum_Flash_4_4	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_4_LUM__STROBE__SPREAD_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4_2	,	FuncSp__Lum_Flashx4_3	,	FuncSp__Lum_Flashx4_4	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Ambient -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_4_LUM__AMBIENT__AMBIENT",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	3	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	3	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// -----------------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_END",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
};																																																																			

const struct BLOCK_PATTERN Bp_3[] = {																																																																			
	// LUM__Still -------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_3_LUM__STILL__OFF",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STILL__ON",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STILL__ON_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STILL__ON_1CH",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STILL__ON_2CH",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	33	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	7	,	7	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	33	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StillFlowBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_3_LUM__STILLFLOW_BL__FLOW",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_3_Bl	,	FuncSp__Lum_On_2_3_Bl	,	FuncSp__Lum_On_3_3_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_3_Bl	,	FuncSp__Lum_Off_2_3_Bl	,	FuncSp__Lum_Off_3_3_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	100	,	100	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	100	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	100	,	100	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	100	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StillFlow -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_3_LUM__STILLFLOW__FLOW",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_3	,	FuncSp__Lum_On_2_3	,	FuncSp__Lum_On_3_3	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_3	,	FuncSp__Lum_Off_2_3	,	FuncSp__Lum_Off_3_3	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	4	,	4	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	4	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	10	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	10	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STILLFLOW__FLOW_x3",																																																																	
		3	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_On_1_3	,	FuncSp__Lum_On_2_3	,	FuncSp__Lum_On_3_3	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Off_1_3	,	FuncSp__Lum_Off_2_3	,	FuncSp__Lum_Off_3_3	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	100	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	100	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	30	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__FlashBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_3_LUM__FLASH_BL__FLASH",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__FLASH_BL__FLASH_1CH",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__FLASH_BL__FLASH_2CH",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__FLASH_BL__FLASH_1_3CH",																																																																	
		1	,	// Speed																																																															
		5	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	25	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	13	,	13	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	25	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StrobeBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_3_LUM__STROBE_BL__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STROBE_BL__STROBE_x4_1CH",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STROBE_BL__STROBE_x4_2CH",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STROBE_BL__ORDER_x3",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_1_3_Bl	,	FuncSp__Lum_Flash_2_3_Bl	,	FuncSp__Lum_Flash_3_3_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STROBE_BL__SPREAD_x3_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx3_Bl	,	FuncSp__Lum_Flashx3_2_Bl	,	FuncSp__Lum_Flashx3_3_Bl	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Strobe -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_3_LUM__STROBE__STROBE_x4",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STROBE__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STROBE__STROBE_x4_1CH",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STROBE__STROBE_x4_2CH",																																																																	
		1	,	// Speed																																																															
		2	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STROBE__ORDER_x3",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_1_3	,	FuncSp__Lum_Flash_2_3	,	FuncSp__Lum_Flash_3_3	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	15	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	75	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_LUM__STROBE__SPREAD_x3_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx3	,	FuncSp__Lum_Flashx3_2	,	FuncSp__Lum_Flashx3_3	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	12	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Ambient -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_3_LUM__AMBIENT__AMBIENT",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	3	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	3	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// PanTilt__Pose -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_3_PAN__POSE__OPEN_CLOSE",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_3ch_const_Angle_0	,	FuncSp__Pan_3ch_const_Angle_1	,	FuncSp__Pan_3ch_const_Angle_2	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	25	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__POSE__OPEN_CLOSE",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_3ch_const_Angle_0	,	FuncSp__Tilt_3ch_const_Angle_1	,	FuncSp__Tilt_3ch_const_Angle_2	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	16	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__POSE__V_LOW",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_3ch_const_Angle_0	,	FuncSp__Tilt_3ch_const_Angle_1	,	FuncSp__Tilt_3ch_const_Angle_0	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	16	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__POSE__V_HIGH",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_3ch_const_Angle_2	,	FuncSp__Tilt_3ch_const_Angle_1	,	FuncSp__Tilt_3ch_const_Angle_2	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	16	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__POSE__UNITY_0",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_3ch_const_Angle_0	,	FuncSp__Pan_3ch_const_Angle_0	,	FuncSp__Pan_3ch_const_Angle_0	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	25	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__POSE__UNITY_1",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_3ch_const_Angle_1	,	FuncSp__Pan_3ch_const_Angle_1	,	FuncSp__Pan_3ch_const_Angle_1	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	25	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__POSE__UNITY_2",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_3ch_const_Angle_2	,	FuncSp__Pan_3ch_const_Angle_2	,	FuncSp__Pan_3ch_const_Angle_2	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	25	,	25	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__POSE__UNITY_0",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_3ch_const_Angle_0	,	FuncSp__Tilt_3ch_const_Angle_0	,	FuncSp__Tilt_3ch_const_Angle_0	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	16	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__POSE__UNITY_1",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_3ch_const_Angle_1	,	FuncSp__Tilt_3ch_const_Angle_1	,	FuncSp__Tilt_3ch_const_Angle_1	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	16	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__POSE__UNITY_2",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_3ch_const_Angle_2	,	FuncSp__Tilt_3ch_const_Angle_2	,	FuncSp__Tilt_3ch_const_Angle_2	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	16	,	16	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// PanTilt__Triangle -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_3_PAN__TRIANGLE__1_2__PHASE_0",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_4__PHASE_0",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_8__PHASE_0",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_0	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_2__PHASE_0",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_4__PHASE_0",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_8__PHASE_0",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_0	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_2__PHASE_90__LINE",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_4__PHASE_90__LINE",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_8__PHASE_90__LINE",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_2__PHASE_90__RANDOM",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_4__PHASE_90__RANDOM",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_8__PHASE_90__RANDOM",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_45	,	FuncSp__Pan_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_2__PHASE_90__LINE",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_4__PHASE_90__LINE",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_8__PHASE_90__LINE",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_2__PHASE_90__RANDOM",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_4__PHASE_90__RANDOM",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_8__PHASE_90__RANDOM",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_45	,	FuncSp__Tilt_Triangle_phase_90	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_2__PHASE_180__LINE",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_4__PHASE_180__LINE",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_8__PHASE_180__LINE",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_2__PHASE_180__RANDOM",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_4__PHASE_180__RANDOM",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_PAN__TRIANGLE__1_8__PHASE_180__RANDOM",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Pan_Triangle_phase_0	,	FuncSp__Pan_Triangle_phase_90	,	FuncSp__Pan_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_2__PHASE_180__LINE",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_4__PHASE_180__LINE",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_8__PHASE_180__LINE",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_2__PHASE_180__RANDOM",																																																																	
		0.5	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_4__PHASE_180__RANDOM",																																																																	
		0.25	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_3_TILT__TRIANGLE__1_8__PHASE_180__RANDOM",																																																																	
		0.125	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Tilt_Triangle_phase_0	,	FuncSp__Tilt_Triangle_phase_90	,	FuncSp__Tilt_Triangle_phase_180	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	20	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	20	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// -----------------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_END",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
};																																																																			

const struct BLOCK_PATTERN Bp_2[] = {																																																																			
	// LUM__Still -------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_2_LUM__STILL__OFF",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_2_LUM__STILL__ON",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_2_LUM__STILL__ON_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_2_LUM__STILL__ON_1CH",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StillFlowBl -----------------------------------------------------------------------------------------------------------------																																																																		
	// Lum__StillFlow -----------------------------------------------------------------------------------------------------------------																																																																		
	// Lum__FlashBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_2_LUM__FLASH_BL__FLASH",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	5	,	5	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	5	,	5	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_2_LUM__FLASH_BL__FLASH_1CH",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	5	,	5	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	5	,	5	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StrobeBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_2_LUM__STROBE_BL__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_2_LUM__STROBE_BL__STROBE_x4_1CH",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_2_LUM__STROBE_BL__ORDER_x2",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_1_2_Bl	,	FuncSp__Lum_Flash_2_2_Bl	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_2_LUM__STROBE_BL__SPREAD_x2_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx2_Bl	,	FuncSp__Lum_Flashx2_2_Bl	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_LINE,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Strobe -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_2_LUM__STROBE__STROBE_x4",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_2_LUM__STROBE__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_2_LUM__STROBE__STROBE_x4_1CH",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_2_LUM__STROBE__SPREAD_x2_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx2	,	FuncSp__Lum_Flashx2_2	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RANDOM,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Ambient -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_2_LUM__AMBIENT__AMBIENT",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Ambient	,	FuncSp__Lum_Ambient	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	3	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	3	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// -----------------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_END",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
};																																																																			

const struct BLOCK_PATTERN Bp_1[] = {																																																																			
	// LUM__Still -------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_1_LUM__STILL__OFF",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_1_LUM__STILL__ON",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_1_LUM__STILL__ON_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_const_Max	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	2	,	2	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StillFlowBl -----------------------------------------------------------------------------------------------------------------																																																																		
	// Lum__StillFlow -----------------------------------------------------------------------------------------------------------------																																																																		
	// Lum__FlashBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_1_LUM__FLASH_BL__FLASH",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flash_Bl	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	5	,	5	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	5	,	5	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	1	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__StrobeBl -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_1_LUM__STROBE_BL__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4_Bl	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	1	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Strobe -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_1_LUM__STROBE__STROBE_x4",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
	{	"BP_1_LUM__STROBE__STROBE_x4_OFF",																																																																	
		1	,	// Speed																																																															
		1	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Flashx4	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	FuncSp__Lum_const_Zero	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	1	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// Lum__Ambient -----------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_1_LUM__AMBIENT__AMBIENT",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	FuncSp__Lum_Ambient	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	1	,	0	}, },	{ {	0	,	0	}, {	3	,	3	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	3	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
																																																																			
	// -----------------------------------------------------------------------------------------------------------------------------																																																																		
	{	"BP_END",																																																																	
		1	,	// Speed																																																															
		0	,	// StartPatternId_Candidate																																																															
		{																																																																	
			{	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	,	NULL	},																																																		
		},																																																																	
		SYMMETRY_RIGID,																																																																	
		{ //		STATE_NOSOUND										STATE_SOUND								STATE_SOUND_DROP									STATE_BEAT_IN									STATE_BEAT_IN_DROP									STATE_FLYWHEEL									STATE_FLYWHEEL_DROP									
		// 			Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self					Beat				Self				
/*Fix Panel*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*Fix Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov RGB*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Strobe*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Pan*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
/*mov Tilt*/			{	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	{ {	0	,	0	}, {	0	,	0	}, },	},
		},																																																																	
	},																																																																		
};																																																																			


/************************************************************************************************************************/
} // namespace SPACE_LIGHT{
	
	
