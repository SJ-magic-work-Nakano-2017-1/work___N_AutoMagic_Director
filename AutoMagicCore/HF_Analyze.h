#pragma once

/************************************************************
************************************************************/
enum SUB_STATE_SOUND{
	STATE_SOUND_NONE,
	
	STATE_SOUND_1ST_PATTEN,
	STATE_SOUND_NORMAL_AFTER_2ND_PATTERN,
	STATE_SOUND_NORMAL_TO_BOOST,
	STATE_SOUND_BOOST,
};

/************************************************************
************************************************************/
double HF_input_vol_high(double vol_High, int now_ms);
double HF_get_tan();
void HF_EnterBEATIN();
void HF_ReLoad__selfBeatInterval_EnteringSOUND(int& self_Beat_interval, bool b_Load_FastVal = false);
void HF_DropFlywheel(int now_ms);
bool HF_IsBoost();
void HF_init();
void HF_EnterSOUND(int now_ms, const int self_Beat_interval);
void HF_EnterSOUND_fromDrop(int now_ms, int& self_Beat_interval);
void HF_EnterFLYWHEEL(int now_ms);
void HF_everyINT_inSOUND(int now_ms, int& self_Beat_interval);
bool HF_Transraion_Sound_to_Sound();
void HF_debug_log(FILE* fp, int now_ms);
int HF_getSubState();

