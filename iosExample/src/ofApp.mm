#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
//    ofDisableArbTex();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(22, 22, 22, 255);
    
    fontNormal.load("Vera.ttf", 24);
    fontItalic.load("VeraMono-Bold.ttf", 48);
    fontBold.load("VeraMono-Bold.ttf", 48);
    fontJapanese.load("Arial Unicode.ttf", 48);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
    ofPushStyle();
    
    float dx = 10, dy = 10;
    
    dy += fontNormal.getLineHeight();
    fontNormal.drawString("The quick ", dx, dy);
    
    dy += fontJapanese.getLineHeight();
    fontJapanese.drawString("Ég get etið gler án þess að meiða mig.", dx, dy);
    
    ofSetColor(ofColor::red);
    dy += fontJapanese.getLineHeight();
    fontJapanese.drawString("私はガラスを食べられます。それは私を傷つけません。", dx, dy);
    
    ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){

}

//--------------------------------------------------------------
void ofApp::gotFocus(){

}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){

}
