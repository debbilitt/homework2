#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"

#include "RAIN.h"
#define NRAIN 100


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

    
        ofVideoGrabber 		vidGrabber;
	
        ofxCvColorImage			myColorImg;
        ofPixels                pix;
        ofxCvGrayscaleImage 	myGrayImage;
		ofxCvGrayscaleImage 	myBackground;
		ofxCvGrayscaleImage 	myGrayDiff;

        ofxCvContourFinder 	contourFinder;
    
    //textrain variable
    
//    float letterSpeed = 1;
//    float letterPosX = 0;
//    float letterPosY [NRAIN] = {};
//    float letterXSpace;
//    float threshold = 80.0;
//    char letters [NRAIN] = {};
//    
//  
    
        float pixBrightness;
    
		int 				threshold;
		bool				bLearnBackground;
		bool				bShowVideo = true;
    
    
    //Rain rainDrops[NRAIN];
    
     Rain rainDrops[];
    
       // vector <Rain> rainDrops;
    

    


};

