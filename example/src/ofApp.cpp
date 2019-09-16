#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofDisableArbTex();
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(22, 22, 22, 255);

	fontNormal.setup("Vera.ttf", 24);
	fontItalic.setup("VeraMono-Bold.ttf", 48);
	fontBold.setup("VeraMono-Bold.ttf", 48);
	fontJapanese.setup("Arial Unicode.ttf", 48);


}

void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofPushStyle();
	
	float dx = 10, dy = 10;

	dy += fontNormal.getFontHeight();
	fontNormal.drawString("The quick ", dx, dy);

	dy += fontJapanese.getFontHeight();
	fontJapanese.drawString("Ég get etið gler án þess að meiða mig.", dx, dy);

	ofSetColor(ofColor::red);
	dy += fontJapanese.getFontHeight();
	fontJapanese.drawString("私はガラスを食べられます。それは私を傷つけません。", dx, dy);

	ofPopStyle();
}


void ofApp::drawPoint(float x, float y) {
	ofSetColor(0, 255, 0, 128);
	ofCircle(x, y, 2);
}


void ofApp::keyPressed(int k) {
}
