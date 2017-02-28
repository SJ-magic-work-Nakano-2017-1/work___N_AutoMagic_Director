/************************************************************
ShortPattern definition
	double (*pFunc)(int)
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ofMain.h"

#include "am_common.h"
#include "vj_common.h"
#include "vj_ShortPattern.h"



/************************************************************************************************************************/
namespace SPACE_VJ{




/************************************************************
************************************************************/


/************************************************************
param
************************************************************/
/********************
for test code
********************/
static PFUNC_VJ_SHORTPATTERN pFunc[] = {
	FUNC_SP_VJ::FuncSp__const_Zero,
	FUNC_SP_VJ::FuncSp__const_Max,
	FUNC_SP_VJ::FuncSp__Flash,
	FUNC_SP_VJ::FuncSp__Flash_Bl,
	FUNC_SP_VJ::FuncSp__Flash_x4,
	FUNC_SP_VJ::FuncSp__Flash_x4_Bl,
	FUNC_SP_VJ::FuncSp__sin,
	FUNC_SP_VJ::FuncSp__Square_x2,
	FUNC_SP_VJ::FuncSp__Square_x2_Bl,
	FUNC_SP_VJ::FuncSp__Square_x1,
	FUNC_SP_VJ::FuncSp__Square_x1_Bl,
	FUNC_SP_VJ::FuncSp__Trape_On,
	FUNC_SP_VJ::FuncSp__Trape_Off,
};

static const int Num_ShortPatterns = sizeof(pFunc) / sizeof(pFunc[0]);



/************************************************************
function prototype
************************************************************/


/************************************************************
function
************************************************************/

/******************************
test code
	void VJ::test()
	に記述(FUNC_SP_VJ::FuncSp_test();)して、vj.test()をvoid AUTOMAGIC_CORE::test()から呼ぶ
******************************/
void FUNC_SP_VJ::FuncSp_test()
{
	for(int i = 0; i < Num_ShortPatterns; i++){
		char buf[1000];
		sprintf(buf, "../../../test_sp_%d.csv", i);
		
		FILE* fp;
		fp = fopen(buf, "w");
		if(fp == NULL){
			printf("File open Error\n");
			std::exit(1);
		}
		
		const int offset = 2000;
		for(int j = -offset; j < MAXPROGRESS_ANIM_KEY + offset; j+= 10){
			const double phase_deg = 45.5;
			
			double val = pFunc[i](j, phase_deg);
			fprintf_Log_forTestCode(fp, "%d,%f\n", j, val);
		}
		
		
		fclose(fp);
	}
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__const_Zero(const int Progress, const double phase_deg)
{
	return 0;
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__const_Max(const int Progress, const double phase_deg)
{
	return 1.0;
}

/******************************
******************************/
double FUNC_SP_VJ::Flash(const int Progress, const int MaxProgress)
{
	if(Progress < 0){
		return 1.0;
	}else if(MaxProgress <= Progress){
		return 0;
	}else{
		return ( -1.0 / MaxProgress) * Progress + 1.0;
	}
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__Flash(const int Progress, const double phase_deg)
{
	return Flash(Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__Flash_Bl(const int Progress, const double phase_deg)
{
	return Flash(Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
double FUNC_SP_VJ::Flash_xN(int Progress, const int MaxProgress, const int N)
{
	if(Progress < 0){
		return 1.0;
	}else if(MaxProgress <= Progress){
		return 0;
	}else{
		Progress = (Progress * N) % MaxProgress;
		
		return ( -1.0 / MaxProgress) * Progress + 1.0;
	}
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__Flash_x4(const int Progress, const double phase_deg)
{
	return Flash_xN(Progress, MAXPROGRESS_ANIM_KEY, 4);
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__Flash_x4_Bl(const int Progress, const double phase_deg)
{
	return Flash_xN(Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO, 4);
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__sin(const int Progress, const double phase_deg)
{
	// const double PI = 3.14159265398979;
	double phase = (MAXPROGRESS_ANIM_KEY * phase_deg) / 360;
	
	return 0.5 + 0.5 * sin(2 * PI * (Progress + phase) / MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
double FUNC_SP_VJ::Square_xN(int Progress, const int MaxProgress, const int N)
{
	if(Progress < 0){
		return 1.0;
	}else if(MaxProgress <= Progress){
		return 0;
	}else{
		Progress = (Progress * N) % MaxProgress;
		
		if(Progress < MaxProgress/2)	return 1.0;
		else							return 0.0;
	}
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__Square_x2(const int Progress, const double phase_deg)
{
	return Square_xN(Progress, MAXPROGRESS_ANIM_KEY, 2);
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__Square_x2_Bl(const int Progress, const double phase_deg)
{
	return Square_xN(Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO, 2);
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__Square_x1(const int Progress, const double phase_deg)
{
	return Square_xN(Progress, MAXPROGRESS_ANIM_KEY, 1);
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__Square_x1_Bl(const int Progress, const double phase_deg)
{
	return Square_xN(Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO, 1);
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__Trape_On(const int Progress, const double phase_deg)
{
	const double thresh = 700;
	const double tan = 1.0/thresh;
	
	if(Progress < 0)			return 0;
	else if(thresh < Progress)	return 1.0;
	else						return tan * Progress;
}

/******************************
******************************/
double FUNC_SP_VJ::FuncSp__Trape_Off(const int Progress, const double phase_deg)
{
	const double thresh = 700;
	const double tan = -1.0/thresh;
	
	if(Progress < 0)			return 1.0;
	else if(thresh < Progress)	return 0.0;
	else						return tan * Progress + 1.0;
}

	
/************************************************************************************************************************/
} // namespace SPACE_VJ{
	
	
