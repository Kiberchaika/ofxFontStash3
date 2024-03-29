#ifndef ofxFontStash_h
#define ofxFontStash_h

#include "ofMain.h"

extern "C" {
#include "fontstash.h"
}

#ifdef MURKA_OF
#include "murkafontstash.h"
#else 
extern "C" {
#include "offontstash.h"
}
#endif

class ofxFontStash {
    int font = FONS_INVALID;
    FONScontext* fs = NULL;
   
	void cleanup();

public:
    
	struct Rectangle {
		float x;
		float y;
		float width;
		float height;
	};
    ofxFontStash();
    ~ofxFontStash();
    
	ofxFontStash& operator=(const ofxFontStash& obj);
	
    void load(const filesystem::path &filename, float fontsize, bool isAbsolutePath = false, void* renderer = nullptr);
    void updateTexture(void* renderer = nullptr);
    void clearTexture();

	float getLineHeight();
	float stringWidth(const std::string& s);
	float stringHeight(const std::string& s);
	Rectangle getStringBoundingBox(const string &s, float x, float y);

	// custom function
	vector<Rectangle> getStringSymbolsBoundingBoxes(const string &s, float x, float y, bool needJoin = false);

	void drawString(const string &s, float x, float y);

	/// static C error handler
	static void stashError(void* uptr, int error, int val);
};

#endif

