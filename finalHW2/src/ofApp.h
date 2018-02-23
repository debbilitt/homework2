#pragma once

// FINAL FILE FOR PROJECT 

#include "ofMain.h"

#include "ofxOpenCv.h"

#define NRAIN 50

class ofApp : public ofBaseApp{

	public:
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
        char generateString();
        void fallingLetters();

    
        ofVideoGrabber 		vidGrabber;
    
    //openCV variables
    
        ofxCvColorImage			myColorImg;
        ofxCvGrayscaleImage 	myGrayImage;
		ofxCvGrayscaleImage 	myBackground;
		ofxCvGrayscaleImage 	myGrayDiff;
        ofxCvContourFinder 	contourFinder;

    
        ofPixels                pix;
 
  
    //color lerp variables
    
    
        ofColor firstColor;
        ofColor secondColor;
        ofColor lerpColor;
        ofColor mappedColor;

    //rain variables
    
    float threshold = 170.0;
    char letters [NRAIN] = {};
    float letterPosY [NRAIN] = {};

    
    bool                bLearnBackground;
    bool                bShowVideo = true;
    

};

