/************************************************************
ShortPattern definition
	int (*pFunc)(int)
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ofMain.h"

#include "am_common.h"
#include "L_common.h"
#include "L_ShortPattern.h"

/************************************************************************************************************************/
namespace SPACE_LIGHT{



/************************************************************
************************************************************/
enum{
	LUM_MAX = 255,
	LUM_LOW = 50,
	
	
	PANTILT_MAX = 65535,
	
	PAN_TRIANGLE_CENTER	= 43690,
	PAN_TRIANGLE_AMP	= 7282,
	
	TILT_TRIANGLE_CENTER	= 14043,
	TILT_TRIANGLE_AMP		= 14043,
};

/************************************************************
param
************************************************************/
/********************
for test code
********************/
static PFUNC_SHORTPATTERN pFunc[] = {
	FuncSp__Lum_const_Zero,
	FuncSp__Lum_const_Max,
	FuncSp__Lum_const_Low,
	FuncSp__Lum_Flash,
	FuncSp__Lum_Flash_Bl,
	FuncSp__Lum_Ambient,
	FuncSp__Lum_On_1_3,
	FuncSp__Lum_On_1_3_Bl,
	FuncSp__Lum_On_2_3,
	FuncSp__Lum_On_2_3_Bl,
	FuncSp__Lum_On_3_3,
	FuncSp__Lum_On_3_3_Bl,
	FuncSp__Lum_On_1_4,
	FuncSp__Lum_On_1_4_Bl,
	FuncSp__Lum_On_2_4,
	FuncSp__Lum_On_2_4_Bl,
	FuncSp__Lum_On_3_4,
	FuncSp__Lum_On_3_4_Bl,
	FuncSp__Lum_On_4_4,
	FuncSp__Lum_On_4_4_Bl,
	FuncSp__Lum_On_1_5,
	FuncSp__Lum_On_1_5_Bl,
	FuncSp__Lum_On_2_5,
	FuncSp__Lum_On_2_5_Bl,
	FuncSp__Lum_On_3_5,
	FuncSp__Lum_On_3_5_Bl,
	FuncSp__Lum_On_4_5,
	FuncSp__Lum_On_4_5_Bl,
	FuncSp__Lum_On_5_5,
	FuncSp__Lum_On_5_5_Bl,
	FuncSp__Lum_On_1_7,
	FuncSp__Lum_On_1_7_Bl,
	FuncSp__Lum_On_2_7,
	FuncSp__Lum_On_2_7_Bl,
	FuncSp__Lum_On_3_7,
	FuncSp__Lum_On_3_7_Bl,
	FuncSp__Lum_On_4_7,
	FuncSp__Lum_On_4_7_Bl,
	FuncSp__Lum_On_5_7,
	FuncSp__Lum_On_5_7_Bl,
	FuncSp__Lum_On_6_7,
	FuncSp__Lum_On_6_7_Bl,
	FuncSp__Lum_On_7_7,
	FuncSp__Lum_On_7_7_Bl,
	FuncSp__Lum_Off_1_3,
	FuncSp__Lum_Off_1_3_Bl,
	FuncSp__Lum_Off_2_3,
	FuncSp__Lum_Off_2_3_Bl,
	FuncSp__Lum_Off_3_3,
	FuncSp__Lum_Off_3_3_Bl,
	FuncSp__Lum_Off_1_4,
	FuncSp__Lum_Off_1_4_Bl,
	FuncSp__Lum_Off_2_4,
	FuncSp__Lum_Off_2_4_Bl,
	FuncSp__Lum_Off_3_4,
	FuncSp__Lum_Off_3_4_Bl,
	FuncSp__Lum_Off_4_4,
	FuncSp__Lum_Off_4_4_Bl,
	FuncSp__Lum_Off_1_5,
	FuncSp__Lum_Off_1_5_Bl,
	FuncSp__Lum_Off_2_5,
	FuncSp__Lum_Off_2_5_Bl,
	FuncSp__Lum_Off_3_5,
	FuncSp__Lum_Off_3_5_Bl,
	FuncSp__Lum_Off_4_5,
	FuncSp__Lum_Off_4_5_Bl,
	FuncSp__Lum_Off_5_5,
	FuncSp__Lum_Off_5_5_Bl,
	FuncSp__Lum_Off_1_7,
	FuncSp__Lum_Off_1_7_Bl,
	FuncSp__Lum_Off_2_7,
	FuncSp__Lum_Off_2_7_Bl,
	FuncSp__Lum_Off_3_7,
	FuncSp__Lum_Off_3_7_Bl,
	FuncSp__Lum_Off_4_7,
	FuncSp__Lum_Off_4_7_Bl,
	FuncSp__Lum_Off_5_7,
	FuncSp__Lum_Off_5_7_Bl,
	FuncSp__Lum_Off_6_7,
	FuncSp__Lum_Off_6_7_Bl,
	FuncSp__Lum_Off_7_7,
	FuncSp__Lum_Off_7_7_Bl,
	FuncSp__Lum_Flash_1_2,
	FuncSp__Lum_Flash_1_2_Bl,
	FuncSp__Lum_Flash_2_2,
	FuncSp__Lum_Flash_2_2_Bl,
	FuncSp__Lum_Flash_1_3,
	FuncSp__Lum_Flash_1_3_Bl,
	FuncSp__Lum_Flash_2_3,
	FuncSp__Lum_Flash_2_3_Bl,
	FuncSp__Lum_Flash_3_3,
	FuncSp__Lum_Flash_3_3_Bl,
	FuncSp__Lum_Flash_1_4,
	FuncSp__Lum_Flash_1_4_Bl,
	FuncSp__Lum_Flash_2_4,
	FuncSp__Lum_Flash_2_4_Bl,
	FuncSp__Lum_Flash_3_4,
	FuncSp__Lum_Flash_3_4_Bl,
	FuncSp__Lum_Flash_4_4,
	FuncSp__Lum_Flash_4_4_Bl,
	FuncSp__Lum_Flash_1_5,
	FuncSp__Lum_Flash_1_5_Bl,
	FuncSp__Lum_Flash_2_5,
	FuncSp__Lum_Flash_2_5_Bl,
	FuncSp__Lum_Flash_3_5,
	FuncSp__Lum_Flash_3_5_Bl,
	FuncSp__Lum_Flash_4_5,
	FuncSp__Lum_Flash_4_5_Bl,
	FuncSp__Lum_Flash_5_5,
	FuncSp__Lum_Flash_5_5_Bl,
	FuncSp__Lum_Flash_1_7,
	FuncSp__Lum_Flash_1_7_Bl,
	FuncSp__Lum_Flash_2_7,
	FuncSp__Lum_Flash_2_7_Bl,
	FuncSp__Lum_Flash_3_7,
	FuncSp__Lum_Flash_3_7_Bl,
	FuncSp__Lum_Flash_4_7,
	FuncSp__Lum_Flash_4_7_Bl,
	FuncSp__Lum_Flash_5_7,
	FuncSp__Lum_Flash_5_7_Bl,
	FuncSp__Lum_Flash_6_7,
	FuncSp__Lum_Flash_6_7_Bl,
	FuncSp__Lum_Flash_7_7,
	FuncSp__Lum_Flash_7_7_Bl,
	FuncSp__Lum_Flashx2,
	FuncSp__Lum_Flashx2_Bl,
	FuncSp__Lum_Flashx2_2,
	FuncSp__Lum_Flashx2_2_Bl,
	FuncSp__Lum_Flashx3,
	FuncSp__Lum_Flashx3_Bl,
	FuncSp__Lum_Flashx3_2,
	FuncSp__Lum_Flashx3_2_Bl,
	FuncSp__Lum_Flashx3_3,
	FuncSp__Lum_Flashx3_3_Bl,
	FuncSp__Lum_Flashx4,
	FuncSp__Lum_Flashx4_Bl,
	FuncSp__Lum_Flashx4_2,
	FuncSp__Lum_Flashx4_2_Bl,
	FuncSp__Lum_Flashx4_3,
	FuncSp__Lum_Flashx4_3_Bl,
	FuncSp__Lum_Flashx4_4,
	FuncSp__Lum_Flashx4_4_Bl,
	FuncSp__Lum_Flashx5,
	FuncSp__Lum_Flashx5_Bl,
	FuncSp__Lum_Flashx5_2,
	FuncSp__Lum_Flashx5_2_Bl,
	FuncSp__Lum_Flashx5_3,
	FuncSp__Lum_Flashx5_3_Bl,
	FuncSp__Lum_Flashx5_4,
	FuncSp__Lum_Flashx5_4_Bl,
	FuncSp__Lum_Flashx5_5,
	FuncSp__Lum_Flashx5_5_Bl,
	FuncSp__Lum_Flashx7,
	FuncSp__Lum_Flashx7_Bl,
	FuncSp__Lum_Flashx7_2,
	FuncSp__Lum_Flashx7_2_Bl,
	FuncSp__Lum_Flashx7_3,
	FuncSp__Lum_Flashx7_3_Bl,
	FuncSp__Lum_Flashx7_4,
	FuncSp__Lum_Flashx7_4_Bl,
	FuncSp__Lum_Flashx7_5,
	FuncSp__Lum_Flashx7_5_Bl,
	FuncSp__Lum_Flashx7_6,
	FuncSp__Lum_Flashx7_6_Bl,
	FuncSp__Lum_Flashx7_7,
	FuncSp__Lum_Flashx7_7_Bl,
	FuncSp__Pan_3ch_const_Angle_0,
	FuncSp__Pan_3ch_const_Angle_1,
	FuncSp__Pan_3ch_const_Angle_2,
	FuncSp__Tilt_3ch_const_Angle_0,
	FuncSp__Tilt_3ch_const_Angle_1,
	FuncSp__Tilt_3ch_const_Angle_2,
	FuncSp__Pan_7ch_const_Angle_0,
	FuncSp__Pan_7ch_const_Angle_1,
	FuncSp__Pan_7ch_const_Angle_2,
	FuncSp__Pan_7ch_const_Angle_3,
	FuncSp__Pan_7ch_const_Angle_4,
	FuncSp__Pan_7ch_const_Angle_5,
	FuncSp__Pan_7ch_const_Angle_6,
	FuncSp__Tilt_7ch_const_Angle_0,
	FuncSp__Tilt_7ch_const_Angle_1,
	FuncSp__Tilt_7ch_const_Angle_2,
	FuncSp__Tilt_7ch_const_Angle_3,
	FuncSp__Tilt_7ch_const_Angle_4,
	FuncSp__Tilt_7ch_const_Angle_5,
	FuncSp__Tilt_7ch_const_Angle_6,
	FuncSp__Pan_Triangle_phase_0,
	FuncSp__Pan_Triangle_phase_15,
	FuncSp__Pan_Triangle_phase_30,
	FuncSp__Pan_Triangle_phase_45,
	FuncSp__Pan_Triangle_phase_60,
	FuncSp__Pan_Triangle_phase_75,
	FuncSp__Pan_Triangle_phase_90,
	FuncSp__Pan_Triangle_phase_105,
	FuncSp__Pan_Triangle_phase_120,
	FuncSp__Pan_Triangle_phase_135,
	FuncSp__Pan_Triangle_phase_150,
	FuncSp__Pan_Triangle_phase_165,
	FuncSp__Pan_Triangle_phase_180,
	FuncSp__Tilt_Triangle_phase_0,
	FuncSp__Tilt_Triangle_phase_15,
	FuncSp__Tilt_Triangle_phase_30,
	FuncSp__Tilt_Triangle_phase_45,
	FuncSp__Tilt_Triangle_phase_60,
	FuncSp__Tilt_Triangle_phase_75,
	FuncSp__Tilt_Triangle_phase_90,
	FuncSp__Tilt_Triangle_phase_105,
	FuncSp__Tilt_Triangle_phase_120,
	FuncSp__Tilt_Triangle_phase_135,
	FuncSp__Tilt_Triangle_phase_150,
	FuncSp__Tilt_Triangle_phase_165,
	FuncSp__Tilt_Triangle_phase_180,
};
static const int Num_ShortPatterns = sizeof(pFunc) / sizeof(pFunc[0]);



/************************************************************
function prototype
************************************************************/
static int Lum_Flash(const int Progress, const int MaxProgress);
static int Lum_On_x_x(const int num, const int den, const int Progress, const int MaxProgress);
static int Lum_Off_x_x(const int num, const int den, const int Progress, const int MaxProgress);
static int Lum_Flash_x_x(const int num, const int den, const int Progress, const int MaxProgress);
static int Lum_FlashxX_x(const int num, const int den, const int Progress, const int MaxProgress);
static int PanTilt_Triangle(const int Progress, const int center, const int Amp, const int phase_deg);


/************************************************************
function
************************************************************/

/******************************
test code
	void LIGHT::test()
	Ç…ãLèqÇµÇƒÅAlight.test()Çvoid AUTOMAGIC_CORE::test()Ç©ÇÁåƒÇ‘
******************************/
void FuncSp_test()
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
			int val = pFunc[i](j);
			fprintf_Log_forTestCode(fp, "%d,%d\n", j, val);
		}
		
		fclose(fp);
	}
}

