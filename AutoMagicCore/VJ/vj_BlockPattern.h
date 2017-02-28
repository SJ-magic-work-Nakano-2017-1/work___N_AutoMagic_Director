/************************************************************
************************************************************/
#include "../am_common.h"
#include "vj_common.h"


/************************************************************************************************************************/
namespace SPACE_VJ{


/************************************************************
************************************************************/
enum{
	MAX_SHORTPATTERN_INDEX = 30, // 1Ží—Þ‚Ì block pattern“à‚Ìshort pattern•À‚Ñ
};

struct BLOCK_PATTERN{
	char name[BUF_SIZE];
	
	double Speed;
	int StartPatternId_Candidate; // 0:start from 0. 1:start from 0 or 1.
	
	const PFUNC_VJ_SHORTPATTERN pShortPattern[MAX_SHORTPATTERN_INDEX];
	
	int Weight[NUM_VJ_ALPHA_CH_TYPE][NUM_STATES][NUM_PLAYMODES][NUM_BOOSTMODE];
};


/************************************************************
************************************************************/
extern const struct BLOCK_PATTERN vjBp_1[];



/************************************************************************************************************************/
} // namespace SPACE_VJ{

