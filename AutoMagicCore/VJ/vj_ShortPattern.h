#pragma once

/************************************************************************************************************************/
namespace SPACE_VJ{



/************************************************************
************************************************************/

/************************************************************
************************************************************/


/************************************************************
************************************************************/

/**************************************************
**************************************************/
class FUNC_SP_VJ{
private:
	
	/****************************************
	****************************************/
	static double Flash(const int Progress, const int MaxProgress);
	static double Flash_xN(int Progress, const int MaxProgress, const int N);
	static double Square_xN(int Progress, const int MaxProgress, const int N);

public:
	/****************************************
	****************************************/
	enum{
		MAXPROGRESS_ANIM_KEY				= 10000,
		MAXPROGRESS_ANIM_KEY_x_VALID_RATIO	= 9000,
	};
	
	/****************************************
	****************************************/
	static void FuncSp_test();
	
	static double FuncSp__const_Zero(const int Progress, const double phase_deg);
	static double FuncSp__const_Max(const int Progress, const double phase_deg);
	static double FuncSp__Flash(const int Progress, const double phase_deg);
	static double FuncSp__Flash_Bl(const int Progress, const double phase_deg);
	static double FuncSp__Flash_x4(const int Progress, const double phase_deg);
	static double FuncSp__Flash_x4_Bl(const int Progress, const double phase_deg);
	static double FuncSp__sin(const int Progress, const double phase_deg);
	static double FuncSp__Square_x2(const int Progress, const double phase_deg);
	static double FuncSp__Square_x2_Bl(const int Progress, const double phase_deg);
	static double FuncSp__Square_x1(const int Progress, const double phase_deg);
	static double FuncSp__Square_x1_Bl(const int Progress, const double phase_deg);
	static double FuncSp__Trape_On(const int Progress, const double phase_deg);
	static double FuncSp__Trape_Off(const int Progress, const double phase_deg);
};


/************************************************************************************************************************/
} // namespace SPACE_VJ{


