#pragma once

/************************************************************************************************************************/
namespace SPACE_LIGHT{




/************************************************************
************************************************************/

/******************************
******************************/
static const int W_ColorChange[NUM_STATES][NUM_BOOSTMODE][NUM_COLOR_CHANGE_KEEP] = {
	// STATE_NOSOUND,
	{// Normal{	COLOR_KEEP, COLOR_CHANGE, COLOR_FLASH}, Boost{*, *, *}
		{1, 9, 0}, {1, 9, 0}
	},
	
	// STATE_SOUND,
	{
		{2, 8, 0}, {2, 8, 0}
	},
	// STATE_SOUND_DROP,
	{
	},
	// STATE_BEAT_IN,
	{
		{2, 8, 0}, {2, 8, 0}
	},
	// STATE_BEAT_IN_DROP,
	{
	},
	// STATE_FLYWHEEL,
	{
		{2, 8, 0}, {1, 7, 2}
	},
	// STATE_FLYWHEEL_DROP,
	{
	},

};

/******************************
******************************/
static const int W_BlockGrouping_Tangible[NUM_STATES][NUM_BOOSTMODE][NUM_GROUPTYPES_TANGIBLE] = {
	// STATE_NOSOUND,
	{
		{ // Normal
			1, // "TANGIBLE_GP__DUMMY",
		},
		{ // Boost
		},
	},
	// STATE_SOUND,
	{
		{ // Normal
			1, // "TANGIBLE_GP__DUMMY",
		},
		{ // Boost
			1, // "TANGIBLE_GP__DUMMY",
		},
	},
	// STATE_SOUND_DROP,
	{
	},
	// STATE_BEAT_IN,
	{
		{ // Normal
			1, // "TANGIBLE_GP__DUMMY",
		},
		{ // Boost
			1, // "TANGIBLE_GP__DUMMY",
		},
	},
	// STATE_BEAT_IN_DROP,
	{
	},
	// STATE_FLYWHEEL,
	{
		{ // Normal
			1, // "TANGIBLE_GP__DUMMY",
		},
		{ // Boost
			1, // "TANGIBLE_GP__DUMMY",
		},
	},
	// STATE_FLYWHEEL_DROP,
	{
	},
};

static const int W_BlockGrouping_InTangible[NUM_STATES][NUM_BOOSTMODE][NUM_GROUPTYPES_INTANGIBLE] = {
	// STATE_NOSOUND,
	{
		{ // Normal
			1, // "GP0__NOSOUND",
			0, // "GP0__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP0__SOUND_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__SOUND_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__BEAT_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__BEAT_NORMAL__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SYNC__STRAIGHT",
			0, // "GP0__BEAT_BOOST__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__BEAT_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__SYMMETRY",
			0, // "GP1__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP2__FLYWHEEL_BOOST__SEPARATE",
		},
		{ // Boost
		},
	},
	// STATE_SOUND,
	{
		{ // Normal
			0, // "GP0__NOSOUND",
			8, // "GP0__SOUND_NORMAL__SYNC__STRAIGHT",
			8, // "GP0__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP0__SOUND_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__SOUND_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__BEAT_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__BEAT_NORMAL__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SYNC__STRAIGHT",
			0, // "GP0__BEAT_BOOST__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__BEAT_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__SYMMETRY",
			1, // "GP1__SOUND_NORMAL__SYNC__STRAIGHT",
			1, // "GP1__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP2__FLYWHEEL_BOOST__SEPARATE",
		},
		{ // Boost
			0, // "GP0__NOSOUND",
			0, // "GP0__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__SOUND_NORMAL__SYNC__TWIST",
			1, // "GP0__SOUND_BOOST__SEPARATE__DIRECTION",
			1, // "GP0__SOUND_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__BEAT_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__BEAT_NORMAL__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SYNC__STRAIGHT",
			0, // "GP0__BEAT_BOOST__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__BEAT_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__SYMMETRY",
			0, // "GP1__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP2__FLYWHEEL_BOOST__SEPARATE",
		},
	},
	// STATE_SOUND_DROP,
	{
	},
	// STATE_BEAT_IN,
	{
		{ // Normal
			0, // "GP0__NOSOUND",
			0, // "GP0__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP0__SOUND_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__SOUND_BOOST__SEPARATE__SYMMETRY",
			1, // "GP0__BEAT_NORMAL__SYNC__STRAIGHT",
			1, // "GP0__BEAT_NORMAL__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SYNC__STRAIGHT",
			0, // "GP0__BEAT_BOOST__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__BEAT_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__SYMMETRY",
			0, // "GP1__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP2__FLYWHEEL_BOOST__SEPARATE",
		},
		{ // Boost
			0, // "GP0__NOSOUND",
			0, // "GP0__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP0__SOUND_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__SOUND_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__BEAT_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__BEAT_NORMAL__SYNC__TWIST",
			1, // "GP0__BEAT_BOOST__SYNC__STRAIGHT",
			1, // "GP0__BEAT_BOOST__SYNC__TWIST",
			3, // "GP0__BEAT_BOOST__SEPARATE__DIRECTION",
			3, // "GP0__BEAT_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__SYMMETRY",
			0, // "GP1__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP2__FLYWHEEL_BOOST__SEPARATE",
		},
	},
	// STATE_BEAT_IN_DROP,
	{
	},
	// STATE_FLYWHEEL,
	{
		{ // Normal
			0, // "GP0__NOSOUND",
			0, // "GP0__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP0__SOUND_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__SOUND_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__BEAT_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__BEAT_NORMAL__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SYNC__STRAIGHT",
			0, // "GP0__BEAT_BOOST__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__BEAT_BOOST__SEPARATE__SYMMETRY",
			8, // "GP0__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			8, // "GP0__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__FLYWHEEL_BOOST__SEPARATE__SYMMETRY",
			0, // "GP1__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__SOUND_NORMAL__SYNC__TWIST",
			1, // "GP1__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			1, // "GP1__FLYWHEEL_NORMAL__SYNC__TWIST",
			0, // "GP2__FLYWHEEL_BOOST__SEPARATE",
		},
		{ // Boost
			0, // "GP0__NOSOUND",
			0, // "GP0__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP0__SOUND_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__SOUND_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__BEAT_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__BEAT_NORMAL__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SYNC__STRAIGHT",
			0, // "GP0__BEAT_BOOST__SYNC__TWIST",
			0, // "GP0__BEAT_BOOST__SEPARATE__DIRECTION",
			0, // "GP0__BEAT_BOOST__SEPARATE__SYMMETRY",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP0__FLYWHEEL_NORMAL__SYNC__TWIST",
			5, // "GP0__FLYWHEEL_BOOST__SEPARATE__DIRECTION",
			5, // "GP0__FLYWHEEL_BOOST__SEPARATE__SYMMETRY",
			0, // "GP1__SOUND_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__SOUND_NORMAL__SYNC__TWIST",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__STRAIGHT",
			0, // "GP1__FLYWHEEL_NORMAL__SYNC__TWIST",
			1, // "GP2__FLYWHEEL_BOOST__SEPARATE",
		},
	},
	// STATE_FLYWHEEL_DROP,
	{
	},
};

/************************************************************************************************************************/
} // namespace SPACE_LIGHT{

