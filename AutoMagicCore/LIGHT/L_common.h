#pragma once

/************************************************************************************************************************/
namespace SPACE_LIGHT{



/************************************************************
************************************************************/
enum TANGIBLE_OR_NOT{
	INTANGIBLE,
	TANGIBLE,
};

enum COLOR_CHANGE_KEEP{
	COLOR_KEEP,
	COLOR_CHANGE,
	COLOR_FLASH,
	
	NUM_COLOR_CHANGE_KEEP,
};

typedef int (*PFUNC_SHORTPATTERN)(const int Progress);

enum SYMMETRIC_TYPE{
	SYMMETRY_RANDOM,
	SYMMETRY_LINE,
	SYMMETRY_RIGID,
};

enum CH_TO_SET{
	CH_LUM,
	CH_PAN,
	CH_TILT,
	
	NUM_CH_TO_SET,
};

enum DEVICE_CH_TYPE{
	DEVICE_CH_TYPE__FIX_LUM_PANEL,
	DEVICE_CH_TYPE__FIX_LUM_STROBE,
	
	DEVICE_CH_TYPE__MOV_LUM_RGB,
	DEVICE_CH_TYPE__MOV_LUM_STROBE,
	
	DEVICE_CH_TYPE__MOV_ANGLE_PAN,
	DEVICE_CH_TYPE__MOV_ANGLE_TILT,
	
	
	NUM_DEVICE_CH_TYPE,
};


/************************************************************************************************************************/
} // namespace SPACE_LIGHT{

