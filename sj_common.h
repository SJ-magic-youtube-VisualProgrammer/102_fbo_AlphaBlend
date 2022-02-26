/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include <stdio.h>

#include <ofMain.h>
#include <ofxGui.h>

/************************************************************
************************************************************/
#define ERROR_MSG(); printf("Error in %s:%d\n", __FILE__, __LINE__);

/************************************************************
************************************************************/
enum{
	BUF_SIZE_S = 500,
	BUF_SIZE_M = 1000,
	BUF_SIZE_L = 6000,
	BUF_SIZE_LL = 100000,
	UDP_BUF_SIZE = 100000,
};

enum{
	AUDIO_BUF_SIZE = 512,
	
	AUDIO_OUT_CHS = 2,
	AUDIO_IN_CHS = 2,
	AUDIO_BUFFERS = 2,			// 使われてないっぽい
	AUDIO_SAMPLERATE = 44100,
};

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class GUI_GLOBAL{
private:
	/****************************************
	****************************************/
	
public:
	/****************************************
	****************************************/
	void setup(string GuiName, string FileName = "gui.xml", float x = 10, float y = 10);
	
	ofxGuiGroup Group_Screen;
		ofxColorSlider Screen__ClearColor;
		
	ofxGuiGroup Group_DrawContents;
		ofxToggle DrawContents__b_Smoothing;
		ofxToggle DrawContents__b_AntiAliasing;
		ofxToggle DrawContents__b_Fill;
		ofxToggle DrawContents__b_DepthTest;
		ofxFloatSlider DrawContents__BlendMode;
		ofxFloatSlider DrawContents__LineWidth;
		ofxColorSlider DrawContents__color;
		
	ofxGuiGroup Group_DrawFbo;
		ofxToggle DrawFbo__b_UseFbo;
		ofxToggle DrawFbo__b_Smoothing;
		ofxToggle DrawFbo__b_AntiAliasing;
		ofxToggle DrawFbo__b_Fill;
		ofxToggle DrawFbo__b_DepthTest;
		ofxFloatSlider DrawFbo__BlendMode;
		ofxFloatSlider DrawFbo__id_of_fbo;
		ofxColorSlider DrawFbo__ClearColor;
		
	ofxGuiGroup Group_Draw3D;
		ofxToggle Draw3D__b_ReverseOrder;
		ofxToggle Draw3D_WireFrame;
		ofxFloatSlider Draw3D__LineWidth;
		ofxFloatSlider Draw3D__Resolution;
		
	ofxGuiGroup Group_Light;
		ofxToggle Light_Enable;
		ofxFloatSlider Light_Distance;
		ofxFloatSlider Light__Strength_Ambient;
		ofxFloatSlider Light__Strength_Diffuse;
		
	ofxGuiGroup Group_misc;
		ofxFloatSlider DrawContents_id;
		
	ofxPanel gui;
	
	bool b_Disp = false;
};

/************************************************************
************************************************************/
double LPF(double LastVal, double CurrentVal, double Alpha_dt, double dt);
double LPF(double LastVal, double CurrentVal, double Alpha);
double sj_max(double a, double b);

bool checkIf_ContentsExist(char* ret, char* buf);
void Align_StringOfData(string& s);
void print_separatoin();
void ClearFbo(ofFbo& fbo);

float toRad(float val);
float toDeg(float val);

/************************************************************
************************************************************/
extern GUI_GLOBAL* Gui_Global;

extern FILE* fp_Log;

extern int GPIO_0;
extern int GPIO_1;


/************************************************************
************************************************************/

