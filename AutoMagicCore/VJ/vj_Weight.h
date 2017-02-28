#pragma once

/************************************************************************************************************************/
namespace SPACE_VJ{



/************************************************************
************************************************************/

/******************************
******************************/
static const int W_AddGeneratedImage[NUM_STATES][NUM_BOOSTMODE][NUM_ADD_EFFECT] = {
	// STATE_NOSOUND,
	{
		{ // Normal
			0, // on
			1, // off
		},
		{ // Boost
			0, // on
			1, // off
		},
	},
	// STATE_SOUND,
	{
		{ // Normal
			1, // on
			5, // off
		},
		{ // Boost
			1, // on
			3, // off
		},
	},
	// STATE_SOUND_DROP,
	{
	},
	// STATE_BEAT_IN,
	{
		{ // Normal
			1, // on
			6, // off
		},
		{ // Boost
			1, // on
			6, // off
		},
	},
	// STATE_BEAT_IN_DROP,
	{
	},
	// STATE_FLYWHEEL,
	{
		{ // Normal
			1, // on
			5, // off
		},
		{ // Boost
			1, // on
			3, // off
		},
	},
	// STATE_FLYWHEEL_DROP,
	{
	},
};

/******************************
******************************/
static const int W_AddText[NUM_STATES][NUM_BOOSTMODE][NUM_ADD_EFFECT] = {
	// STATE_NOSOUND,
	{
		{ // Normal
			0, // on
			1, // off
		},
		{ // Boost
			0, // on
			1, // off
		},
	},
	// STATE_SOUND,
	{
		{ // Normal
			0, // on
			1, // off
		},
		{ // Boost
			1, // on
			3, // off
		},
	},
	// STATE_SOUND_DROP,
	{
	},
	// STATE_BEAT_IN,
	{
		{ // Normal
			0, // on
			1, // off
		},
		{ // Boost
			0, // on
			1, // off
		},
	},
	// STATE_BEAT_IN_DROP,
	{
	},
	// STATE_FLYWHEEL,
	{
		{ // Normal
			1, // on
			20, // off
		},
		{ // Boost
			1, // on
			6, // off
		},
	},
	// STATE_FLYWHEEL_DROP,
	{
	},
};

/******************************
******************************/
static const int W_AddEffectToMov_All[NUM_STATES][NUM_BOOSTMODE][NUM_ADD_EFFECT] = {
	// STATE_NOSOUND,
	{
		{ // Normal
			0, // on
			1, // off
		},
		{ // Boost
			0, // on
			1, // off
		},
	},
	// STATE_SOUND,
	{
		{ // Normal
			1, // on
			5, // off
		},
		{ // Boost
			1, // on
			4, // off
		},
	},
	// STATE_SOUND_DROP,
	{
	},
	// STATE_BEAT_IN,
	{
		{ // Normal
			1, // on
			6, // off
		},
		{ // Boost
			1, // on
			6, // off
		},
	},
	// STATE_BEAT_IN_DROP,
	{
	},
	// STATE_FLYWHEEL,
	{
		{ // Normal
			1, // on
			5, // off
		},
		{ // Boost
			1, // on
			4, // off
		},
	},
	// STATE_FLYWHEEL_DROP,
	{
	},
};

/******************************
******************************/
static const int W_AddEffectToMov_0[NUM_STATES][NUM_BOOSTMODE][NUM_ADD_EFFECT] = {
	// STATE_NOSOUND,
	{
		{ // Normal
			0, // on
			1, // off
		},
		{ // Boost
			0, // on
			1, // off
		},
	},
	// STATE_SOUND,
	{
		{ // Normal
			1, // on
			5, // off
		},
		{ // Boost
			1, // on
			4, // off
		},
	},
	// STATE_SOUND_DROP,
	{
	},
	// STATE_BEAT_IN,
	{
		{ // Normal
			1, // on
			6, // off
		},
		{ // Boost
			1, // on
			6, // off
		},
	},
	// STATE_BEAT_IN_DROP,
	{
	},
	// STATE_FLYWHEEL,
	{
		{ // Normal
			1, // on
			5, // off
		},
		{ // Boost
			1, // on
			4, // off
		},
	},
	// STATE_FLYWHEEL_DROP,
	{
	},
};

	
/************************************************************************************************************************/
} // namespace SPACE_VJ{


