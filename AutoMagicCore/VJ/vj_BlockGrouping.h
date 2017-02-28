#pragma once

/************************************************************
************************************************************/
#include "../am_common.h"
#include "vj_common.h"


/************************************************************************************************************************/
namespace SPACE_VJ{



/************************************************************
************************************************************/
struct ANIM_SELF_PROPULSION{
	int LastBeat_ms;
};

struct BP_INFO{
	/********************
	Fix
	********************/
	enum VJ_ALPHA_CH_TYPE AlphaChType;
	
	/********************
	Dynamic
	èâä˙ílÇ†ÇË
	********************/
	double LastOutputLevel;
	double PhaseDeg_for_BlockPattern;
	
	/********************
	Dynamic
	********************/
	enum PLAYMODE PlayMode;
	int Bp_Pattern_index;
	int Pattern_index;
	ANIM_SELF_PROPULSION SelfPropulsion;
	
	int t_NewPatternStart;
	
};

struct BLOCK{
	/********************
	********************/
	const int (*Weight_PlayMode)[NUM_PLAYMODES];
	
	const BLOCK_PATTERN *Bp_Pattern;
	
	/********************
	********************/
	BP_INFO BpInfo;
	
	/********************
	********************/
	void Set_AllBpInfo_SelfPropulsion_LastBeatms(int now_ms)
	{
		BpInfo.SelfPropulsion.LastBeat_ms = now_ms;
	}
	
	void Reset_AllBpInfo_SelfPropulsion(int now_ms)
	{
		Set_AllBpInfo_SelfPropulsion_LastBeatms(now_ms);
	}
};

/************************************************************
************************************************************/
static const int Weight_PlayMode_strobe[NUM_STATES][NUM_PLAYMODES] = {
	{ // STATE_NOSOUND, 
		// Beat, Self ... Normal = Boost
		0, 1, 
	},
	{ // STATE_SOUND, 
		0, 1, 
	},
	{ // STATE_SOUND_DROP, 
	},
	{ // STATE_BEAT_IN, 
		0, 1, 
	},
	{ // STATE_BEAT_IN_DROP, 
	},
	{ // STATE_FLYWHEEL, 
		3, 1, 
	},
	{ // STATE_FLYWHEEL_DROP, 
	},
};

static const int Weight_PlayMode_particle[NUM_STATES][NUM_PLAYMODES] = {
	{ // STATE_NOSOUND, 
		// Beat, Self ... Normal = Boost
		0, 1, 
	},
	{ // STATE_SOUND, 
		0, 1, 
	},
	{ // STATE_SOUND_DROP, 
	},
	{ // STATE_BEAT_IN, 
		0, 1, 
	},
	{ // STATE_BEAT_IN_DROP, 
	},
	{ // STATE_FLYWHEEL, 
		0, 1, 
	},
	{ // STATE_FLYWHEEL_DROP, 
	},
};

static const int Weight_PlayMode_indicator[NUM_STATES][NUM_PLAYMODES] = {
	{ // STATE_NOSOUND, 
		// Normal{Beat, Self}
		0, 1, 
	},
	{ // STATE_SOUND, 
		0, 1, 
	},
	{ // STATE_SOUND_DROP, 
	},
	{ // STATE_BEAT_IN, 
		0, 1, 
	},
	{ // STATE_BEAT_IN_DROP, 
	},
	{ // STATE_FLYWHEEL, 
		0, 1, 
	},
	{ // STATE_FLYWHEEL_DROP, 
	},
};

static const int Weight_PlayMode_mov_0_12[NUM_STATES][NUM_PLAYMODES] = {
	{ // STATE_NOSOUND, 
		// Normal{Beat, Self}
		0, 1, 
	},
	{ // STATE_SOUND, 
		0, 1, 
	},
	{ // STATE_SOUND_DROP, 
	},
	{ // STATE_BEAT_IN, 
		0, 1, 
	},
	{ // STATE_BEAT_IN_DROP, 
	},
	{ // STATE_FLYWHEEL, 
		0, 1, 
	},
	{ // STATE_FLYWHEEL_DROP, 
	},
};

static const int Weight_PlayMode_mov_1_2[NUM_STATES][NUM_PLAYMODES] = {
	{ // STATE_NOSOUND, 
		// Normal{Beat, Self}
		0, 1, 
	},
	{ // STATE_SOUND, 
		0, 1, 
	},
	{ // STATE_SOUND_DROP, 
	},
	{ // STATE_BEAT_IN, 
		3, 1, 
	},
	{ // STATE_BEAT_IN_DROP, 
	},
	{ // STATE_FLYWHEEL, 
		1, 0, 
	},
	{ // STATE_FLYWHEEL_DROP, 
	},
};

/************************************************************
ÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅö
Copy from Excel below.
ÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅöÅö
************************************************************/
BLOCK Block[] = {			
			
	{ // Block	BLOCK_A_0_12	
		Weight_PlayMode_mov_0_12,	
		vjBp_1,	// Bp_Pattern
		{ // BpInfo	
			VJ_ALPHA_CH_TYPE__MOV_0_12,
			0, 0,
		},	
	},		
	{ // Block	BLOCK_A_1_2	
		Weight_PlayMode_mov_1_2,	
		vjBp_1,	// Bp_Pattern
		{ // BpInfo	
			VJ_ALPHA_CH_TYPE__MOV_1_2,
			0, 0,
		},	
	},		
	{ // Block	Indicator	
		Weight_PlayMode_indicator,	
		vjBp_1,	// Bp_Pattern
		{ // BpInfo	
			VJ_ALPHA_CH_TYPE__INDICATOR,
			0, 0,
		},	
	},		
	{ // Block	Particle	
		Weight_PlayMode_particle,	
		vjBp_1,	// Bp_Pattern
		{ // BpInfo	
			VJ_ALPHA_CH_TYPE__PARTICLE,
			0, 0,
		},	
	},		
	{ // Block	Strobe	
		Weight_PlayMode_strobe,	
		vjBp_1,	// Bp_Pattern
		{ // BpInfo	
			VJ_ALPHA_CH_TYPE__STROBE,
			0, 0,
		},	
	},		
			
	{ // END		
		Weight_PlayMode_mov_0_12,	
		NULL,	// Bp_Pattern
		{ // BpInfo	
			VJ_ALPHA_CH_TYPE__MOV_0_12,
			0, 0,
		},	
	},		
};			

/************************************************************************************************************************/
} //namespace SPACE_VJ{


