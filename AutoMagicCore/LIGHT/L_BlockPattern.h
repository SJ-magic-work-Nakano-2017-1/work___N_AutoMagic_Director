/************************************************************
************************************************************/
#pragma once

#include "../am_common.h"

/************************************************************************************************************************/
namespace SPACE_LIGHT{


/************************************************************
************************************************************/
enum{
	MAX_CHS_IN_A_BLOCK = 7,
	MAX_SHORTPATTERN_INDEX = 30, // 1Ží—Þ‚Ì block pattern“à‚Ìshort pattern•À‚Ñ
};

struct BLOCK_PATTERN{
	char name[BUF_SIZE];
	
	double Speed;
	int StartPatternId_Candidate; // 0:start from 0. 1:start from 0 or 1.
	
	const PFUNC_SHORTPATTERN pShortPattern[MAX_SHORTPATTERN_INDEX][MAX_CHS_IN_A_BLOCK];
	enum SYMMETRIC_TYPE SymmetricType;
	
	int Weight[NUM_DEVICE_CH_TYPE][NUM_STATES][NUM_PLAYMODES][NUM_BOOSTMODE];
};


/************************************************************
************************************************************/
extern const struct BLOCK_PATTERN Bp_1[];
extern const struct BLOCK_PATTERN Bp_2[];
extern const struct BLOCK_PATTERN Bp_3[];
extern const struct BLOCK_PATTERN Bp_4[];
extern const struct BLOCK_PATTERN Bp_5[];
extern const struct BLOCK_PATTERN Bp_7[];


/************************************************************************************************************************/
} // namespace SPACE_LIGHT{


