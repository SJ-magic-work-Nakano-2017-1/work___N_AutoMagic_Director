/************************************************************
************************************************************/
#include "Graph.h"

/************************************************************
************************************************************/

/******************************
******************************/
GRAPH::GRAPH()
{
}

/******************************
******************************/
GRAPH::~GRAPH()
{
}

/******************************
******************************/
void GRAPH::threadedFunction(){
	while(isThreadRunning()) {
		lock();
		
		unlock();
		
		sleep(THREAD_SLEEP_MS);
	}
}

/******************************
******************************/
void GRAPH::setup()
{
	/********************
	********************/
	gui.setup();
	
	GuiGroup_main.setup("main");
	GuiGroup_main.add(max_of_Volume.setup("max Volume", 10000, 1000, 10000));
	gui.add(&GuiGroup_main);
	
	GuiGroup_HighBoost.setup("HighBoost");
	GuiGroup_HighBoost.add(max_of_Volume_VolHigh.setup("max Volume", 2000, 500, 2000));
	GuiGroup_HighBoost.add(range_tangent_HighFreq.setup("range_tan_HF", 0.5, 0.1, 2.0));
	gui.add(&GuiGroup_HighBoost);
	
	/********************
	********************/
	/* Verts */
	for(int i = 0; i < NUM_DATA_TYPES; i++){
		for(int j = 0; j < NUM_POINTS; j++){
			VboVerts[i][j].set(j, 0);
		}
	}
	
	/* color */
	// main
	double alpha = 0.7;
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__VOL_THROUGH][j].set(0.0, 0.5, 1.0, alpha); }
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__VOL_LPF][j].set(1.0, 0.0, 0.0, alpha); }
	
	alpha = 0.5;
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__BEAT][j].set(0.0, 1.0, 0.0, alpha); }
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__STATE][j].set(1.0, 0.0, 0.5, alpha); }
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__DOUBT_BEAT][j].set(0.0, 1.0, 1.0, alpha); }
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__LIGHT_TANGIBLEPATTERN_CHANGE][j].set(1.0, 0.5, 0.0, alpha); }
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__LIGHT_PATTERN_CHANGE][j].set(0.0, 0.5, 1.0, alpha); }
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__VJ_PATTERN_CHANGE][j].set(0.0, 1.0, 0.0, alpha); }
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__VJ_CONTENTS_CHANGE][j].set(1.0, 0.0, 0.0, alpha); }
	
	// High & Boost
	alpha = 0.7;
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__VOL_BPF][j].set(0.0, 0.5, 1.0, alpha); }
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__TAN_HIGH_FREQ][j].set(1.0, 0.0, 0.0, alpha); }
	
	alpha = 0.5;
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__BOOST][j].set(0.0, 1.0, 0.0, alpha); }
	
	// IsLock & vol_fft
	alpha = 0.7;
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__VOL_SOUNDSYNC][j].set(0.0, 0.5, 1.0, alpha); }
	
	alpha = 0.5;
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__STATE_IS_LOCK][j].set(1.0, 0.0, 0.0, alpha); }
	for(int j = 0; j < NUM_POINTS; j++) { VboColor[DATA__BEAT2][j].set(0.0, 1.0, 0.0, alpha); }
	
	/********************
	********************/
	for(int i = 0; i < NUM_DATA_TYPES; i++){
		Vbo[i].setVertexData(VboVerts[i], NUM_POINTS, GL_DYNAMIC_DRAW);
		Vbo[i].setColorData(VboColor[i], NUM_POINTS, GL_DYNAMIC_DRAW);
	}
}

