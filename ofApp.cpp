/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(){
	/********************
	********************/
	str_StarWars =	string("It is a dark time for the Rebellion. Although the \n") + 
					string("Death Star has been destroyed, Imperial troops have\n") + 
					string("driven the Rebel forces from their hidden base and \n") + 
					string("pursued them across the galaxy.Evading the dreaded\n") + 
					string("Imperial Starfleet, a group of freedom fighters led\n") + 
					string("by Luke Skywalker has established a new secret base\n") + 
					string("on the remote ice world of Hoth.The evil lord Darth\n") + 
					string("Vader, obsessed with finding young Skywalker, has \n") + 
					string("dispatched thousands of remote probes into the far\n") + 
					string("reaches of space…");
					
	/********************
	********************/
	font_S.load("font/RictyDiminished-Regular.ttf", 14, true, true, false, 0.3, 72);
	font_S.setLineHeight(25);
	
	font_M.load("font/ヒラギノ角ゴシック W8.ttc", 32, true, true, false, 0.3, 72);
	
	font_Hiragino_M.load("font/ヒラギノ角ゴシック W8.ttc", 150, true, true, false, 0.3, 72);
}

/******************************
******************************/
ofApp::~ofApp(){
}

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	setup_Gui();
	
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("fbo_test");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(WINDOW_W, WINDOW_H);
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	img_Frame.load("img/img_Frame.png");
	img_Square_Green.load("img/img_Square_Green.png");
	img_Square_Red.load("img/img_Square_Red.png");
	img_text_of_StarWars.load("img/img_text_of_StarWars.png");
	
	img_Cursor.load("img/img_Cursor.png");
	img_Cursor.setAnchorPercent(0.5, 0.5);
	
	
	printf("ofFbo::maxSamples = %d\n", ofFbo::maxSamples());
	fflush(stdout);
	for(int i = 0; i < NUM_FBOS; i++){
		fbo_out[i].allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, i);
	}
	
	fbo_CheckForced.allocate(200, 200, GL_RGBA, 4);
	
	ofSetCircleResolution(100);
	
	/********************
	********************/
	VboSet_Quads_R.setup(4);
	VboSet_Quads_G.setup(4);
	VboSet_Lines_R.setup(2);
	VboSet_Lines_G.setup(2);
	
	// color
	VboSet_Quads_R.set_singleColor(ofColor(255, 0, 0, 128));
	VboSet_Quads_G.set_singleColor(ofColor(0, 255, 0, 128));
	VboSet_Lines_R.set_singleColor(ofColor(255, 0, 0, 128));
	VboSet_Lines_G.set_singleColor(ofColor(0, 255, 0, 128));
	
	// verts
	RefreshVboVerts_ForcedCheck();
	
	/********************
	********************/
	img_Screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
}

/******************************
description
	memoryを確保は、app start後にしないと、
	segmentation faultになってしまった。
******************************/
void ofApp::setup_Gui()
{
	/********************
	********************/
	Gui_Global = new GUI_GLOBAL;
	Gui_Global->setup("param", "gui.xml", 10, 10);
}

/******************************
******************************/
void ofApp::setup_light(glm::vec2 light_pos)
{
	// light.enable();
	light.setPointLight();
	light.setPosition(light_pos.x, light_pos.y, Gui_Global->Light_Distance);
	
	float val = Gui_Global->Light__Strength_Ambient;
	light.setAmbientColor(ofFloatColor(val, val, val, 1.0));
	
	val = Gui_Global->Light__Strength_Diffuse;
	light.setDiffuseColor(ofFloatColor(val, val, val, 1.0));
	
	light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
}

/******************************
******************************/
void ofApp::grab_and_save_screen(string _FileName)
{
	img_Screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	
	img_Screen.save(_FileName);
	
	printf("> saved img = ");
	printf("%s\n", _FileName.c_str());
	fflush(stdout);
}

