#pragma once

#include "ofxiOS.h"
#include "ofxFontStash.h"


class ofApp : public ofxiOSApp {
    ofxFontStash fontNormal;
    ofxFontStash fontItalic;
    ofxFontStash fontBold;
    ofxFontStash fontJapanese;

    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);

};