/******************************
******************************/
void GRAPH::update(GRAPH_DATA& GraphData)
{
	/********************
	********************/
	int Height = HEIGHT/2;
	RefreshVerts(DATA__VOL_THROUGH, ofMap(GraphData.VolThrough, 0, max_of_Volume, 0, Height));
	RefreshVerts(DATA__VOL_LPF, ofMap(GraphData.VolLpf, 0, max_of_Volume, 0, Height));
	
	RefreshVerts(DATA__BEAT, ofMap(GraphData.f_Beat, 0, 10, 0, Height));
	RefreshVerts(DATA__STATE, ofMap(GraphData.f_State, 0, 10, 0, Height));
	RefreshVerts(DATA__DOUBT_BEAT, ofMap(GraphData.f_DoubtBeat, 0, 10, 0, Height));
	RefreshVerts(DATA__LIGHT_TANGIBLEPATTERN_CHANGE, ofMap(GraphData.f_Light_TangibleChange, 0, 10, 0, Height));
	RefreshVerts(DATA__LIGHT_PATTERN_CHANGE, ofMap(GraphData.f_Light_PatternChange, 0, 10, 0, Height));
	RefreshVerts(DATA__VJ_PATTERN_CHANGE, ofMap(GraphData.f_vj_PatternChange, 0, 10, 0, Height));
	RefreshVerts(DATA__VJ_CONTENTS_CHANGE, ofMap(GraphData.f_vj_ContentsChange, 0, 10, 0, Height));
	
	/********************
	********************/
	Height = HEIGHT/4;
	RefreshVerts(DATA__VOL_BPF, ofMap(GraphData.VolBpf, 0, max_of_Volume_VolHigh, 0, Height));
	
	RefreshVerts(DATA__TAN_HIGH_FREQ, ofMap(GraphData.tan_HighFreq, -range_tangent_HighFreq, range_tangent_HighFreq, 0, Height));
	RefreshVerts(DATA__BOOST, ofMap(GraphData.f_Boost, 0, 4, 0, Height));

	/********************
	********************/
	Height = HEIGHT/4;
	RefreshVerts(DATA__VOL_SOUNDSYNC, ofMap(GraphData.VolSoundSync, 0, 1.0, 0, Height));
	RefreshVerts(DATA__STATE_IS_LOCK, ofMap(GraphData.f_StateIsLock, 0, 4, 0, Height));
	RefreshVerts(DATA__BEAT2, ofMap(GraphData.f_Beat, 0, 6, 0, Height));
}

/******************************
******************************/
void GRAPH::RefreshVerts(DATA_TYPE DataType, double NewVal)
{
	for(int i = 0; i < NUM_POINTS - 1; i++){
		VboVerts[DataType][i].set(i, VboVerts[DataType][i + 1].y);
	}
	VboVerts[DataType][NUM_POINTS - 1].set(NUM_POINTS - 1, NewVal);
}

/******************************
******************************/
void GRAPH::draw_mainData()
{
	ofPushMatrix();
		ofTranslate(0, ofGetHeight() - 1); // so that i can see zero Level.
		ofScale(1, -1, 1);
		
		/********************
		********************/
		/* */
		glPointSize(2.0);
		Vbo[DATA__VOL_THROUGH].draw(GL_LINE_STRIP, 0, NUM_POINTS);
		Vbo[DATA__VOL_LPF].draw(GL_LINE_STRIP, 0, NUM_POINTS);
		
		/* */
		glPointSize(1.5);
		Vbo[DATA__BEAT].draw(GL_LINE_STRIP, 0, NUM_POINTS);
		Vbo[DATA__STATE].draw(GL_LINE_STRIP, 0, NUM_POINTS);
		Vbo[DATA__DOUBT_BEAT].draw(GL_LINE_STRIP, 0, NUM_POINTS);
		
		glPointSize(3.0);
		Vbo[DATA__LIGHT_TANGIBLEPATTERN_CHANGE].draw(GL_POINTS, 0, NUM_POINTS);
		Vbo[DATA__LIGHT_PATTERN_CHANGE].draw(GL_POINTS, 0, NUM_POINTS);
		Vbo[DATA__VJ_PATTERN_CHANGE].draw(GL_POINTS, 0, NUM_POINTS);
		Vbo[DATA__VJ_CONTENTS_CHANGE].draw(GL_POINTS, 0, NUM_POINTS);
		
		/********************
		y 目盛り
		********************/
		ofSetLineWidth(1);
		const int Step = 1e3;
		int Height = HEIGHT/2;
		int y_Disp;
		for(int y = 0; y_Disp = ofMap(y, 0, max_of_Volume, 0, Height), y_Disp < Height; y += Step){
			ofSetColor(120);
			ofDrawBitmapString( ofToString(y), 10, y_Disp );
			
			ofSetColor(50);
			ofDrawLine(0, y_Disp, WIDTH - 1, y_Disp);
		}
	ofPopMatrix();
}