/******************************
******************************/
void ofApp::RefreshVboVerts_ForcedCheck(){
	/********************
	********************/
	VboSet_Quads_R.set_vboVerts(0, 241, 359, Gui_Global->Draw3D__b_ReverseOrder ? 0 : -1);
	VboSet_Quads_R.set_vboVerts(1, 241, 269, Gui_Global->Draw3D__b_ReverseOrder ? 0 : -1);
	VboSet_Quads_R.set_vboVerts(2, 331, 269, Gui_Global->Draw3D__b_ReverseOrder ? 0 : -1);
	VboSet_Quads_R.set_vboVerts(3, 331, 359, Gui_Global->Draw3D__b_ReverseOrder ? 0 : -1);
	
	VboSet_Quads_G.set_vboVerts(0, 269, 331, Gui_Global->Draw3D__b_ReverseOrder ? -1 : 0);
	VboSet_Quads_G.set_vboVerts(1, 269, 241, Gui_Global->Draw3D__b_ReverseOrder ? -1 : 0);
	VboSet_Quads_G.set_vboVerts(2, 359, 241, Gui_Global->Draw3D__b_ReverseOrder ? -1 : 0);
	VboSet_Quads_G.set_vboVerts(3, 359, 331, Gui_Global->Draw3D__b_ReverseOrder ? -1 : 0);
	
	VboSet_Lines_R.set_vboVerts(0, 440, 240, Gui_Global->Draw3D__b_ReverseOrder ? 0 : -1);
	VboSet_Lines_R.set_vboVerts(1, 560, 360, Gui_Global->Draw3D__b_ReverseOrder ? 0 : -1);
	
	VboSet_Lines_G.set_vboVerts(0, 440, 360, Gui_Global->Draw3D__b_ReverseOrder ? -1 : 0);
	VboSet_Lines_G.set_vboVerts(1, 560, 240, Gui_Global->Draw3D__b_ReverseOrder ? -1 : 0);
	
	/********************
	********************/
	VboSet_Quads_R.update_vertex_color();
	VboSet_Quads_G.update_vertex_color();
	VboSet_Lines_R.update_vertex_color();
	VboSet_Lines_G.update_vertex_color();
}

/******************************
******************************/
void ofApp::update(){
	/********************
	********************/
	fbo_id = int(Gui_Global->DrawFbo__id_of_fbo);
	if(NUM_FBOS <= fbo_id) fbo_id = 0;
	
	/********************
	********************/
	fbo_out[fbo_id].begin();
		ofBackground(Gui_Global->DrawFbo__ClearColor);
		drawContents_according_to_id();
	fbo_out[fbo_id].end();
}

