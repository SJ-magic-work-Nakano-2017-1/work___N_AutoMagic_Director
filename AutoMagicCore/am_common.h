/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxNetwork.h"

#include "../sj_common.h"
#include "DeviceCh.h"


/************************************************************
************************************************************/
enum STATE{
	STATE_NOSOUND,
	
	STATE_SOUND,
	STATE_SOUND_DROP,
	
	STATE_BEAT_IN,
	STATE_BEAT_IN_DROP,
	
	STATE_FLYWHEEL,
	STATE_FLYWHEEL_DROP,
	
	NUM_STATES,
};

enum STATE__BEAT_DETECT{
	STATE_WAIT_1ST_PEAK,
	STATE_WAIT_NEXT_PEAK,
	STATE_KEEP_PEAK,
};

enum TRANSITION{
	BOOT_TO_NOSOUND,
	
	NOSOUND_TO_NOSOUND,
	NOSOUND_TO_SOUND,
	
	SOUND_TO_SOUND,
	SOUND_TO_BEATIN,
	SOUND_TO_SOUNDDROP,
	
	SOUNDDROP_TO_NOSOUND,
	SOUNDDROP_TO_SOUND,
	
	BEATIN_TO_BEATIN,
	BEATIN_TO_FLYWHEEL,
	BEATIN_TO_BEATINDROP,
	
	BEATINDROP_TO_NOSOUND,
	BEATINDROP_TO_SOUND,
	BEATINDROP_TO_BEATIN,
	
	FLYWHEEL_TO_FLYWHEEL,
	FLYWHEEL_TO_FLYWHEELDROP,
	
	FLYWHEELDROP_TO_NOSOUND,
	FLYWHEELDROP_TO_SOUND,
	
	
	NUM_TRANSITIONS,
};

enum BOOSTMODE{
	BOOSTMODE_NORMAL,
	BOOSTMODE_BOOST,
	
	NUM_BOOSTMODE,
};

enum PLAYMODE{
	BEAT_PROPULSION,
	SELF_PROPULSION,
	
	NUM_PLAYMODES,
};



/************************************************************
class
************************************************************/

/**************************************************
**************************************************/
class OSC_SEND{
private:
	char IP[BUF_SIZE];
	int Port;

	ofxOscSender sender;
	
public:
	OSC_SEND(const char* _IP, int _Port)
	{
		if(_Port != -1){
			sprintf(IP, "%s", _IP);
			Port = _Port;
			
			sender.setup(IP, Port);
		}
	}
	
	void sendMessage(ofxOscMessage &message)
	{
		if(Port != -1){
			sender.sendMessage(message);
		}
	}
};

class OSC_RECEIVE{
private:
	int Port;
	ofxOscReceiver	receiver;
	
public:
	OSC_RECEIVE(int _Port)
	{
		if(_Port != -1){
			Port = _Port;
			receiver.setup(Port);
		}
	}
	
	bool hasWaitingMessages()
	{
		if(Port == -1){
			return false;
		}else{
			return receiver.hasWaitingMessages();
		}
	}
	
	bool getNextMessage(ofxOscMessage *msg)
	{
		if(Port == -1){
			return false;
		}else{
			return receiver.getNextMessage(msg);
		}
	}
};

class OSC_TARGET{
private:
public:
	OSC_SEND	OscSend;
	OSC_RECEIVE	OscReceive;
	
	OSC_TARGET(const char* _SendTo_IP, int _SendTo_Port, int _Receive_Port)
	: OscSend(_SendTo_IP, _SendTo_Port), OscReceive(_Receive_Port)
	{
	}
};


/************************************************************
************************************************************/
/********************
********************/
extern bool b_Fileout;
extern bool b_Demo;

extern int now_ms;
extern int LastINT_ms;

extern const int Beat_interval_amb;
extern const int Beat_interval_temp;

extern int Beat_interval;
extern int self_Beat_interval;

extern int LastBeat_ms;

extern const PALETTE Palette[];
extern const PALETTE *system_ColorTheme_palette;

extern int PATTERN_CHANGE_BEATS;

/********************
********************/
extern int debug_int[10];
extern double debug_PatternChange[10];



/************************************************************
global function
************************************************************/

/********************
common.cpp
********************/
extern void printMessage(const char* message);
extern int Dice_index(int *Weight, int NUM);

/********************
xxx.cpp
********************/
extern void HF_debug_log(FILE* fp, int now_ms);
extern BOOSTMODE get_BoostMode();
extern bool DB_isDoubtSetInThisState();
extern void ColorPalette_AutoChange(int OperationType);


/************************************************************
[alias of fprintf]
template function : should be in .h
	fprintf_Log
		comment.
		used for both Dmx and Vj.
		
	fprintf_Log_forTestCode
		for test code
		
	fprintf_Dmx
		Dmx param
		
	fprintf_Vj_ContentsChangeTiming
	fprintf_Vj_ColorTheme
	fprintf_Vj_Alpha_fft
	fprintf_Vj_BpmInfo
************************************************************/

/******************************
[C++11 ~] variadic templates
******************************/
template <typename ... Args>
void fprintf_Log(FILE* fp, const char *format, Args const & ... args)
{
	if(b_Fileout) fprintf(fp, format, args ...);
}
void fprintf_Log(FILE* fp, const char *format)
{
	if(b_Fileout) fprintf(fp, "%s", format);
}

/******************************
******************************/
template <typename ... Args>
void fprintf_Log_forTestCode(FILE* fp, const char *format, Args const & ... args)
{
	if(b_Fileout) fprintf(fp, format, args ...);
}
void fprintf_Log_forTestCode(FILE* fp, const char *format)
{
	if(b_Fileout) fprintf(fp, "%s", format);
}

/******************************
******************************/
template <typename ... Args>
void fprintf_Dmx(FILE* fp, const char *format, Args const & ... args)
{
	if(b_Fileout) fprintf(fp, format, args ...);
}
void fprintf_Dmx(FILE* fp, const char *format)
{
	if(b_Fileout) fprintf(fp, "%s", format);
}

/******************************
******************************/
template <typename ... Args>
void fprintf_Vj_ContentsChangeTiming(FILE* fp, const char *format, Args const & ... args)
{
	if(b_Fileout) fprintf(fp, format, args ...);
}
void fprintf_Vj_ContentsChangeTiming(FILE* fp, const char *format)
{
	if(b_Fileout) fprintf(fp, "%s", format);
}

/******************************
******************************/
template <typename ... Args>
void fprintf_Vj_ColorTheme(FILE* fp, const char *format, Args const & ... args)
{
	if(b_Fileout) fprintf(fp, format, args ...);
}
void fprintf_Vj_ColorTheme(FILE* fp, const char *format)
{
	if(b_Fileout) fprintf(fp, "%s", format);
}

/******************************
******************************/
template <typename ... Args>
void fprintf_Vj_Alpha_fft(FILE* fp, const char *format, Args const & ... args)
{
	if(b_Fileout) fprintf(fp, format, args ...);
}
void fprintf_Vj_Alpha_fft(FILE* fp, const char *format)
{
	if(b_Fileout) fprintf(fp, "%s", format);
}

/******************************
******************************/
template <typename ... Args>
void fprintf_Vj_BpmInfo(FILE* fp, const char *format, Args const & ... args)
{
	if(b_Fileout) fprintf(fp, format, args ...);
}
void fprintf_Vj_BpmInfo(FILE* fp, const char *format)
{
	if(b_Fileout) fprintf(fp, "%s", format);
}