/******************************
******************************/
void GRAPH::draw_High_Boost()
{
	ofPushMatrix();
		ofTranslate(0, ofGetHeight() / 2);
		ofScale(1, -1, 1);
		
		/********************
		********************/
		ofFill();
		ofSetColor(0, 0, 255, 40);
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight()/4);
		
		/********************
		********************/
		/* */
		glPointSize(2.0);
		Vbo[DATA__VOL_BPF].draw(GL_LINE_STRIP, 0, NUM_POINTS);
		Vbo[DATA__TAN_HIGH_FREQ].draw(GL_LINE_STRIP, 0, NUM_POINTS);
		
		/* */
		glPointSize(1.5);
		Vbo[DATA__BOOST].draw(GL_LINE_STRIP, 0, NUM_POINTS);
		
		/********************
		y 目盛り
		********************/
		/* center */
		ofSetLineWidth(2);
		ofSetColor(50);
		ofDrawLine(0, ofGetHeight()/8, WIDTH - 1, ofGetHeight()/8);
		
		/* */
		ofSetLineWidth(1);
		const int Step = 200;
		int Height = ofGetHeight()/4;
		int y_Disp;
		for(int y = 0; y_Disp = ofMap(y, 0, max_of_Volume_VolHigh, 0, Height), y_Disp < Height; y += Step){
			ofSetColor(120);
			ofDrawBitmapString( ofToString(y), 10, y_Disp );
			
			ofSetColor(50);
			ofDrawLine(0, y_Disp, WIDTH - 1, y_Disp);
		}
		
	ofPopMatrix();
}

/******************************
******************************/
void GRAPH::draw_IsLock_volSoundSync()
{
	ofPushMatrix();
		ofTranslate(0, ofGetHeight() / 4);
		ofScale(1, -1, 1);
		
		/********************
		********************/
		/*
		ofFill();
		ofSetColor(0, 255, 0, 50);
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight()/4);
		*/
		
		/********************
		********************/
		/* */
		glPointSize(2.0);
		Vbo[DATA__VOL_SOUNDSYNC].draw(GL_LINE_STRIP, 0, NUM_POINTS);
		
		/* */
		glPointSize(1.5);
		Vbo[DATA__STATE_IS_LOCK].draw(GL_LINE_STRIP, 0, NUM_POINTS);
		Vbo[DATA__BEAT2].draw(GL_LINE_STRIP, 0, NUM_POINTS);
		
		/********************
		y 目盛り
		********************/
		ofSetLineWidth(1);
		ofSetColor(50);
		ofDrawLine(0, ofGetHeight()/8, WIDTH - 1, ofGetHeight()/8);
		
	ofPopMatrix();
}

/******************************
******************************/
void GRAPH::draw()
{
	/********************
	********************/
	for(int i = 0; i < NUM_DATA_TYPES; i++){
		Vbo[i].updateVertexData(VboVerts[i], NUM_POINTS);
	}		
	
	/********************
	********************/
	ofPushStyle();
		/********************
		********************/
		draw_mainData();
		draw_High_Boost();
		draw_IsLock_volSoundSync();
		
		/********************
		sampleFreq	44.1 kHz
		Width		1280
		
		全画面で14.86[sec]
		1secごとの縦ラインをここで描画.
		********************/
		ofSetColor(50);
		ofSetLineWidth(1);
		const double x_step = ofGetWidth() / 14.86;
		for(int i = 0; i * x_step < ofGetWidth(); i++){
			int x = int(i * x_step + 0.5);
			ofLine(x, 0, x, ofGetHeight() - 1 );
		}
		
	ofPopStyle();
		
	/********************
	********************/
	gui.draw();
}

/******************************
******************************/
void GRAPH::keyPressed(int key)
{
	switch(key){
		default:
			break;
	}
}