/******************************
******************************/
void ofApp::draw(){
	/********************
	********************/
	int now = ofGetElapsedTimeMillis();
	
	/********************
	********************/
	ofDisableLighting();
	
	ofBackground(Gui_Global->Screen__ClearColor);
	
	if(Gui_Global->DrawFbo__b_UseFbo){
		SetupMode__fbo();
		
		ofSetColor(255, 255, 255, 255);
		fbo_out[fbo_id].draw(0, 0, ofGetWidth(), ofGetHeight());
		
	}else{
		drawContents_according_to_id();
	}
	
	/********************
	********************/
	if(30 < now - t_LastUpdate_Screen){
		t_LastUpdate_Screen = now;
		img_Screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	/********************
	********************/
	print_color_of_the_cursor();
	
	/********************
	********************/
	ofDisableDepthTest();
	if(Gui_Global->b_Disp){
		Gui_Global->gui.draw();
	}
}

/******************************
******************************/
void ofApp::print_color_of_the_cursor(){
	/********************
	********************/
	ofColor col;
	
	int _x = mouseX;
	int _y = mouseY;
	
	/********************
	********************/
	if(State == STATE__FIXED_CURSOR){
		_x = pos_FixedCursor.x;
		_y = pos_FixedCursor.y;
		
		ofDisableSmoothing();
		ofFill();
		ofDisableDepthTest();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		
		ofSetColor(255, 255, 255, 200);
		img_Cursor.draw(_x, _y);
	}
	
	/********************
	********************/
	if(_x < 0)					_x = 0;
	if(ofGetWidth() - 1 < _x)	_x = ofGetWidth() - 1;
	
	if(_y < 0)					_y = 0;
	if(ofGetHeight() - 1 < _y)	_y = ofGetHeight() - 1;
	
	col = img_Screen.getPixels().getColor(_x, _y);
	
	printf("(%3d, %3d, %3d, %3d)\r", col.r, col.g, col.b, col.a);
	fflush(stdout);
}

/******************************
******************************/
void ofApp::drawContents_according_to_id(){
	switch( int(Gui_Global->DrawContents_id) ){
		case 0:
			draw_Contents_0();
			break;
		case 1:
			draw_Contents_1();
			break;
		case 2:
			draw_Contents_2();
			break;
		case 3:
			draw_Contents_3();
			break;
		case 4:
			draw_Contents_4();
			break;
		default:
			break;
	}
}

/******************************
******************************/
void ofApp::SetupMode__Contents(){
	if(Gui_Global->DrawContents__b_Smoothing)					ofEnableSmoothing();
	else														ofDisableSmoothing();
	
	if(Gui_Global->DrawContents__b_AntiAliasing)				ofEnableAntiAliasing();
	else														ofDisableAntiAliasing();
	
	if(Gui_Global->DrawContents__b_Fill)						ofFill();
	else														ofNoFill();
	
	if(Gui_Global->DrawContents__b_DepthTest)					ofEnableDepthTest();
	else														ofDisableDepthTest();
	
	if( int(Gui_Global->DrawContents__BlendMode) == 0 )			ofEnableBlendMode(OF_BLENDMODE_DISABLED);
	else if( int(Gui_Global->DrawContents__BlendMode) == 1 )	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	else if( int(Gui_Global->DrawContents__BlendMode) == 2 )	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	if(Gui_Global->Light_Enable)								{ light.enable(); }
	else														{ light.disable(); ofDisableLighting(); } // 個別off + light system全体のoff
}

/******************************
******************************/
void ofApp::SetupMode__fbo_of_CheckForced(){
	ofEnableAntiAliasing();
	ofNoFill();
	ofDisableDepthTest();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}

/******************************
******************************/
void ofApp::SetupMode__fbo(){
	if(Gui_Global->DrawFbo__b_Smoothing)				ofEnableSmoothing();
	else												ofDisableSmoothing();
	
	if(Gui_Global->DrawFbo__b_AntiAliasing)				ofEnableAntiAliasing();
	else												ofDisableAntiAliasing();
	
	if(Gui_Global->DrawFbo__b_Fill)						ofFill();
	else												ofNoFill();
	
	if(Gui_Global->DrawFbo__b_DepthTest)				ofEnableDepthTest();
	else												ofDisableDepthTest();
	
	if( int(Gui_Global->DrawFbo__BlendMode) == 0 )		ofEnableBlendMode(OF_BLENDMODE_DISABLED);
	else if( int(Gui_Global->DrawFbo__BlendMode) == 1 )	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	else if( int(Gui_Global->DrawFbo__BlendMode) == 2 )	ofEnableBlendMode(OF_BLENDMODE_ADD);
}
/******************************
******************************/
void ofApp::draw_Contents_0(){
	/********************
	********************/
	SetupMode__Contents();
	
	/********************
	********************/
	ofSetColor(255, 0, 0, 128);
	ofDrawCircle(glm::vec2(206, 300), 150);
	
	ofSetColor(0, 255, 0, 128);
	ofDrawCircle(glm::vec2(394, 300), 150);
}

/******************************
******************************/
void ofApp::draw_Contents_1(){
	/********************
	********************/
	SetupMode__Contents();
	
	/********************
	********************/
	ofSetColor(255, 0, 0, 128);
	ofDrawCircle(glm::vec2(300, 300), 200);
}

/******************************
******************************/
void ofApp::draw_Contents_2(){
	/********************
	********************/
	SetupMode__Contents();
	
	/********************
	********************/
	// ofSetLineWidth(Gui_Global->DrawContents__LineWidth);
	ofSetLineWidth(4);
	
	ofSetColor(Gui_Global->DrawContents__color);
	ofDrawLine(glm::vec2(386, 444), glm::vec2(586, 444));
	ofDrawLine(glm::vec2(392, 410), glm::vec2(580, 478));
	ofDrawLine(glm::vec2(409, 380), glm::vec2(563, 509));
	ofDrawLine(glm::vec2(436, 358), glm::vec2(536, 531));
	ofDrawLine(glm::vec2(469, 346), glm::vec2(503, 543));
	ofDrawLine(glm::vec2(503, 346), glm::vec2(469, 543));
	ofDrawLine(glm::vec2(536, 358), glm::vec2(436, 531));
	ofDrawLine(glm::vec2(563, 380), glm::vec2(409, 509));
	ofDrawLine(glm::vec2(580, 410), glm::vec2(392, 478));
	
	font_S.drawString(str_StarWars, 16, 338);
	
	/********************
	********************/
	ofSetColor(Gui_Global->DrawContents__color);
	img_text_of_StarWars.draw(0, 0);
}

/******************************
******************************/
void ofApp::draw_Contents_3(){
	/********************
	********************/
	RefreshVboVerts_ForcedCheck();
	
	/********************
	********************/
	fbo_CheckForced.begin();
		ofBackground(0, 0, 0, 255);
		SetupMode__fbo_of_CheckForced();
		draw_CheckForced__Circle();
	fbo_CheckForced.end();
	
	/********************
	********************/
	SetupMode__Contents();
	
	/********************
	********************/
	draw_CheckForced__Circle();
	draw_CheckForced__Rectangle();
	draw_CheckForced__Line();
	draw_CheckForced__Font();
	draw_CheckForced__vbo_Quads();
	draw_CheckForced__vbo_Lines();
	draw_CheckForced__fbo();
	draw_CheckForced__img();
	draw_CheckForced__Sphere();
	
	/********************
	********************/
	ofDisableSmoothing();
	ofDisableAntiAliasing();
	ofNoFill();
	ofDisableDepthTest();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofDisableLighting();
	
	ofSetColor(255, 255, 255, 255);
	img_Frame.draw(0, 0);
}

/******************************
******************************/
void ofApp::draw_CheckForced__Circle(){
	setup_light(glm::vec2(100, 100));
	
	ofSetLineWidth(Gui_Global->DrawContents__LineWidth);
	
	ofSetColor(255, 0, 0, 128);
	ofDrawCircle(glm::vec3(75, 100, Gui_Global->Draw3D__b_ReverseOrder ? 0 : -1), 50);
	
	ofSetColor(0, 255, 0, 128);
	ofDrawCircle(glm::vec3(125, 100, Gui_Global->Draw3D__b_ReverseOrder ? -1 : 0), 50);
}

/******************************
******************************/
void ofApp::draw_CheckForced__Rectangle(){
	setup_light(glm::vec2(300, 100));
	
	ofSetLineWidth(Gui_Global->DrawContents__LineWidth);
	
	ofSetColor(255, 0, 0, 128);
	ofDrawRectangle(glm::vec3(241, 69, Gui_Global->Draw3D__b_ReverseOrder ? 0 : -1), 90, 90);
	
	ofSetColor(0, 255, 0, 128);
	ofDrawRectangle(glm::vec3(269, 41, Gui_Global->Draw3D__b_ReverseOrder ? -1 : 0), 90, 90);
}

/******************************
******************************/
void ofApp::draw_CheckForced__Line(){
	setup_light(glm::vec2(500, 100));
	
	ofSetLineWidth(Gui_Global->DrawContents__LineWidth);
	
	ofSetColor(255, 0, 0, 128);
	ofDrawLine(glm::vec3(440, 40, Gui_Global->Draw3D__b_ReverseOrder ? 0 : -1), glm::vec3(560, 160, Gui_Global->Draw3D__b_ReverseOrder ? 0 : -1));
	
	ofSetColor(0, 255, 0, 128);
	ofDrawLine(glm::vec3(440, 160, Gui_Global->Draw3D__b_ReverseOrder ? -1 : 0), glm::vec3(560, 40, Gui_Global->Draw3D__b_ReverseOrder ? -1 : 0));
}

/******************************
******************************/
void ofApp::draw_CheckForced__Font(){
	setup_light(glm::vec2(100, 300));
	
	ofSetColor(255, 0, 0, 128);
	font_Hiragino_M.drawString("A", 34, 370);
	
	ofSetColor(0, 255, 0, 128);
	font_Hiragino_M.drawString("A", 46, 360);
}

/******************************
******************************/
void ofApp::draw_CheckForced__vbo_Quads(){
	setup_light(glm::vec2(300, 300));
	
	glLineWidth(Gui_Global->DrawContents__LineWidth);
	
	ofSetColor(255, 255, 255, 255);
	VboSet_Quads_R.draw(GL_QUADS);
	VboSet_Quads_G.draw(GL_QUADS);
}

/******************************
******************************/
void ofApp::draw_CheckForced__vbo_Lines(){
	setup_light(glm::vec2(500, 300));
	
	glLineWidth(Gui_Global->DrawContents__LineWidth);
	
	ofSetColor(255, 255, 255, 255);
	VboSet_Lines_R.draw(GL_LINES);
	VboSet_Lines_G.draw(GL_LINES);
}

/******************************
******************************/
void ofApp::draw_CheckForced__fbo(){
	setup_light(glm::vec2(100, 500));
	
	ofSetColor(255, 255, 255, 255);
	fbo_CheckForced.draw(0, 400);
}

/******************************
******************************/
void ofApp::draw_CheckForced__img(){
	setup_light(glm::vec2(300, 500));
	
	ofSetColor(255, 255, 255, 255);
	img_Square_Red.draw(200, 400, Gui_Global->Draw3D__b_ReverseOrder ? 0 : -1);
	img_Square_Green.draw(200, 400, Gui_Global->Draw3D__b_ReverseOrder ? -1 : 0);
}

/******************************
https://www.slideshare.net/tado/media-art-ii-2013
******************************/
void ofApp::draw_CheckForced__Sphere(){
	/********************
	********************/
	setup_light(glm::vec2(500, 500));
	
	ofSetLineWidth(Gui_Global->Draw3D__LineWidth);
	
	/********************
	********************/
	sphere_R.set(50, Gui_Global->Draw3D__Resolution); // r, 面の細かさ
	sphere_G.set(50, Gui_Global->Draw3D__Resolution); // r, 面の細かさ
	
	if(Gui_Global->Draw3D__b_ReverseOrder){
		sphere_R.setPosition(475, 500, 0);
		sphere_G.setPosition(525, 500, -30);
	}else{
		sphere_R.setPosition(475, 500, -30);
		sphere_G.setPosition(525, 500, 0);
	}
	
	/********************
	********************/
	if(Gui_Global->Draw3D_WireFrame){
		ofSetColor(255, 0, 0, 128);
		sphere_R.drawWireframe();
		
		ofSetColor(0, 255, 0, 128);
		sphere_G.drawWireframe();
	}else{
		ofSetColor(255, 0, 0, 128);
		sphere_R.draw();
		
		ofSetColor(0, 255, 0, 128);
		sphere_G.draw();
	}
}

/******************************
******************************/
void ofApp::draw_Contents_4(){
	draw_Contents_2();
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case 'p':
			grab_and_save_screen("screenshot.png");
			break;
			
		case 'j':
			grab_and_save_screen("screenshot.jpg");
			break;
			
		case 'd':
			Gui_Global->b_Disp = !Gui_Global->b_Disp;
			break;
			
		case 'm':
			Gui_Global->gui.minimizeAll();
			break;
			
		case OF_KEY_RIGHT:
			if(State == STATE__FIXED_CURSOR){
				pos_FixedCursor.x ++;
				if(ofGetWidth() - 1 < pos_FixedCursor.x)	pos_FixedCursor.x = ofGetWidth() - 1;
			}
			break;
			
		case OF_KEY_LEFT:
			if(State == STATE__FIXED_CURSOR){
				pos_FixedCursor.x --;
				if(pos_FixedCursor.x < 0)	pos_FixedCursor.x = 0;
			}
			break;
			
		case OF_KEY_UP:
			if(State == STATE__FIXED_CURSOR){
				pos_FixedCursor.y --;
				if(pos_FixedCursor.y < 0)	pos_FixedCursor.y = 0;
			}
			break;
			
		case OF_KEY_DOWN:
			if(State == STATE__FIXED_CURSOR){
				pos_FixedCursor.y ++;
				if(ofGetHeight() - 1 < pos_FixedCursor.y)	pos_FixedCursor.y = ofGetHeight() - 1;
			}
			break;
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){
	switch(State){
		case STATE__FREE_CURSOR:
			State = STATE__FIXED_CURSOR;
			pos_FixedCursor = glm::vec2(x, y);
			break;
			
		case STATE__FIXED_CURSOR:
			State = STATE__FREE_CURSOR;
			break;
	}
}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
