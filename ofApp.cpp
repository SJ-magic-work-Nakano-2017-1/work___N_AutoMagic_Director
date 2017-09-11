/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(int _BootMode, int _soundStream_Input_DeviceId, int _soundStream_Output_DeviceId)
: BootMode(BOOT_MODE(_BootMode))
, fp_Filterout(NULL)
, soundStream_Input_DeviceId(_soundStream_Input_DeviceId)
, soundStream_Output_DeviceId(_soundStream_Output_DeviceId)
, AutoMagicCore(AUTOMAGIC_CORE::getInstance())
, png_id(0)
{
}

/******************************
******************************/
ofApp::~ofApp()
{
	/********************
	********************/
	if(fp_Filterout)	fclose(fp_Filterout);
}

/******************************
******************************/
void ofApp::exit()
{
	if(BootMode != MODE__NOSET){
		/********************
		********************/
		AutoMagicCore->exit();
		
		/********************
		ofAppとaudioが別threadなので、ここで止めておくのが安全.
		********************/
		soundStream.stop();
		soundStream.close();
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	font.loadFont("RictyDiminished-Regular.ttf", 12);
	
	/********************
	********************/
	ofSetWindowTitle("Director");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(WIDTH, HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableSmoothing();
	
	/********************
	********************/
	soundStream.listDevices();
	if( (BootMode == MODE__NOSET) || (soundStream_Input_DeviceId == -1) || (soundStream_Output_DeviceId == -1) ){
		ofExit();
		return;
	}
	// soundStream.setDeviceID(soundStream_DeviceId);
	/* set in & out respectively. */
	soundStream.setInDeviceID(soundStream_Input_DeviceId);  
	soundStream.setOutDeviceID(soundStream_Output_DeviceId);
	
	soundStream.setup(this, 2/* out */, 2/* in */, AUDIO_SAMPLERATE, AUDIO_BUF_SIZE, AUDIO_BUFFERS);
	
	AudioSample.reserve(AUDIO_BUF_SIZE);
	
	/********************
	********************/
	AutoMagicCore->setup(BootMode);
	
	switch(BootMode){
		case MODE__TEST:
		{
			test();
			ofExit();
			return;
		}
			
		case MODE__CHECK_FILTEROUT:
			fp_Filterout = fopen("../../../check_Filterout.csv", "w");
			if(fp_Filterout == NULL){
				ERROR_MSG();
				std::exit(1);
			}
			break;
			
		default:
			break;
	}
	
	/********************
	********************/
	Graph.setup();
}

/******************************
******************************/
void ofApp::test()
{
	AutoMagicCore->test();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	ofBackground(20);
	
	/********************
	********************/
	Graph.lock();
	Graph.draw();
	Graph.unlock();
	
	AutoMagicCore->lock();
	AutoMagicCore->draw_gui();
	AutoMagicCore->unlock();
	
	/********************
	********************/
	ofPushStyle();
	
	draw_time();
	
	ofPopStyle();
}

/******************************
******************************/
void ofApp::draw_time()
{
	float now_sec = ofGetElapsedTimef();
	
	/********************
	********************/
	char buf[BUF_SIZE];
	
	int hour = now_sec / 60 / 60;
	int min	= now_sec / 60;
	int sec	= now_sec - min * 60;
	
	sprintf(buf, "%6d:%6d:%6d", hour, min, sec);
	
	/********************
	********************/
	ofSetColor(255, 255, 255);
	
	font.drawString(buf, 10, 30);
}

/******************************
audioIn/ audioOut
	同じthreadで動いている様子。
	また、audioInとaudioOutは、同時に呼ばれることはない(多分)。
	つまり、ofAppからaccessがない限り、変数にaccessする際にlock/unlock する必要はない。
	ofApp側からaccessする時は、threadを立てて、安全にpassする仕組みが必要(cf:NotUsed__thread_safeAccess.h)
	...ReferenceとSetで違う変数を用意し、このpassはthreadの向こう側で行う。
******************************/
void ofApp::audioIn(float *input, int bufferSize, int nChannels)
{
    for (int i = 0; i < bufferSize; i++) {
        AudioSample.Left[i] = input[2*i];
		AudioSample.Right[i] = input[2*i+1];
    }
}  

/******************************
******************************/
void ofApp::audioOut(float *output, int bufferSize, int nChannels)
{
	/********************
	********************/
	float now_sec = ofGetElapsedTimef();
	double vol_Raw = 0;
	
	/********************
	input -> output
	Filtering
	********************/
    for (int i = 0; i < bufferSize; i++) {
		/* */
		output[2*i] = AudioSample.Left[i];
		output[2*i+1] = AudioSample.Right[i];
		
		/* */
		Sound_Filter.x_in(AudioSample.Left[i]);
		
		/* */
		vol_Raw += AudioSample.Left[i] * AudioSample.Left[i];
    }
	vol_Raw = sqrt(vol_Raw / bufferSize);
	
	/* 1 output / BufferBlock */
	if(BootMode == MODE__CHECK_FILTEROUT){
		fprintf(fp_Filterout, "%f,%f,%f,%f,%f\n", now_sec, Sound_Filter.get_y(SOUND_FILTER::VOL_THROUGH), Sound_Filter.get_y(SOUND_FILTER::VOL_LPF), Sound_Filter.get_y(SOUND_FILTER::VOL_BPF), Sound_Filter.get_y(SOUND_FILTER::VOL_SOUNDSYNC));
		
	}else{
		AutoMagicCore->INT(Graph, now_sec, vol_Raw, Sound_Filter.get_y(SOUND_FILTER::VOL_THROUGH), Sound_Filter.get_y(SOUND_FILTER::VOL_LPF), Sound_Filter.get_y(SOUND_FILTER::VOL_BPF), Sound_Filter.get_y(SOUND_FILTER::VOL_SOUNDSYNC));
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	enum KEY_STATE{
		KEY_MAIN,
		KEY_GRAPH,
	};
	static KEY_STATE KeyState = KEY_MAIN;
	
	if(KeyState == KEY_MAIN){
		switch(key){
			case ' ':
			{
				/********************
				********************/
				char buf[BUF_SIZE];
				
				sprintf(buf, "image_%d.png", png_id);
				ofSaveScreen(buf);
				
				png_id++;
				
				/********************
				********************/
				printf("%s saved\n", buf);
			}
				break;
				
			case 'g':
				KeyState = KEY_GRAPH;
				break;
				
			case 'l':
				AutoMagicCore->set__b_Fileout(true);
				break;
				
			default:
				break;
		}
		
	}else{
		if(KeyState == KEY_GRAPH){
			Graph.keyPressed(key);
		}
		
		KeyState = KEY_MAIN;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
