/************************************************************
************************************************************/
#include <stdio.h>
#include <math.h>

#include <stdlib.h>
#include "Perlin.h"

#include "am_common.h"
#include "HF_Analyze.h"

#include "StopWatch.h"


/************************************************************
************************************************************/

/********************
INT interval = 10 or 11ms.
count = 10 means 100 - 110ms.
********************/
enum{
	THRESH_COUNT_TO_BOOST	= 400,
	THRESH_COUNT_TO_NORMAL	= 40,
};

static const int C_CARRY_BOOST_CHANCE = 2;

/************************************************************
************************************************************/
/********************
********************/
static BOOSTMODE mode			= BOOSTMODE_NORMAL;
static BOOSTMODE running_mode	= BOOSTMODE_NORMAL;

static int counter = 0;

static double last_vol_High = 0;
static double last_tan = 0;

static int t_Flywheel = -1;
static int t_EnterFLYWHEEL = 0;
static int t_EnterSOUND = 0;

static bool b_Refresh_mode = false;
static int c_CarryBoostChance = 0;

static int self_Beat_interval_Entering_SOUND;
static int self_Beat_interval_Entering_SOUND_Slow;

/********************
********************/
static SUB_STATE_SOUND SubState_Sound = STATE_SOUND_NONE;
static int t_intervalTransition;
static int t_from_SpeedChange;

static int self_Beat_interval_From;
static int self_Beat_interval_To;

/********************
********************/
static Perlin* perlin = NULL;


/************************************************************
************************************************************/
static void StateChart();
static void save__selfBeatInterval_EnteringSOUND(int interval);
static void setParam_selfInterval_SpeedUp(int now_ms, const int self_Beat_interval);
static void setParam_selfInterval_SpeedDown(int now_ms, const int self_Beat_interval);


/************************************************************
function
************************************************************/

/******************************
description

param
	vol_High
		平均化された後の値
		tanは、ここからtanを求め、さらにこれを平均化する.
******************************/
double HF_input_vol_high(double vol_High, int now_ms)
{
	/********************
	********************/
	static int last_INT_ms = 0;
	
	// const double Ck = 0.001;
	const double Ck = 0.0007;
	
	double tan;
	if(now_ms == last_INT_ms){
		tan = 0;
	}else{
		// "*10" is just Boost up so that I can check easily.
		// + or - matters, so actually no meaning.
		// tan = (vol_High - last_vol_High) * 10 / (now_ms - last_INT_ms);
		
		tan = (vol_High - last_vol_High) * 10 / (now_ms - last_INT_ms);
	}
	last_INT_ms = now_ms;
	
	last_tan = (1 - Ck) * last_tan + Ck * tan;
	
	last_vol_High = vol_High;
	
	/********************
	********************/
	StateChart();
	
	/********************
	********************/
	if( b_Refresh_mode ){
		mode = running_mode;
	}
	
	return last_tan;
}

/******************************
******************************/
void StateChart()
{
	switch(running_mode){
		case BOOSTMODE_NORMAL:
			if(0 <= last_tan)	counter++;
			else				counter = 0;
			if(THRESH_COUNT_TO_BOOST <= counter){
				counter = 0;
				running_mode = BOOSTMODE_BOOST;
			}
			break;
			
		case BOOSTMODE_BOOST:
			if(last_tan < 0)	counter++;
			else				counter = 0;
			if(THRESH_COUNT_TO_NORMAL <= counter){
				counter = 0;
				running_mode = BOOSTMODE_NORMAL;
			}
			break;
			
		default:
			break;
	}
}

/******************************
******************************/
double HF_get_tan()
{
	return last_tan;
}

/******************************
description
	例えば、SelectBlockPattern()で使用。
	Boost/ Normal分岐があるので、内部状態が見えるとdebugが可能となる。
******************************/
void HF_debug_log(FILE* fp, int now_ms)
{
	char buf[BUF_SIZE];

	sprintf(buf, ";HF LOG:\n");
	fprintf_Log(fp, "%s", buf);
	
	sprintf(buf, ";t_Flywheel=%d, t_EnterSOUND=%d, t_StartRefresh=%d\n", (int)t_Flywheel, (int)t_EnterSOUND, (int)(t_EnterSOUND + t_Flywheel *4/5));
	fprintf_Log(fp, "%s", buf);
	
	sprintf(buf, ";running_mode=%d, mode=%d, c_CarryBoostChance=%d\n", (int)running_mode, (int)mode, (int)c_CarryBoostChance);
	fprintf_Log(fp, "%s", buf);
}

