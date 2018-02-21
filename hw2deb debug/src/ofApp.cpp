#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    vidGrabber.setup(320,240);
	
		
    myColorImg.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myGrayImage.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myBackground.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myGrayDiff.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());

	bLearnBackground = true;
	threshold = 80;
	ofSetBackgroundAuto(false);
    
        //set up rain
    
    
    for (int i=0; i<70; i++){
        
        Rain tempRain;							// create the rain object
        tempRain.setup(ofRandom(0,ofGetWidth()),0, ofRandom(10,40));	// setup its initial state
        rainDrops.push_back(tempRain);				// add it to the vector
    }

//  
//        for(int i=0; i<NRAIN; i++){
//            int size = (i+1) * 10; // defining the size of each ball based on its place in the array
//            int randomX = ofRandom( 0, ofGetWidth() ); //generate a random value bigger than 0 and smaller than our application screen width
//            int randomY = ofRandom( 0, ofGetHeight() ); //generate a random value bigger than 0 and smaller than our application screen height
//    
//            rainDrops[i].setup(randomX, 0, 100);
//        }

}

//--------------------------------------------------------------
void ofApp::update(){
	//ofBackground(100,100,100);

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
		contourFinder.findContours(myGrayDiff, 20, (340*240)/3, 10, false);
    }

    
    //update some rain
    
    for (int i = 0; i<rainDrops.size(); i++) {
        rainDrops[i].update();
    }

//    
//   for(int i=0; i<NRAIN; i++){
//             rainDrops[i].update();
//      }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
	
	// draw the incoming video image
	ofSetHexColor(0xffffff);
    
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2 - myColorImg.getWidth()/2,ofGetHeight()/2 - myColorImg.getHeight()/2);
        if(bShowVideo){
            //myColorImg.draw(0,0);
            myGrayDiff.draw(0,0);
        }
    
// original example code - I did not see much of a difference between using boundingRect or centroids
//      for (int i = 0; i < contourFinder.nBlobs; i++){
//		ofSetColor(ofColor::fuchsia);
//		ofFill();
//		ofDrawEllipse(contourFinder.blobs[i].boundingRect.getCenter(), 20,20);
        //ofDrawEllipse(contourFinder.blobs[i].centroid, 20,20);
//}
    
    //shorthand blob code...guess we don't need this if we're doing pixel brightness
//    for(auto &blob : contourFinder.blobs){
//        ofSetColor(ofColor::violet);
//        ofFill();
//        ofDrawEllipse(blob.centroid, 20,20);
//    
    
    //loop for rain with vectors
    for (int i = 0; i<rainDrops.size(); i++) {
        pix = myGrayDiff.getPixels();
        
        pixBrightness = pix.getColor(locx,locy).getBrightness();

        
        rainDrops[i].draw();
        
    }
    
    
    

//    //draw some rain using NRAIN
//    for(int i=0; i<NRAIN; i++){
//        rainDrops[i].draw();
//        
//        
//        //from Shuai... trying to combine
//        float locX = letterPosX + ( i * letterXSpace);
//        float locY = letterPosY[i];
//        
//        ofDrawBitmapString(letters[i], letterPosX,letterPosY[i]);
//        
//        letterPosX += letterXSpace;
//        
//        float pixBrightness = pix.getColor(locX,locY).getBrightness();
//        
//        
//        if(letterPosY[i] >= ofGetHeight() - 1)
//        {
//            letterPosY[i] = 0;
//        } else if(pixBrightness < threshold)
//        {
//            if(letterPosY[i] > 10)
//            {
//                letterPosY[i]-=letterSpeed;
//            }
//        }
//        else
//        {
//            letterPosY[i]+=letterSpeed;
//        }//end shuai's code
//    }


  
	ofPopMatrix();

	
//	ofDrawBitmapString("Press 'v' to toggle video and path drawing", ofGetWidth()/2.0, ofGetHeight()-100.0);
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
