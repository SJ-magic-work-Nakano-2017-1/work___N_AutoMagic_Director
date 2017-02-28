#pragma once

/************************************************************************************************************************/
namespace SPACE_VJ{


/************************************************************
************************************************************/

enum VJ_ALPHA_CH_TYPE{
	VJ_ALPHA_CH_TYPE__MOV_0_12,
	VJ_ALPHA_CH_TYPE__MOV_1_2,
	VJ_ALPHA_CH_TYPE__INDICATOR,
	VJ_ALPHA_CH_TYPE__PARTICLE,
	VJ_ALPHA_CH_TYPE__STROBE,
	
	NUM_VJ_ALPHA_CH_TYPE,
};

enum ADD_EFFECT{
	ADD_EFFECT__ON,
	ADD_EFFECT__OFF,
	
	NUM_ADD_EFFECT,
};

typedef double (*PFUNC_VJ_SHORTPATTERN)(const int Progress, const double phase_deg);


/************************************************************************************************************************/
} // namespace SPACE_VJ{