/******************************
******************************/
int FuncSp__Lum_const_Zero(const int Progress)
{
	return 0;
}

/******************************
******************************/
int FuncSp__Lum_const_Max(const int Progress)
{
	return LUM_MAX;
}

/******************************
******************************/
int FuncSp__Lum_const_Low(const int Progress)
{
	return LUM_LOW;
}

/******************************
******************************/
int Lum_Flash(const int Progress, const int MaxProgress)
{
	if(Progress < 0){
		return LUM_MAX;
	}else if(MaxProgress <= Progress){
		return 0;
	}else{
		return int (-(double(LUM_MAX) / MaxProgress) * Progress + LUM_MAX);
	}
}

/******************************
******************************/
int FuncSp__Lum_Flash(const int Progress)
{
	return Lum_Flash(Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_Bl(const int Progress)
{
	return Lum_Flash(Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Ambient(const int Progress)
{
	if(Progress < 0){
		return 0;
	}else if(MAXPROGRESS_ANIM_KEY <= Progress){
		return 0;
	}else{
		if(Progress < MAXPROGRESS_ANIM_KEY/2){
			return int(Progress * double(LUM_MAX) / (MAXPROGRESS_ANIM_KEY / 2));
		}else{
			return int ((Progress - (MAXPROGRESS_ANIM_KEY / 2)) * (double(-LUM_MAX) / (MAXPROGRESS_ANIM_KEY / 2)) + LUM_MAX);
		}
	}
}

/******************************
******************************/
int Lum_On_x_x(const int num, const int den, const int Progress, const int MaxProgress)
{
	if(Progress < 0){
		return 0;
	}else if(MaxProgress < Progress){
		return LUM_MAX;
	}else{
		if(Progress < MaxProgress * (num - 1) / den){
			return 0;
		}else{
			return LUM_MAX;
		}
	}
}

/******************************
******************************/
int FuncSp__Lum_On_1_3(const int Progress)
{
	return LUM_MAX;
}

/******************************
******************************/
int FuncSp__Lum_On_1_3_Bl(const int Progress)
{
	return LUM_MAX;
}

/******************************
******************************/
int FuncSp__Lum_On_2_3(int Progress)
{
	return Lum_On_x_x(2, 3, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_2_3_Bl(int Progress)
{
	return Lum_On_x_x(2, 3, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_3_3(int Progress)
{
	return Lum_On_x_x(3, 3, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_3_3_Bl(int Progress)
{
	return Lum_On_x_x(3, 3, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_1_4(const int Progress)
{
	return LUM_MAX;
}

/******************************
******************************/
int FuncSp__Lum_On_1_4_Bl(const int Progress)
{
	return LUM_MAX;
}

/******************************
******************************/
int FuncSp__Lum_On_2_4(int Progress)
{
	return Lum_On_x_x(2, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_2_4_Bl(int Progress)
{
	return Lum_On_x_x(2, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_3_4(int Progress)
{
	return Lum_On_x_x(3, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_3_4_Bl(int Progress)
{
	return Lum_On_x_x(3, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_4_4(int Progress)
{
	return Lum_On_x_x(4, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_4_4_Bl(int Progress)
{
	return Lum_On_x_x(4, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_1_5(const int Progress)
{
	return LUM_MAX;
}

/******************************
******************************/
int FuncSp__Lum_On_1_5_Bl(const int Progress)
{
	return LUM_MAX;
}

/******************************
******************************/
int FuncSp__Lum_On_2_5(int Progress)
{
	return Lum_On_x_x(2, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_2_5_Bl(int Progress)
{
	return Lum_On_x_x(2, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_3_5(int Progress)
{
	return Lum_On_x_x(3, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_3_5_Bl(int Progress)
{
	return Lum_On_x_x(3, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_4_5(int Progress)
{
	return Lum_On_x_x(4, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_4_5_Bl(int Progress)
{
	return Lum_On_x_x(4, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_5_5(int Progress)
{
	return Lum_On_x_x(5, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_5_5_Bl(int Progress)
{
	return Lum_On_x_x(5, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_1_7(const int Progress)
{
	return LUM_MAX;
}

/******************************
******************************/
int FuncSp__Lum_On_1_7_Bl(const int Progress)
{
	return LUM_MAX;
}

/******************************
******************************/
int FuncSp__Lum_On_2_7(int Progress)
{
	return Lum_On_x_x(2, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_2_7_Bl(int Progress)
{
	return Lum_On_x_x(2, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_3_7(int Progress)
{
	return Lum_On_x_x(3, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_3_7_Bl(int Progress)
{
	return Lum_On_x_x(3, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_4_7(int Progress)
{
	return Lum_On_x_x(4, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_4_7_Bl(int Progress)
{
	return Lum_On_x_x(4, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_5_7(int Progress)
{
	return Lum_On_x_x(5, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_5_7_Bl(int Progress)
{
	return Lum_On_x_x(5, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_6_7(int Progress)
{
	return Lum_On_x_x(6, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_6_7_Bl(int Progress)
{
	return Lum_On_x_x(6, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_On_7_7(int Progress)
{
	return Lum_On_x_x(7, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_On_7_7_Bl(int Progress)
{
	return Lum_On_x_x(7, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int Lum_Off_x_x(const int num, const int den, const int Progress, const int MaxProgress)
{
	if(Progress < 0){
		return LUM_MAX;
	}else if(MaxProgress <= Progress){
		return 0;
	}else{
		if(Progress <= MaxProgress * (num - 1) / den){
			return LUM_MAX;
		}else{
			return 0;
		}
	}
}

/******************************
******************************/
int FuncSp__Lum_Off_1_3(const int Progress)
{
	return 0;
}

/******************************
******************************/
int FuncSp__Lum_Off_1_3_Bl(const int Progress)
{
	return 0;
}

/******************************
******************************/
int FuncSp__Lum_Off_2_3(int Progress)
{
	return Lum_Off_x_x(2, 3, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_2_3_Bl(int Progress)
{
	return Lum_Off_x_x(2, 3, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_3_3(int Progress)
{
	return Lum_Off_x_x(3, 3, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_3_3_Bl(int Progress)
{
	return Lum_Off_x_x(3, 3, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_1_4(const int Progress)
{
	return 0;
}

/******************************
******************************/
int FuncSp__Lum_Off_1_4_Bl(const int Progress)
{
	return 0;
}

/******************************
******************************/
int FuncSp__Lum_Off_2_4(int Progress)
{
	return Lum_Off_x_x(2, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_2_4_Bl(int Progress)
{
	return Lum_Off_x_x(2, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_3_4(int Progress)
{
	return Lum_Off_x_x(3, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_3_4_Bl(int Progress)
{
	return Lum_Off_x_x(3, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_4_4(int Progress)
{
	return Lum_Off_x_x(4, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_4_4_Bl(int Progress)
{
	return Lum_Off_x_x(4, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_1_5(const int Progress)
{
	return 0;
}

/******************************
******************************/
int FuncSp__Lum_Off_1_5_Bl(const int Progress)
{
	return 0;
}

/******************************
******************************/
int FuncSp__Lum_Off_2_5(int Progress)
{
	return Lum_Off_x_x(2, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_2_5_Bl(int Progress)
{
	return Lum_Off_x_x(2, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_3_5(int Progress)
{
	return Lum_Off_x_x(3, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_3_5_Bl(int Progress)
{
	return Lum_Off_x_x(3, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_4_5(int Progress)
{
	return Lum_Off_x_x(4, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_4_5_Bl(int Progress)
{
	return Lum_Off_x_x(4, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_5_5(int Progress)
{
	return Lum_Off_x_x(5, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_5_5_Bl(int Progress)
{
	return Lum_Off_x_x(5, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_1_7(const int Progress)
{
	return 0;
}

/******************************
******************************/
int FuncSp__Lum_Off_1_7_Bl(const int Progress)
{
	return 0;
}

/******************************
******************************/
int FuncSp__Lum_Off_2_7(int Progress)
{
	return Lum_Off_x_x(2, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_2_7_Bl(int Progress)
{
	return Lum_Off_x_x(2, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_3_7(int Progress)
{
	return Lum_Off_x_x(3, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_3_7_Bl(int Progress)
{
	return Lum_Off_x_x(3, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_4_7(int Progress)
{
	return Lum_Off_x_x(4, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_4_7_Bl(int Progress)
{
	return Lum_Off_x_x(4, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_5_7(int Progress)
{
	return Lum_Off_x_x(5, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_5_7_Bl(int Progress)
{
	return Lum_Off_x_x(5, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_6_7(int Progress)
{
	return Lum_Off_x_x(6, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_6_7_Bl(int Progress)
{
	return Lum_Off_x_x(6, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Off_7_7(int Progress)
{
	return Lum_Off_x_x(7, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Off_7_7_Bl(int Progress)
{
	return Lum_Off_x_x(7, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int Lum_Flash_x_x(const int num, const int den, const int Progress, const int MaxProgress)
{
	if(Progress < 0){
		return 0;
	}else if(MaxProgress <= Progress){
		return 0;
	}else{
		int ProgressFrom	= MaxProgress * (num - 1) / den;
		int ProgressTo		= MaxProgress * num / den;
		
		if( (Progress < ProgressFrom) || (ProgressTo < Progress) ){
			return 0;
		}else{
			double a = - double(LUM_MAX) * den / MaxProgress;
			
			int val = int(a * (Progress - ProgressFrom) + LUM_MAX);
			if(val < 0)			val = 0;
			if(LUM_MAX < val)	val = LUM_MAX;
			
			return val;
		}
	}
}

/******************************
******************************/
int FuncSp__Lum_Flash_1_2(const int Progress)
{
	return Lum_Flash_x_x(1, 2, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_1_2_Bl(const int Progress)
{
	return Lum_Flash_x_x(1, 2, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_2_2(const int Progress)
{
	return Lum_Flash_x_x(2, 2, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_2_2_Bl(const int Progress)
{
	return Lum_Flash_x_x(2, 2, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_1_3(const int Progress)
{
	return Lum_Flash_x_x(1, 3, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_1_3_Bl(const int Progress)
{
	return Lum_Flash_x_x(1, 3, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_2_3(const int Progress)
{
	return Lum_Flash_x_x(2, 3, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_2_3_Bl(const int Progress)
{
	return Lum_Flash_x_x(2, 3, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_3_3(const int Progress)
{
	return Lum_Flash_x_x(3, 3, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_3_3_Bl(const int Progress)
{
	return Lum_Flash_x_x(3, 3, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_1_4(const int Progress)
{
	return Lum_Flash_x_x(1, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_1_4_Bl(const int Progress)
{
	return Lum_Flash_x_x(1, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_2_4(const int Progress)
{
	return Lum_Flash_x_x(2, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_2_4_Bl(const int Progress)
{
	return Lum_Flash_x_x(2, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_3_4(const int Progress)
{
	return Lum_Flash_x_x(3, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_3_4_Bl(const int Progress)
{
	return Lum_Flash_x_x(3, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_4_4(const int Progress)
{
	return Lum_Flash_x_x(4, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_4_4_Bl(const int Progress)
{
	return Lum_Flash_x_x(4, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_1_5(const int Progress)
{
	return Lum_Flash_x_x(1, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_1_5_Bl(const int Progress)
{
	return Lum_Flash_x_x(1, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_2_5(const int Progress)
{
	return Lum_Flash_x_x(2, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_2_5_Bl(const int Progress)
{
	return Lum_Flash_x_x(2, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_3_5(const int Progress)
{
	return Lum_Flash_x_x(3, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_3_5_Bl(const int Progress)
{
	return Lum_Flash_x_x(3, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_4_5(const int Progress)
{
	return Lum_Flash_x_x(4, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_4_5_Bl(const int Progress)
{
	return Lum_Flash_x_x(4, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_5_5(const int Progress)
{
	return Lum_Flash_x_x(5, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_5_5_Bl(const int Progress)
{
	return Lum_Flash_x_x(5, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_1_7(const int Progress)
{
	return Lum_Flash_x_x(1, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_1_7_Bl(const int Progress)
{
	return Lum_Flash_x_x(1, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_2_7(const int Progress)
{
	return Lum_Flash_x_x(2, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_2_7_Bl(const int Progress)
{
	return Lum_Flash_x_x(2, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_3_7(const int Progress)
{
	return Lum_Flash_x_x(3, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_3_7_Bl(const int Progress)
{
	return Lum_Flash_x_x(3, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_4_7(const int Progress)
{
	return Lum_Flash_x_x(4, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_4_7_Bl(const int Progress)
{
	return Lum_Flash_x_x(4, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_5_7(const int Progress)
{
	return Lum_Flash_x_x(5, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_5_7_Bl(const int Progress)
{
	return Lum_Flash_x_x(5, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_6_7(const int Progress)
{
	return Lum_Flash_x_x(6, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_6_7_Bl(const int Progress)
{
	return Lum_Flash_x_x(6, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flash_7_7(const int Progress)
{
	return Lum_Flash_x_x(7, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flash_7_7_Bl(const int Progress)
{
	return Lum_Flash_x_x(7, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int Lum_FlashxX_x(const int num, const int den, const int Progress, const int MaxProgress)
{
	if(Progress < 0){
		return 0;
	}else if(MaxProgress <= Progress){
		return 0;
	}else{
		
		double Width = double(MaxProgress) / den;
		double a = -LUM_MAX / Width;
		
		int ZoneId = int(Progress / Width); // which "Zone id" the "Progress" of this time belongs.
		
		if( (num - 1) <= ZoneId ){
			int val = int(a * (Progress - Width * ZoneId) + LUM_MAX);
			if(val < 0)			val = 0;
			if(LUM_MAX < val)	val = LUM_MAX;
			
			return val;
			
		}else{
			return 0;
		}
	}
}

/******************************
******************************/
int FuncSp__Lum_Flashx2(const int Progress)
{
	return Lum_FlashxX_x(1, 2, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx2_Bl(const int Progress)
{
	return Lum_FlashxX_x(1, 2, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx2_2(const int Progress)
{
	return Lum_FlashxX_x(2, 2, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx2_2_Bl(const int Progress)
{
	return Lum_FlashxX_x(2, 2, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx3(const int Progress)
{
	return Lum_FlashxX_x(1, 3, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx3_Bl(const int Progress)
{
	return Lum_FlashxX_x(1, 3, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx3_2(const int Progress)
{
	return Lum_FlashxX_x(2, 3, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx3_2_Bl(const int Progress)
{
	return Lum_FlashxX_x(2, 3, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx3_3(const int Progress)
{
	return Lum_FlashxX_x(3, 3, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx3_3_Bl(const int Progress)
{
	return Lum_FlashxX_x(3, 3, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx4(const int Progress)
{
	return Lum_FlashxX_x(1, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx4_Bl(const int Progress)
{
	return Lum_FlashxX_x(1, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx4_2(const int Progress)
{
	return Lum_FlashxX_x(2, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx4_2_Bl(const int Progress)
{
	return Lum_FlashxX_x(2, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx4_3(const int Progress)
{
	return Lum_FlashxX_x(3, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx4_3_Bl(const int Progress)
{
	return Lum_FlashxX_x(3, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}
/******************************
******************************/
int FuncSp__Lum_Flashx4_4(const int Progress)
{
	return Lum_FlashxX_x(4, 4, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx4_4_Bl(const int Progress)
{
	return Lum_FlashxX_x(4, 4, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx5(const int Progress)
{
	return Lum_FlashxX_x(1, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx5_Bl(const int Progress)
{
	return Lum_FlashxX_x(1, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx5_2(const int Progress)
{
	return Lum_FlashxX_x(2, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx5_2_Bl(const int Progress)
{
	return Lum_FlashxX_x(2, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx5_3(const int Progress)
{
	return Lum_FlashxX_x(3, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx5_3_Bl(const int Progress)
{
	return Lum_FlashxX_x(3, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx5_4(const int Progress)
{
	return Lum_FlashxX_x(4, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx5_4_Bl(const int Progress)
{
	return Lum_FlashxX_x(4, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx5_5(const int Progress)
{
	return Lum_FlashxX_x(5, 5, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx5_5_Bl(const int Progress)
{
	return Lum_FlashxX_x(5, 5, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7(const int Progress)
{
	return Lum_FlashxX_x(1, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_Bl(const int Progress)
{
	return Lum_FlashxX_x(1, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_2(const int Progress)
{
	return Lum_FlashxX_x(2, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_2_Bl(const int Progress)
{
	return Lum_FlashxX_x(2, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_3(const int Progress)
{
	return Lum_FlashxX_x(3, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_3_Bl(const int Progress)
{
	return Lum_FlashxX_x(3, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_4(const int Progress)
{
	return Lum_FlashxX_x(4, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_4_Bl(const int Progress)
{
	return Lum_FlashxX_x(4, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_5(const int Progress)
{
	return Lum_FlashxX_x(5, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_5_Bl(const int Progress)
{
	return Lum_FlashxX_x(5, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_6(const int Progress)
{
	return Lum_FlashxX_x(6, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_6_Bl(const int Progress)
{
	return Lum_FlashxX_x(6, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_7(const int Progress)
{
	return Lum_FlashxX_x(7, 7, Progress, MAXPROGRESS_ANIM_KEY);
}

/******************************
******************************/
int FuncSp__Lum_Flashx7_7_Bl(const int Progress)
{
	return Lum_FlashxX_x(7, 7, Progress, MAXPROGRESS_ANIM_KEY_x_VALID_RATIO);
}


/******************************
******************************/
int FuncSp__Pan_3ch_const_Angle_0(const int Progress)
{
	return 36408; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Pan_3ch_const_Angle_1(const int Progress)
{
	return 43689; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Pan_3ch_const_Angle_2(const int Progress)
{
	return 50970; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Tilt_3ch_const_Angle_0(const int Progress)
{
	return 0; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Tilt_3ch_const_Angle_1(const int Progress)
{
	return 14043; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Tilt_3ch_const_Angle_2(const int Progress)
{
	return 28086; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Pan_7ch_const_Angle_0(const int Progress)
{
	return 36408; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Pan_7ch_const_Angle_1(const int Progress)
{
	return 38835; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Pan_7ch_const_Angle_2(const int Progress)
{
	return 41262; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Pan_7ch_const_Angle_3(const int Progress)
{
	return 43689; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Pan_7ch_const_Angle_4(const int Progress)
{
	return 46116; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Pan_7ch_const_Angle_5(const int Progress)
{
	return 48543; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Pan_7ch_const_Angle_6(const int Progress)
{
	return 50970; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Tilt_7ch_const_Angle_0(const int Progress)
{
	return 0; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Tilt_7ch_const_Angle_1(const int Progress)
{
	return 4681; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Tilt_7ch_const_Angle_2(const int Progress)
{
	return 9362; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Tilt_7ch_const_Angle_3(const int Progress)
{
	return 14043; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Tilt_7ch_const_Angle_4(const int Progress)
{
	return 18724; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Tilt_7ch_const_Angle_5(const int Progress)
{
	return 23405; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int FuncSp__Tilt_7ch_const_Angle_6(const int Progress)
{
	return 28086; // é¿ë™ÇÊÇË
}

/******************************
******************************/
int PanTilt_Triangle(const int Progress, const int center, const int Amp, const int phase_deg)
{
	double phase = MAXPROGRESS_ANIM_KEY * phase_deg / 360;
	
	double ret =	Amp * 8 / pow(PI, 2) * 
					(
						1.0			* sin(2 * PI * (Progress - phase) / MAXPROGRESS_ANIM_KEY)
					-	1.0 / 9		* sin(2 * PI * 3 * (Progress - phase) / MAXPROGRESS_ANIM_KEY)
					+	1.0 / 25	* sin(2 * PI * 5 * (Progress - phase) / MAXPROGRESS_ANIM_KEY)
					-	1.0 / 49	* sin(2 * PI * 7 * (Progress - phase) / MAXPROGRESS_ANIM_KEY)
					+	1.0 / 81	* sin(2 * PI * 9 * (Progress - phase) / MAXPROGRESS_ANIM_KEY)
					-	1.0 / 121	* sin(2 * PI * 11 * (Progress - phase) / MAXPROGRESS_ANIM_KEY)
					) + center;
	
	return int(ret);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_0(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 0);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_15(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 15);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_30(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 30);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_45(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 45);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_60(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 60);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_75(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 75);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_90(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 90);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_105(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 105);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_120(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 120);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_135(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 135);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_150(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 150);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_165(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 165);
}

/******************************
******************************/
int FuncSp__Pan_Triangle_phase_180(const int Progress)
{
	return PanTilt_Triangle(Progress, PAN_TRIANGLE_CENTER, PAN_TRIANGLE_AMP, 180);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_0(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 0);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_15(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 15);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_30(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 30);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_45(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 45);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_60(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 60);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_75(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 75);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_90(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 90);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_105(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 105);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_120(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 120);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_135(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 135);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_150(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 150);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_165(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 165);
}

/******************************
******************************/
int FuncSp__Tilt_Triangle_phase_180(const int Progress)
{
	return PanTilt_Triangle(Progress, TILT_TRIANGLE_CENTER, TILT_TRIANGLE_AMP, 180);
}

/************************************************************************************************************************/
} // namespace SPACE_LIGHT{