/******************************
******************************/
void HF_EnterBEATIN()
{
	/********************
	********************/
	b_Refresh_mode = false;
	
	if( (get_BoostMode() == BOOSTMODE_NORMAL) && (c_CarryBoostChance) ){
		mode = running_mode;
		c_CarryBoostChance--;
	}
	
	SubState_Sound = STATE_SOUND_NONE;
	
	/********************
	********************/
	if(perlin) delete perlin;
	perlin = new Perlin;
}

/******************************
******************************/
void HF_DropFlywheel(int now_ms)
{
	t_Flywheel = now_ms - t_EnterFLYWHEEL;
}

/******************************
******************************/
bool HF_IsBoost()
{
	if(mode == BOOSTMODE_BOOST)	return true;
	else						return false;
}

/******************************
******************************/
void HF_init()
{
	mode = BOOSTMODE_NORMAL;
	t_Flywheel = -1;
	b_Refresh_mode = false;
	
	SubState_Sound = STATE_SOUND_NONE;
	
	if(perlin) delete perlin;
	perlin = new Perlin;
}

/******************************
******************************/
int HF_getSubState()
{
	return int(SubState_Sound);
}

/******************************
******************************/
void HF_EnterSOUND(int now_ms, const int self_Beat_interval)
{
	t_EnterSOUND = now_ms;
	
	if(mode == BOOSTMODE_NORMAL)	c_CarryBoostChance = 0;
	
	mode = BOOSTMODE_NORMAL;
	SubState_Sound = STATE_SOUND_1ST_PATTEN;
	
	save__selfBeatInterval_EnteringSOUND(self_Beat_interval);
	
	setParam_selfInterval_SpeedDown(now_ms, self_Beat_interval);
}

/******************************
******************************/
void HF_EnterSOUND_fromDrop(int now_ms, int& self_Beat_interval)
{
	c_CarryBoostChance = 0;
	
	if( (mode == BOOSTMODE_BOOST) && (running_mode == BOOSTMODE_BOOST) ){
		mode = BOOSTMODE_BOOST;
	}else{
		mode = BOOSTMODE_NORMAL;
	}
	
	if(get_BoostMode() == BOOSTMODE_NORMAL){
		SubState_Sound = STATE_SOUND_NORMAL_AFTER_2ND_PATTERN;
		
		/********************
		SmoothにSpeedDown
		********************/
		setParam_selfInterval_SpeedDown(now_ms, self_Beat_interval);
		
	}else{
		SubState_Sound = STATE_SOUND_BOOST;
		
		/********************
		ガクッと落としてからSpeedUp
		********************/
		self_Beat_interval = self_Beat_interval_Entering_SOUND_Slow;
		setParam_selfInterval_SpeedUp(now_ms, self_Beat_interval);
		
	}
}

/******************************
******************************/
void setParam_selfInterval_SpeedUp(int now_ms, const int self_Beat_interval)
{
	self_Beat_interval_From	= self_Beat_interval;
	self_Beat_interval_To	= self_Beat_interval_Entering_SOUND;
	
	t_from_SpeedChange		= now_ms;
	t_intervalTransition	= 3 * abs(self_Beat_interval_From - self_Beat_interval_To);
	
	b_Refresh_mode = false;
}

/******************************
******************************/
void setParam_selfInterval_SpeedDown(int now_ms, const int self_Beat_interval)
{
	self_Beat_interval_From	= self_Beat_interval;
	self_Beat_interval_To	= self_Beat_interval_Entering_SOUND_Slow;

	t_from_SpeedChange		= now_ms;
	t_intervalTransition	= 4 * abs(self_Beat_interval_From - self_Beat_interval_To);
}

