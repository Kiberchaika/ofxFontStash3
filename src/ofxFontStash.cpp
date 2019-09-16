#include "ofxFontStash.h"

#define FONTSTASH_IMPLEMENTATION
#define GLFONTSTASH_IMPLEMENTATION

extern "C" {
#include "fontstash.h"
#include "offontstash.h"
}

ofxFontStash::ofxFontStash(){
    
}

ofxFontStash::~ofxFontStash(){
	if (fs != NULL) {
		fonsDeleteInternal(fs);
	}

	fs == NULL;
}

void ofxFontStash::load(const filesystem::path & filename, float fontsize) {
#ifndef OF_TARGET_EMSCRIPTEN
	bool bUseArb = ofGetUsingArbTex();
	if (bUseArb) ofDisableArbTex();
#endif

	fs = glfonsCreate(1024, 1024, FONS_ZERO_TOPLEFT);
	if (fs == NULL) {
		printf("Could not create stash.\n");
		return;
	}

	font = fonsAddFont(fs, "font", ofToDataPath(filename).c_str());
	if (font == FONS_INVALID) {
		printf("Could not add font normal.\n");
		return;
	}

	fonsClearState(fs);
	fonsSetFont(fs, font);
	fonsSetSize(fs, 1.6 * fontsize);
	fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE);
	
	//fonsSetColor(fs, white);
	//fonsSetSpacing(fs, 5.0f);
	//fonsSetBlur(fs, 10.0f);

#ifndef OF_TARGET_EMSCRIPTEN
	if (bUseArb) ofEnableArbTex();
#endif
}

float ofxFontStash::getLineHeight() {
	float lh = 0;
	if (font != FONS_INVALID) {
		fonsVertMetrics(fs, NULL, NULL, &lh);
	}
	return lh;
}

 float ofxFontStash::stringWidth(const std::string & s) {
	if (font != FONS_INVALID) {
		return fonsTextBounds(fs, 0, 0, s.c_str(), NULL, NULL);
	}
	return 0;
}

 float ofxFontStash::stringHeight(const std::string & s) {
	 float bounds[4] = { 0, 0, 0, 0 };
	 if (font != FONS_INVALID) {
		 fonsTextBounds(fs, 0, 0, s.c_str(), NULL, bounds);
	 }
	 return bounds[3] - bounds[1]; // maxy - miny
 }

 ofRectangle ofxFontStash::getStringBoundingBox(const string & s, float x, float y) {
	 float bounds[4] = { 0, 0, 0, 0 };
	 if (font != FONS_INVALID) {
		 fonsTextBounds(fs, x, y, s.c_str(), NULL, bounds);
	 }
	 return ofRectangle(bounds[0], bounds[1], bounds[2], bounds[3]);
 }
 

void ofxFontStash::drawString(const string & s, float x, float y) {
	if (font != FONS_INVALID) {
		fonsDrawText(fs, x, y, s.c_str(), NULL);
	}
}

