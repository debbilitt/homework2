#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    vidGrabber.setup(320,240); //set up video
	
    
    myColorImg.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myGrayImage.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myBackground.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myGrayDiff.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());

    
	bLearnBackground = true;
	threshold = 30;
	ofSetBackgroundAuto(false);
    
    
    //define posX and posY and velocity of circle
    
    posX = 100;
    posY = 0;
    
    velocity = 5;
    
    


}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(100,100,100);

    bool bNewFrame = false;


	vidGrabber.update();
	bNewFrame = vidGrabber.isFrameNew();

	if (bNewFrame){


		myColorImg.setFromPixels(vidGrabber.getPixels());

        myGrayImage = myColorImg;
            if (bLearnBackground == true){
                myBackground = myGrayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
                bLearnBackground = false;
            }

		// take the abs value of the difference between background and incoming and then threshold:
		myGrayDiff.absDiff(myBackground, myGrayImage);
		myGrayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(myGrayDiff, 20, (340*240)/3, 1, false);
    }
    
    //set posY to increase with velocity
    posY += velocity;
    
    //returns ball to top if it goes off screen
    
    if(posY > ofGetHeight()) {
        posX = 100;
        posY = 0;
    }
    
    // setting variable to myGrayDiff pixels
    pix = myGrayDiff.getPixels();
    
    //if the posX and posY position are over a pixel that is dark, stop movement
    
    if(pix.getColor(posX,posY).getBrightness() > threshold ) {
     velocity = 0;
    } else {
     
    velocity = 3; //else keep moving
    
    }


}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// draw the incoming video image
	ofSetHexColor(0xffffff);
    
	ofPushMatrix();
//	ofTranslate(ofGetWidth()/2 - myColorImg.getWidth()/2,ofGetHeight()/2 - myColorImg.getHeight()/2);
	if(bShowVideo){
		myGrayDiff.draw(0,0);
        myColorImg.draw(myGrayDiff.getWidth(),0);
	}


    
    ofSetColor(ofColor::lightSeaGreen);
    ofFill();
    ofDrawCircle(posX, posY, 10);
    ofDrawCircle(posX+myGrayDiff.getWidth(), posY, 10);

        
        
    ofPopMatrix();

    
    ofDrawBitmapString("Press + and - to adjust Threshold", ofGetWidth()/2.0, ofGetHeight()-100.0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key){
		case 'v':
			ofBackground(ofColor::white);
			bShowVideo = !bShowVideo;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
