#pragma once

/************************************************************
************************************************************/
void DB_init();
void DB_ClearFlag_DoubtSet();
bool DB_isDoubtSetInThisState();
bool DB_isDoubting();
void DB_SetDoubt(bool flag);

