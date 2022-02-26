/************************************************************
************************************************************/
#include "sj_common.h"

/************************************************************
************************************************************/
/********************
********************/
int GPIO_0 = 0;
int GPIO_1 = 0;

/********************
********************/
GUI_GLOBAL* Gui_Global = NULL;

FILE* fp_Log = nullptr;


/************************************************************
func
************************************************************/
/******************************
******************************/
double LPF(double LastVal, double CurrentVal, double Alpha_dt, double dt)
{
	double Alpha;
	if((Alpha_dt <= 0) || (Alpha_dt < dt))	Alpha = 1;
	else									Alpha = 1/Alpha_dt * dt;
	
	return CurrentVal * Alpha + LastVal * (1 - Alpha);
}

/******************************
******************************/
double LPF(double LastVal, double CurrentVal, double Alpha)
{
	if(Alpha < 0)		Alpha = 0;
	else if(1 < Alpha)	Alpha = 1;
	
	return CurrentVal * Alpha + LastVal * (1 - Alpha);
}

/******************************
******************************/
double sj_max(double a, double b)
{
	if(a < b)	return b;
	else		return a;
}

/******************************
******************************/
bool checkIf_ContentsExist(char* ret, char* buf)
{
	if( (ret == NULL) || (buf == NULL)) return false;
	
	string str_Line = buf;
	Align_StringOfData(str_Line);
	vector<string> str_vals = ofSplitString(str_Line, ",");
	if( (str_vals.size() == 0) || (str_vals[0] == "") ){ // no_data or exist text but it's",,,,,,,".
		return false;
	}else{
		return true;
	}
}

/******************************
******************************/
void Align_StringOfData(string& s)
{
	size_t pos;
	while((pos = s.find_first_of(" 　\t\n\r")) != string::npos){ // 半角・全角space, \t 改行 削除
		s.erase(pos, 1);
	}
}

/******************************
******************************/
void print_separatoin()
{
	printf("---------------------------------\n");
}

/******************************
******************************/
void ClearFbo(ofFbo& fbo)
{
	fbo.begin();
		ofClear(0, 0, 0, 0);
	fbo.end();
}

/******************************
******************************/
float toRad(float val){
	return val * 3.1415 / 180.0;
}

/******************************
******************************/
float toDeg(float val){
	return val * 180.0 / 3.1415;
}


/************************************************************
class
************************************************************/

/******************************
******************************/
void GUI_GLOBAL::setup(string GuiName, string FileName, float x, float y)
{
	/********************
	********************/
	gui.setup(GuiName.c_str(), FileName.c_str(), x, y);
	
	/********************
	********************/
	Group_Screen.setup("Screen");
		{
			ofColor initColor = ofColor(0, 0, 0, 255);
			ofColor minColor = ofColor(0, 0, 0, 0);
			ofColor maxColor = ofColor(255, 255, 255, 255);
			Group_Screen.add(Screen__ClearColor.setup("ClearColor", initColor, minColor, maxColor));
		}
	gui.add(&Group_Screen);
	
	Group_DrawContents.setup("DrawContents");
		Group_DrawContents.add(DrawContents__b_Smoothing.setup("Contents:Smoothing", false));
		Group_DrawContents.add(DrawContents__b_AntiAliasing.setup("Contents:AntiAliasing", false));
		Group_DrawContents.add(DrawContents__b_Fill.setup("Contents:Fill", false));
		Group_DrawContents.add(DrawContents__b_DepthTest.setup("Contents:DepthTest", false));
		Group_DrawContents.add(DrawContents__BlendMode.setup("Contents:BlendMode", 1, 0, 2));
		Group_DrawContents.add(DrawContents__LineWidth.setup("Contents:LineWidth", 15, 1, 20));
		{
			ofColor initColor = ofColor(255, 255, 255, 255);
			ofColor minColor = ofColor(0, 0, 0, 0);
			ofColor maxColor = ofColor(255, 255, 255, 255);
			Group_DrawContents.add(DrawContents__color.setup("color", initColor, minColor, maxColor));
		}
	gui.add(&Group_DrawContents);
	
	Group_DrawFbo.setup("DrawFbo");
		Group_DrawFbo.add(DrawFbo__b_UseFbo.setup("DrawFbo:b_use", false));
		Group_DrawFbo.add(DrawFbo__b_Smoothing.setup("DrawFbo:Smoothing", false));
		Group_DrawFbo.add(DrawFbo__b_AntiAliasing.setup("DrawFbo:AntiAliasing", false));
		Group_DrawFbo.add(DrawFbo__b_Fill.setup("DrawFbo:Fill", false));
		Group_DrawFbo.add(DrawFbo__b_DepthTest.setup("DrawFbo:DepthTest", false));
		Group_DrawFbo.add(DrawFbo__BlendMode.setup("DrawFbo:BlendMode", 1, 0, 2));
		Group_DrawFbo.add(DrawFbo__id_of_fbo.setup("DrawFbo:id", 4, 0, 8));
		{
			ofColor initColor = ofColor(0, 0, 0, 0);
			ofColor minColor = ofColor(0, 0, 0, 0);
			ofColor maxColor = ofColor(255, 255, 255, 255);
			Group_DrawFbo.add(DrawFbo__ClearColor.setup("ClearColor", initColor, minColor, maxColor));
		}
	gui.add(&Group_DrawFbo);
	
	Group_Draw3D.setup("Draw3D");
		Group_Draw3D.add(Draw3D__b_ReverseOrder.setup("Draw3D:ReverseOrder", false));
		Group_Draw3D.add(Draw3D_WireFrame.setup("Draw3D:wireframe", false));
		Group_Draw3D.add(Draw3D__LineWidth.setup("Draw3D:LineWidth", 1, 1, 20));
		Group_Draw3D.add(Draw3D__Resolution.setup("Draw3D:Resolution", 32, 4, 64));
	gui.add(&Group_Draw3D);
	
	Group_Light.setup("Light");
		Group_Light.add(Light_Enable.setup("light:enable", false));
		Group_Light.add(Light_Distance.setup("light:Distance", 55, 0, 500));
		Group_Light.add(Light__Strength_Ambient.setup("light:Ambient", 0.4, 0, 1.0));
		Group_Light.add(Light__Strength_Diffuse.setup("light:Diffuse", 0.5, 0, 1.0));
	gui.add(&Group_Light);
	
	Group_misc.setup("misc");
		Group_misc.add(DrawContents_id.setup("DrawContents_id", 0, 0, 4));
	gui.add(&Group_misc);

	/********************
	********************/
	gui.minimizeAll();
}

