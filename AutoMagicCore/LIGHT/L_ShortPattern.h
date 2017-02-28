#pragma once

/************************************************************************************************************************/
namespace SPACE_LIGHT{


/************************************************************
************************************************************/


/************************************************************
************************************************************/
enum{
	MAXPROGRESS_ANIM_KEY				= 10000,
	MAXPROGRESS_ANIM_KEY_x_VALID_RATIO	= 9000,
};

/************************************************************
function prototype to user of this object
************************************************************/
void FuncSp_test();

//
int FuncSp__Lum_const_Zero(const int Progress);
int FuncSp__Lum_const_Max(const int Progress);
int FuncSp__Lum_const_Low(const int Progress);

// 
int FuncSp__Lum_Flash(const int Progress);
int FuncSp__Lum_Flash_Bl(const int Progress);
int FuncSp__Lum_Ambient(const int Progress);

// 
int FuncSp__Lum_On_1_3(const int Progress);
int FuncSp__Lum_On_1_3_Bl(const int Progress);
int FuncSp__Lum_On_2_3(int Progress);
int FuncSp__Lum_On_2_3_Bl(int Progress);
int FuncSp__Lum_On_3_3(int Progress);
int FuncSp__Lum_On_3_3_Bl(int Progress);

int FuncSp__Lum_On_1_4(const int Progress);
int FuncSp__Lum_On_1_4_Bl(const int Progress);
int FuncSp__Lum_On_2_4(int Progress);
int FuncSp__Lum_On_2_4_Bl(int Progress);
int FuncSp__Lum_On_3_4(int Progress);
int FuncSp__Lum_On_3_4_Bl(int Progress);
int FuncSp__Lum_On_4_4(int Progress);
int FuncSp__Lum_On_4_4_Bl(int Progress);

int FuncSp__Lum_On_1_5(const int Progress);
int FuncSp__Lum_On_1_5_Bl(const int Progress);
int FuncSp__Lum_On_2_5(int Progress);
int FuncSp__Lum_On_2_5_Bl(int Progress);
int FuncSp__Lum_On_3_5(int Progress);
int FuncSp__Lum_On_3_5_Bl(int Progress);
int FuncSp__Lum_On_4_5(int Progress);
int FuncSp__Lum_On_4_5_Bl(int Progress);
int FuncSp__Lum_On_5_5(int Progress);
int FuncSp__Lum_On_5_5_Bl(int Progress);

int FuncSp__Lum_On_1_7(const int Progress);
int FuncSp__Lum_On_1_7_Bl(const int Progress);
int FuncSp__Lum_On_2_7(int Progress);
int FuncSp__Lum_On_2_7_Bl(int Progress);
int FuncSp__Lum_On_3_7(int Progress);
int FuncSp__Lum_On_3_7_Bl(int Progress);
int FuncSp__Lum_On_4_7(int Progress);
int FuncSp__Lum_On_4_7_Bl(int Progress);
int FuncSp__Lum_On_5_7(int Progress);
int FuncSp__Lum_On_5_7_Bl(int Progress);
int FuncSp__Lum_On_6_7(int Progress);
int FuncSp__Lum_On_6_7_Bl(int Progress);
int FuncSp__Lum_On_7_7(int Progress);
int FuncSp__Lum_On_7_7_Bl(int Progress);

int FuncSp__Lum_Off_1_3(const int Progress);
int FuncSp__Lum_Off_1_3_Bl(const int Progress);
int FuncSp__Lum_Off_2_3(int Progress);
int FuncSp__Lum_Off_2_3_Bl(int Progress);
int FuncSp__Lum_Off_3_3(int Progress);
int FuncSp__Lum_Off_3_3_Bl(int Progress);

int FuncSp__Lum_Off_1_4(const int Progress);
int FuncSp__Lum_Off_1_4_Bl(const int Progress);
int FuncSp__Lum_Off_2_4(int Progress);
int FuncSp__Lum_Off_2_4_Bl(int Progress);
int FuncSp__Lum_Off_3_4(int Progress);
int FuncSp__Lum_Off_3_4_Bl(int Progress);
int FuncSp__Lum_Off_4_4(int Progress);
int FuncSp__Lum_Off_4_4_Bl(int Progress);

int FuncSp__Lum_Off_1_5(const int Progress);
int FuncSp__Lum_Off_1_5_Bl(const int Progress);
int FuncSp__Lum_Off_2_5(int Progress);
int FuncSp__Lum_Off_2_5_Bl(int Progress);
int FuncSp__Lum_Off_3_5(int Progress);
int FuncSp__Lum_Off_3_5_Bl(int Progress);
int FuncSp__Lum_Off_4_5(int Progress);
int FuncSp__Lum_Off_4_5_Bl(int Progress);
int FuncSp__Lum_Off_5_5(int Progress);
int FuncSp__Lum_Off_5_5_Bl(int Progress);

int FuncSp__Lum_Off_1_7(const int Progress);
int FuncSp__Lum_Off_1_7_Bl(const int Progress);
int FuncSp__Lum_Off_2_7(int Progress);
int FuncSp__Lum_Off_2_7_Bl(int Progress);
int FuncSp__Lum_Off_3_7(int Progress);
int FuncSp__Lum_Off_3_7_Bl(int Progress);
int FuncSp__Lum_Off_4_7(int Progress);
int FuncSp__Lum_Off_4_7_Bl(int Progress);
int FuncSp__Lum_Off_5_7(int Progress);
int FuncSp__Lum_Off_5_7_Bl(int Progress);
int FuncSp__Lum_Off_6_7(int Progress);
int FuncSp__Lum_Off_6_7_Bl(int Progress);
int FuncSp__Lum_Off_7_7(int Progress);
int FuncSp__Lum_Off_7_7_Bl(int Progress);

//
int FuncSp__Lum_Flash_1_2(const int Progress);
int FuncSp__Lum_Flash_1_2_Bl(const int Progress);
int FuncSp__Lum_Flash_2_2(const int Progress);
int FuncSp__Lum_Flash_2_2_Bl(const int Progress);

int FuncSp__Lum_Flash_1_3(const int Progress);
int FuncSp__Lum_Flash_1_3_Bl(const int Progress);
int FuncSp__Lum_Flash_2_3(const int Progress);
int FuncSp__Lum_Flash_2_3_Bl(const int Progress);
int FuncSp__Lum_Flash_3_3(const int Progress);
int FuncSp__Lum_Flash_3_3_Bl(const int Progress);

int FuncSp__Lum_Flash_1_4(const int Progress);
int FuncSp__Lum_Flash_1_4_Bl(const int Progress);
int FuncSp__Lum_Flash_2_4(const int Progress);
int FuncSp__Lum_Flash_2_4_Bl(const int Progress);
int FuncSp__Lum_Flash_3_4(const int Progress);
int FuncSp__Lum_Flash_3_4_Bl(const int Progress);
int FuncSp__Lum_Flash_4_4(const int Progress);
int FuncSp__Lum_Flash_4_4_Bl(const int Progress);

int FuncSp__Lum_Flash_1_5(const int Progress);
int FuncSp__Lum_Flash_1_5_Bl(const int Progress);
int FuncSp__Lum_Flash_2_5(const int Progress);
int FuncSp__Lum_Flash_2_5_Bl(const int Progress);
int FuncSp__Lum_Flash_3_5(const int Progress);
int FuncSp__Lum_Flash_3_5_Bl(const int Progress);
int FuncSp__Lum_Flash_4_5(const int Progress);
int FuncSp__Lum_Flash_4_5_Bl(const int Progress);
int FuncSp__Lum_Flash_5_5(const int Progress);
int FuncSp__Lum_Flash_5_5_Bl(const int Progress);

int FuncSp__Lum_Flash_1_7(const int Progress);
int FuncSp__Lum_Flash_1_7_Bl(const int Progress);
int FuncSp__Lum_Flash_2_7(const int Progress);
int FuncSp__Lum_Flash_2_7_Bl(const int Progress);
int FuncSp__Lum_Flash_3_7(const int Progress);
int FuncSp__Lum_Flash_3_7_Bl(const int Progress);
int FuncSp__Lum_Flash_4_7(const int Progress);
int FuncSp__Lum_Flash_4_7_Bl(const int Progress);
int FuncSp__Lum_Flash_5_7(const int Progress);
int FuncSp__Lum_Flash_5_7_Bl(const int Progress);
int FuncSp__Lum_Flash_6_7(const int Progress);
int FuncSp__Lum_Flash_6_7_Bl(const int Progress);
int FuncSp__Lum_Flash_7_7(const int Progress);
int FuncSp__Lum_Flash_7_7_Bl(const int Progress);

//
int FuncSp__Lum_Flashx2(const int Progress);
int FuncSp__Lum_Flashx2_Bl(const int Progress);
int FuncSp__Lum_Flashx2_2(const int Progress);
int FuncSp__Lum_Flashx2_2_Bl(const int Progress);

int FuncSp__Lum_Flashx3(const int Progress);
int FuncSp__Lum_Flashx3_Bl(const int Progress);
int FuncSp__Lum_Flashx3_2(const int Progress);
int FuncSp__Lum_Flashx3_2_Bl(const int Progress);
int FuncSp__Lum_Flashx3_3(const int Progress);
int FuncSp__Lum_Flashx3_3_Bl(const int Progress);

int FuncSp__Lum_Flashx4(const int Progress);
int FuncSp__Lum_Flashx4_Bl(const int Progress);
int FuncSp__Lum_Flashx4_2(const int Progress);
int FuncSp__Lum_Flashx4_2_Bl(const int Progress);
int FuncSp__Lum_Flashx4_3(const int Progress);
int FuncSp__Lum_Flashx4_3_Bl(const int Progress);
int FuncSp__Lum_Flashx4_4(const int Progress);
int FuncSp__Lum_Flashx4_4_Bl(const int Progress);

int FuncSp__Lum_Flashx5(const int Progress);
int FuncSp__Lum_Flashx5_Bl(const int Progress);
int FuncSp__Lum_Flashx5_2(const int Progress);
int FuncSp__Lum_Flashx5_2_Bl(const int Progress);
int FuncSp__Lum_Flashx5_3(const int Progress);
int FuncSp__Lum_Flashx5_3_Bl(const int Progress);
int FuncSp__Lum_Flashx5_4(const int Progress);
int FuncSp__Lum_Flashx5_4_Bl(const int Progress);
int FuncSp__Lum_Flashx5_5(const int Progress);
int FuncSp__Lum_Flashx5_5_Bl(const int Progress);

int FuncSp__Lum_Flashx7(const int Progress);
int FuncSp__Lum_Flashx7_Bl(const int Progress);
int FuncSp__Lum_Flashx7_2(const int Progress);
int FuncSp__Lum_Flashx7_2_Bl(const int Progress);
int FuncSp__Lum_Flashx7_3(const int Progress);
int FuncSp__Lum_Flashx7_3_Bl(const int Progress);
int FuncSp__Lum_Flashx7_4(const int Progress);
int FuncSp__Lum_Flashx7_4_Bl(const int Progress);
int FuncSp__Lum_Flashx7_5(const int Progress);
int FuncSp__Lum_Flashx7_5_Bl(const int Progress);
int FuncSp__Lum_Flashx7_6(const int Progress);
int FuncSp__Lum_Flashx7_6_Bl(const int Progress);
int FuncSp__Lum_Flashx7_7(const int Progress);
int FuncSp__Lum_Flashx7_7_Bl(const int Progress);

//
int FuncSp__Pan_3ch_const_Angle_0(const int Progress);
int FuncSp__Pan_3ch_const_Angle_1(const int Progress);
int FuncSp__Pan_3ch_const_Angle_2(const int Progress);
int FuncSp__Tilt_3ch_const_Angle_0(const int Progress);
int FuncSp__Tilt_3ch_const_Angle_1(const int Progress);
int FuncSp__Tilt_3ch_const_Angle_2(const int Progress);

//
int FuncSp__Pan_7ch_const_Angle_0(const int Progress);
int FuncSp__Pan_7ch_const_Angle_1(const int Progress);
int FuncSp__Pan_7ch_const_Angle_2(const int Progress);
int FuncSp__Pan_7ch_const_Angle_3(const int Progress);
int FuncSp__Pan_7ch_const_Angle_4(const int Progress);
int FuncSp__Pan_7ch_const_Angle_5(const int Progress);
int FuncSp__Pan_7ch_const_Angle_6(const int Progress);

int FuncSp__Tilt_7ch_const_Angle_0(const int Progress);
int FuncSp__Tilt_7ch_const_Angle_1(const int Progress);
int FuncSp__Tilt_7ch_const_Angle_2(const int Progress);
int FuncSp__Tilt_7ch_const_Angle_3(const int Progress);
int FuncSp__Tilt_7ch_const_Angle_4(const int Progress);
int FuncSp__Tilt_7ch_const_Angle_5(const int Progress);
int FuncSp__Tilt_7ch_const_Angle_6(const int Progress);

//
int FuncSp__Pan_Triangle_phase_0(const int Progress);
int FuncSp__Pan_Triangle_phase_15(const int Progress);
int FuncSp__Pan_Triangle_phase_30(const int Progress);
int FuncSp__Pan_Triangle_phase_45(const int Progress);
int FuncSp__Pan_Triangle_phase_60(const int Progress);
int FuncSp__Pan_Triangle_phase_75(const int Progress);
int FuncSp__Pan_Triangle_phase_90(const int Progress);
int FuncSp__Pan_Triangle_phase_105(const int Progress);
int FuncSp__Pan_Triangle_phase_120(const int Progress);
int FuncSp__Pan_Triangle_phase_135(const int Progress);
int FuncSp__Pan_Triangle_phase_150(const int Progress);
int FuncSp__Pan_Triangle_phase_165(const int Progress);
int FuncSp__Pan_Triangle_phase_180(const int Progress);

int FuncSp__Tilt_Triangle_phase_0(const int Progress);
int FuncSp__Tilt_Triangle_phase_15(const int Progress);
int FuncSp__Tilt_Triangle_phase_30(const int Progress);
int FuncSp__Tilt_Triangle_phase_45(const int Progress);
int FuncSp__Tilt_Triangle_phase_60(const int Progress);
int FuncSp__Tilt_Triangle_phase_75(const int Progress);
int FuncSp__Tilt_Triangle_phase_90(const int Progress);
int FuncSp__Tilt_Triangle_phase_105(const int Progress);
int FuncSp__Tilt_Triangle_phase_120(const int Progress);
int FuncSp__Tilt_Triangle_phase_135(const int Progress);
int FuncSp__Tilt_Triangle_phase_150(const int Progress);
int FuncSp__Tilt_Triangle_phase_165(const int Progress);
int FuncSp__Tilt_Triangle_phase_180(const int Progress);



/************************************************************************************************************************/
} // namespace SPACE_LIGHT{
	
	
