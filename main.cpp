#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( int argc, char** argv ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	
	int BootMode;
	int soundStream_Input_DeviceId;
	int soundStream_Output_DeviceId;
	if(argc < 4){
		BootMode = -1;
		soundStream_Input_DeviceId = -1;
		soundStream_Output_DeviceId = -1;
		
		printf("*.exe BootMode InputId OutputId\n\n");
		
		int i = 0;
		printf("\t%d:Test\n", i); i++;
		printf("\t%d:Check FilterOut\n", i); i++;
		printf("\t%d:Check DesignParam\n", i); i++;
		printf("\t%d:Demo with Log\n", i); i++;
		printf("\t%d:Demo without Log\n", i); i++;
		printf("\n");
	
	}else{
		BootMode = atoi(argv[1]);
		soundStream_Input_DeviceId = atoi(argv[2]);
		soundStream_Output_DeviceId = atoi(argv[3]);
	}
	ofRunApp(new ofApp(BootMode, soundStream_Input_DeviceId, soundStream_Output_DeviceId));
}
