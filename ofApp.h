/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sj_common.h"
#include <ofxVboSet.h>

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		WINDOW_W = 900,
		WINDOW_H = 900,
	};
	enum{
		NUM_FBOS = 9,
	};
	
	enum STATE{
		STATE__FREE_CURSOR,
		STATE__FIXED_CURSOR,
	};
	
	/****************************************
	****************************************/
	STATE State = STATE__FREE_CURSOR;
	glm::vec2 pos_FixedCursor = glm::vec2(0, 0);
	
	int t_LastUpdate_Screen = 0;
	ofImage img_Screen;
	
	ofImage img_Frame;
	ofImage img_Square_Green;
	ofImage img_Square_Red;
	ofImage img_text_of_StarWars;
	ofImage img_Cursor;
	
	string str_StarWars;
	
	int fbo_id = 0;
	ofFbo fbo_out[NUM_FBOS];
	ofTrueTypeFont font_S;
	ofTrueTypeFont font_M;
	ofTrueTypeFont font_Hiragino_M;
	
	ofx__VBO_SET VboSet_Quads_R;
	ofx__VBO_SET VboSet_Quads_G;
	ofx__VBO_SET VboSet_Lines_R;
	ofx__VBO_SET VboSet_Lines_G;
	ofFbo fbo_CheckForced;
	
	ofSpherePrimitive sphere_R;
	ofSpherePrimitive sphere_G;
	ofLight light;
	
	/****************************************
	****************************************/
	void setup_Gui();
	void RefreshVboVerts_ForcedCheck();
	void grab_and_save_screen(string _FileName);
	void SetupMode__fbo_of_CheckForced();
	void SetupMode__Contents();
	void SetupMode__fbo();
	void drawContents_according_to_id();
	void draw_Contents_0();
	void draw_Contents_1();
	void draw_Contents_2();
	void draw_Contents_3();
	void draw_Contents_4();
	void draw_CheckForced__Circle();
	void draw_CheckForced__Rectangle();
	void draw_CheckForced__Line();
	void draw_CheckForced__Font();
	void draw_CheckForced__vbo_Quads();
	void draw_CheckForced__vbo_Lines();
	void draw_CheckForced__fbo();
	void draw_CheckForced__img();
	void draw_CheckForced__Sphere();
	void print_color_of_the_cursor();
	void setup_light(glm::vec2 light_pos);
	
public:
	ofApp();
	~ofApp();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
