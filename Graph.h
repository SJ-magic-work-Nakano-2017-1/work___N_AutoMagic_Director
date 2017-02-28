/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxGui.h"

#include "sj_common.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
struct GRAPH_DATA{
	/********************
	main
	********************/
	int VolThrough;
	int VolLpf;
	
	int f_Beat;
	int f_State;
	double f_DoubtBeat;
	
	double f_Light_TangibleChange;
	double f_Light_PatternChange;
	double f_vj_PatternChange;
	double f_vj_ContentsChange;
	
	/********************
	High & Boost
	********************/
	int VolBpf;
	double tan_HighFreq;
	int f_Boost;
	
	/********************
	IsLock & VolSoudSync
	********************/
	double VolSoundSync;
	int f_StateIsLock;
};

/**************************************************
**************************************************/
class GRAPH : public ofThread{
private:
	/****************************************
	****************************************/
	enum{
		THREAD_SLEEP_MS = 1,
		
		NUM_POINTS = WIDTH,
	};
	
	enum DATA_TYPE{
		/* */
		DATA__VOL_THROUGH,
		DATA__VOL_LPF,
		DATA__BEAT,
		DATA__STATE,
		DATA__DOUBT_BEAT,
		
		DATA__LIGHT_TANGIBLEPATTERN_CHANGE,
		DATA__LIGHT_PATTERN_CHANGE,
		DATA__VJ_PATTERN_CHANGE,
		DATA__VJ_CONTENTS_CHANGE,
		
		/* */
		DATA__VOL_BPF,
		DATA__TAN_HIGH_FREQ,
		DATA__BOOST,
		
		/* */
		DATA__VOL_SOUNDSYNC,
		DATA__STATE_IS_LOCK,
		DATA__BEAT2,
		
		NUM_DATA_TYPES,
	};

	/****************************************
	****************************************/
	/********************
	********************/
	ofxPanel gui;
	
	ofxGuiGroup GuiGroup_main;
	ofxIntSlider max_of_Volume;
	
	ofxGuiGroup GuiGroup_HighBoost;
	ofxIntSlider max_of_Volume_VolHigh;
	ofxFloatSlider range_tangent_HighFreq;
	
	/********************
	********************/
	ofVbo Vbo[NUM_DATA_TYPES];
	ofVec3f VboVerts[NUM_DATA_TYPES][NUM_POINTS];
	ofFloatColor VboColor[NUM_DATA_TYPES][NUM_POINTS];
	
	
	/****************************************
	****************************************/
	void RefreshVerts(DATA_TYPE DataType, double NewVal);
	void draw_mainData();
	void draw_High_Boost();
	void draw_IsLock_volSoundSync();
	
public:
	/****************************************
	****************************************/
	GRAPH();
	~GRAPH();
	
	void setup();
	void update(GRAPH_DATA& GraphData);
	void draw();
	void keyPressed(int key);
	
	void threadedFunction();
};
