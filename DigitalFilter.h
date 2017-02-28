/************************************************************
IIR Filter design with the tool below
	http://hs-soft.exout.net/iir.php

Digital Filterの形
	http://www.picfun.com/dsPIC/dspsw/dspprog02.html

HAS2015
	Sample Freq = 44kHzで設計
Car Audio
	Sample Freq = 44.1kHzで設計
************************************************************/
#pragma once


/************************************************************
************************************************************/
#include <math.h>

#include "ofMain.h"

#include "sj_common.h"


/************************************************************
class
************************************************************/

/**************************************************
**************************************************/
class IIR_1{
private:
	/**************************************************
	**************************************************/
	enum{
		NUM_HISTORY = 2,
	};
	const double Ca, Cb, Cc, Cd; // 1次 IIR Filter
	
	/**************************************************
	for z^-1
	**************************************************/
	double x[NUM_HISTORY];
	double y[NUM_HISTORY];
	
	/**************************************************
	for moving average
	**************************************************/
	const bool Is_move_ave;
	double last_y;

	
public:
	IIR_1(double _Ca, double _Cb, double _Cc, double _Cd, bool f_move_ave = true)
	: Ca(_Ca), Cb(_Cb), Cc(_Cc), Cd(_Cd)
	, Is_move_ave(f_move_ave), last_y(0)
	{
		for(int i = 0; i < NUM_HISTORY; i++){
			x[i] = 0; y[i] = 0;
		}
	}
	
	double x_in(double _x);
	
	double get_y();
};

/**************************************************
**************************************************/
class IIR_2{
private:
	/****************************************
	****************************************/
	enum{
		NUM_HISTORY = 3,
	};
	const double Ca, Cb, Cc, Cd, Ce, Cf; // 2次 IIR Filter
	
	/****************************************
	for z^-1
	****************************************/
	double x[NUM_HISTORY];
	double y[NUM_HISTORY];
	
	/****************************************
	for moving average
	****************************************/
	const bool Is_move_ave;
	double last_y;

	
public:
	IIR_2(double _Ca, double _Cb, double _Cc, double _Cd, double _Ce, double _Cf, bool f_move_ave = true)
	: Ca(_Ca), Cb(_Cb), Cc(_Cc), Cd(_Cd), Ce(_Ce), Cf(_Cf)
	, Is_move_ave(f_move_ave), last_y(0)
	{
		for(int i = 0; i < NUM_HISTORY; i++){
			x[i] = 0; y[i] = 0;
		}
	}
	
	double x_in(double _x);
	
	double get_y();
};

/**************************************************
**************************************************/
class IIR_4{
private:
	/****************************************
	****************************************/
	IIR_2 iir2_0;
	IIR_2 iir2_1;
	

	
public:
	IIR_4(	double _Ca0, double _Cb0, double _Cc0, double _Cd0, double _Ce0, double _Cf0,
			double _Ca1, double _Cb1, double _Cc1, double _Cd1, double _Ce1, double _Cf1,
			bool f_move_ave = true)
	: iir2_0(_Ca0, _Cb0, _Cc0, _Cd0, _Ce0, _Cf0, false)
	, iir2_1(_Ca1, _Cb1, _Cc1, _Cd1, _Ce1, _Cf1, f_move_ave)
	{
	}
	
	double x_in(double _x);
	double get_y();
};


/************************************************************
class
************************************************************/

/**************************************************
**************************************************/
class SOUND_FILTER{
private:
	/****************************************
	****************************************/
	IIR_2 iir2_through;
	IIR_4 iir4_LPF;
	IIR_4 iir4_BPF;
	IIR_4 iir4_LPF_forSoundSync;
	
public:
	/****************************************
	****************************************/
	enum{
		VOL_THROUGH,
		VOL_LPF,
		VOL_BPF,
		VOL_SOUNDSYNC,
		
		NUM_VOL_TYPES,
	};
	
	/****************************************
	****************************************/
	SOUND_FILTER();
	~SOUND_FILTER();
	
	void x_in(float val);
	
	double get_y(int VolType);
};




