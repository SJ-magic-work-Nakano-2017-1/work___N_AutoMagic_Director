/************************************************************
// test code
void AUTOMAGIC_CORE::test()
{
	FILE* fp;
	fp = fopen("../../../color.txt", "w");
	
	for(int i = 0; i < int(COLPATTERN_AUTO); i++){
		fprintf_Log_forTestCode(fp, "[%d]----------\n", i);
		fprintf_Log_forTestCode(fp, "> Base Color\n");
		for(int j = 0; Palette[i].LedBase[j].Weight != -1; j++){
			fprintf_Log_forTestCode(fp, "(%3d, %3d, %3d), %d\n", Palette[i].LedBase[j].LedColor.R, Palette[i].LedBase[j].LedColor.G, Palette[i].LedBase[j].LedColor.B, Palette[i].LedBase[j].Weight);
		}
		fprintf_Log_forTestCode(fp, "\n> Strobe Color\n");
		for(int j = 0; Palette[i].LedFlash[j].Weight != -1; j++){
			fprintf_Log_forTestCode(fp, "(%3d, %3d, %3d), %d\n", Palette[i].LedFlash[j].LedColor.R, Palette[i].LedFlash[j].LedColor.G, Palette[i].LedFlash[j].LedColor.B, Palette[i].LedFlash[j].Weight);
		}
		fprintf_Log_forTestCode(fp, "\n");
	}
	
	fclose(fp);
}
************************************************************/


#pragma once

/************************************************************
************************************************************/
enum{
	MAX_COLOR_SETS = 20,
};

enum COLORPATTERNS{
	COLPATTERN_AQUA,
	COLPATTERN_MAGMA,
	COLPATTERN_DIGITAL,
	COLPATTERN_SEXY,
	
	COLPATTERN_TRIP,
	COLPATTERN_REGGAE,
	COLPATTERN_SAMBA,
	COLPATTERN_SWEETS,
	// Å™à»è„:AutoÇ≈égóp
	
	COLPATTERN_RAINBOW,
	COLPATTERN_BLIZZARD,
	
	
	COLPATTERN_AUTO,
	
	
	NUM_COLORPATTERNS,
};

/************************************************************
************************************************************/
struct COLOR{
private:
	void LimitCheck()
	{
		if(R < 0)			R = 0;
		else if(255 < R)	R = 255;

		if(G < 0)			G = 0;
		else if(255 < G)	G = 255;

		if(B < 0)			B = 0;
		else if(255 < B)	B = 255;
	}
	
public:
	int R;
	int G;
	int B;
	
	bool IsZero()
	{
		if( (R == 0) && (G == 0) && (B == 0) )	return true;
		else									return false;
	}
	
	const COLOR& operator += (const COLOR& b)
	{
		R += b.R;
		G += b.G;
		B += b.B;
		
		LimitCheck();
		
		return *this;
	}
	
	const COLOR& operator = (const COLOR& b)
	{
		R = b.R;
		G = b.G;
		B = b.B;
		
		return *this;
	}
	
	void xRatio(double Ratio)
	{
		R = int(R * Ratio);
		G = int(G * Ratio);
		B = int(B * Ratio);
		
		LimitCheck();
	}
	
	void Minus(int val)
	{
		R -= val;
		G -= val;
		B -= val;
		
		LimitCheck();
	}
	
	void Reset()
	{
		R = 0; G = 0; B = 0;
	}
};

struct COLOR_AND_WEIGHT{
	COLOR LedColor;
	int Weight;
};

struct PALETTE{
	int interval_ms;
	
	COLOR_AND_WEIGHT LedBase[MAX_COLOR_SETS];
	COLOR_AND_WEIGHT LedFlash[MAX_COLOR_SETS];
};

struct ANGLE{
	int Pan;
	int Tilt;
	
	void Reset()
	{
		Pan = -1;
		Tilt = -1;
	}
};

struct DEVICE_OUTPUT_CH{
	COLOR Lum;
	ANGLE Angle;
	
	void Reset()
	{
		Lum.Reset();
		Angle.Reset();
	}
};



