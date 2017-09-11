/************************************************************
************************************************************/
#include "ofMain.h"
#include "am_common.h"

#include <stdio.h>
#include <stdlib.h>


/************************************************************
param
************************************************************/

/********************
********************/
bool b_Fileout = false;
bool b_Demo = false;

int now_ms = 0;
int LastINT_ms = 0;

const int Beat_interval_amb = 3000;
const int Beat_interval_temp = 550;

int Beat_interval		= Beat_interval_amb;
int self_Beat_interval	= Beat_interval_amb;

int LastBeat_ms = 0;

int PATTERN_CHANGE_BEATS = 16;


/********************
********************/
int debug_int[10]				= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double debug_PatternChange[10]	= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


/********************
palette for multi color
********************/
const PALETTE Palette[] = {
	{ // COLPATTERN_AQUA
		2000,
		
		{ // LedBase
			{{0, 0, 255}, 6},
			{{0, 255, 255}, 2},
			{{0, 150, 255}, 3},
			
			{{0, 0, 0}, -1},
		},
		{ // LedFlash
			{{255, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
	},

	{ // COLPATTERN_MAGMA
		2000,
		
		{ // LedBase
			{{255, 0, 0}, 6},
			{{255, 140, 0}, 3},
			{{255, 255, 0}, 2},
			
			{{0, 0, 0}, -1},
		},
		{ // LedFlash
			{{255, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
	},

	{ // COLPATTERN_SEXY
		2000,
		
		{ // LedBase
			{{120, 0, 255}, 4},
			{{255, 0, 255}, 3},
			{{0, 0, 255}, 2},
			
			{{0, 0, 0}, -1},
		},
		{ // LedFlash
			{{255, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
	},
	
	{ // COLPATTERN_SWEETS
		2000,
		
		{ // LedBase
			{{255, 0, 255}, 1},
			{{255, 255, 0}, 1},
			{{0, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
		{ // LedFlash
			{{255, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
	},
	
	{ // COLPATTERN_RAINBOW
		2000,
		
		{ // LedBase
			{{255, 0, 0}, 1},
			{{255, 255, 0}, 1},
			{{0, 255, 0}, 1},
			{{0, 255, 255}, 1},
			{{0, 0, 255}, 1},
			{{255, 0, 255}, 1},
			{{120, 0, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
		{ // LedFlash
			{{255, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
	},
	
	{ // COLPATTERN_DIGITAL
		2000,
		
		{ // LedBase
			{{0, 255, 0}, 6},
			{{255, 255, 0}, 3},
			{{0, 255, 255}, 2},
			
			{{0, 0, 0}, -1},
		},
		{ // LedFlash
			{{255, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
	},
	
	{ // COLPATTERN_TRIP
		2000,
		
		{ // LedBase
			{{255, 0, 0}, 5},
			{{0, 0, 255}, 5},
			{{255, 0, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
		{ // LedFlash
			{{255, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
	},
	
	{ // COLPATTERN_REGGAE
		2000,
		
		{ // LedBase
			{{255, 0, 0}, 4},
			{{0, 255, 0}, 3},
			{{255, 255, 0}, 3},
			
			{{0, 0, 0}, -1},
		},
		{ // LedFlash
			{{255, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
	},
	
	{ // COLPATTERN_SAMBA
		2000,
		
		{ // LedBase
			{{0, 255, 0}, 4},
			{{255, 255, 0}, 4},
			{{0, 0, 255}, 1},
			{{0, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
		{ // LedFlash
			{{255, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
	},
	
	{ // COLPATTERN_BLIZZARD
		2000,
		
		{ // LedBase
			{{255, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
		{ // LedFlash
			{{255, 255, 255}, 1},
			
			{{0, 0, 0}, -1},
		},
	},
};

const PALETTE *system_ColorTheme_palette = &Palette[COLPATTERN_AQUA];



/************************************************************
function
************************************************************/

/******************************
******************************/
int Dice_index(int *Weight, int NUM)
{
	/***********************
	cal sum of Weight
	***********************/
	int TotalWeight = 0;
	int i;
	for(i = 0; i < NUM; i++){
		TotalWeight += Weight[i];
	}
	
	if(TotalWeight == 0) { return -1; }
	
	/***********************
	random number
	***********************/
	int RandomNumber = rand() % TotalWeight;
	
	/***********************
	define play mode
	***********************/
	int index;
	for(TotalWeight = 0, index = 0; /* */; index++){
		TotalWeight += Weight[index];
		if(RandomNumber < TotalWeight) break;
	}
	
	return index;
}

/******************************
******************************/
void printMessage(const char* message)
{
	printf("\n> %s\n", message);
}



