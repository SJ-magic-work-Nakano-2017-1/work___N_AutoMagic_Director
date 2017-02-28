/************************************************************
************************************************************/
#include "DoubtBeat.h"

/************************************************************
param
************************************************************/
static bool b_DoubtBeat = false;
static bool b_DoubtSetInThisState = false;


/************************************************************
function
************************************************************/

/******************************
******************************/
void DB_init()
{
	b_DoubtBeat = false;
	b_DoubtSetInThisState = false;
}

/******************************
******************************/
void DB_ClearFlag_DoubtSet()
{
	b_DoubtSetInThisState = false;
}

/******************************
******************************/
bool DB_isDoubtSetInThisState()
{
	return b_DoubtSetInThisState;
}

/******************************
******************************/
bool DB_isDoubting()
{
	return b_DoubtBeat;
}

/******************************
******************************/
void DB_SetDoubt(bool flag)
{
	b_DoubtBeat = flag;
	
	if(flag) b_DoubtSetInThisState = true;
}