/******************************
******************************/
bool HF_Transraion_Sound_to_Sound()
{
	bool ret = false;
	
	switch(SubState_Sound){
		case STATE_SOUND_1ST_PATTEN:
			SubState_Sound = STATE_SOUND_NORMAL_AFTER_2ND_PATTERN;
			c_CarryBoostChance = 0;
			
			// StopWatch_TangiblePatternChange.Reset();
			ret = true;
			
			break;
			
		case STATE_SOUND_NORMAL_AFTER_2ND_PATTERN:
			/* none */
			break;
			
		case STATE_SOUND_NORMAL_TO_BOOST:
			SubState_Sound = STATE_SOUND_BOOST;
			break;
			
		case STATE_SOUND_BOOST:
			/* none */
			break;
			
		default:
			break;
	}
	
	return ret;
}

/******************************
******************************/
void HF_EnterFLYWHEEL(int now_ms)
{
	t_EnterFLYWHEEL = now_ms;
}

/******************************
******************************/
void HF_everyINT_inSOUND(int now_ms, int& self_Beat_interval)
{
	/********************
	********************/
	if( SubState_Sound == STATE_SOUND_NORMAL_AFTER_2ND_PATTERN ){
		if( !b_Refresh_mode && (0 < t_Flywheel) && (t_Flywheel * 4 < (now_ms - t_EnterSOUND) * 5) ){
			b_Refresh_mode = true;
		}
		
		if(get_BoostMode() == BOOSTMODE_BOOST){
			SubState_Sound = STATE_SOUND_NORMAL_TO_BOOST;
			setParam_selfInterval_SpeedUp(now_ms, self_Beat_interval);
			
			c_CarryBoostChance = C_CARRY_BOOST_CHANCE;
		}
	}
			
	/********************
	********************/
	switch(SubState_Sound){
		case STATE_SOUND_1ST_PATTEN:
		case STATE_SOUND_NORMAL_AFTER_2ND_PATTERN:
			if( (0 < t_intervalTransition) && (now_ms - t_from_SpeedChange <= t_intervalTransition) ){
				int Amp	= (self_Beat_interval_To - self_Beat_interval_From) / 2;
				int ofs	= self_Beat_interval_From + Amp;
				int T	= 2 * t_intervalTransition;
				
				self_Beat_interval = int(-Amp * cos(2 * PI * (now_ms - t_from_SpeedChange) / T) + ofs);
				
			}else{
				self_Beat_interval = self_Beat_interval_To;
			}
			
			break;
			
		case STATE_SOUND_NORMAL_TO_BOOST:
		case STATE_SOUND_BOOST:
			if( (0 < t_intervalTransition) && (now_ms - t_from_SpeedChange <= t_intervalTransition) ){
				int Amp	= (self_Beat_interval_From - self_Beat_interval_To) / 2;
				int ofs	= self_Beat_interval_To + Amp;
				int T	= 2 * t_intervalTransition;
				
				self_Beat_interval = int(Amp * cos(2 * PI * (now_ms - t_from_SpeedChange) / T) + ofs);
				
			}else{
				double Amp	= self_Beat_interval_To * 0.4;
				self_Beat_interval = int(self_Beat_interval_To + Amp * perlin->noise(float(double(now_ms - t_from_SpeedChange - t_intervalTransition) * 0.0003), 0, 0));
			}
			break;
			
		default:
			break;
	}
}

/******************************
******************************/
void save__selfBeatInterval_EnteringSOUND(int interval)
{
	self_Beat_interval_Entering_SOUND		= interval;
	self_Beat_interval_Entering_SOUND_Slow	= self_Beat_interval_Entering_SOUND * 4;
	
	if(Beat_interval_amb <= self_Beat_interval_Entering_SOUND)		self_Beat_interval_Entering_SOUND 		= Beat_interval_amb;
	if(Beat_interval_amb <= self_Beat_interval_Entering_SOUND_Slow)	self_Beat_interval_Entering_SOUND_Slow	= Beat_interval_amb;
}

/******************************
******************************/
void HF_ReLoad__selfBeatInterval_EnteringSOUND(int& self_Beat_interval, bool b_Load_FastVal)
{
	if(b_Load_FastVal){
		self_Beat_interval = self_Beat_interval_Entering_SOUND;
		
	}else{
		if(get_BoostMode() == BOOSTMODE_BOOST){
			self_Beat_interval = self_Beat_interval_Entering_SOUND;
		}else{
			self_Beat_interval = self_Beat_interval_Entering_SOUND_Slow;
		}
	}
}

