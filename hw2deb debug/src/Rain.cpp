#include "Rain.h"

Rain::Rain(){
};

void Rain::setup(float _x, float _y, char _letter){
    x = _x;
    y = _y;
    letter = _letter;
    
    velocity = ofRandom(1,3);

    color.set(ofRandom(255), ofRandom(255), ofRandom(255));
    
    letter = generateString();

}

void Rain::update(){

    
    if(y >= ofGetHeight()) {  //reset if letter at the bottom
        x = ofRandom(0, ofGetWidth());  //give random x position
        y = 0;
        
    } else {
        if(pix.getColor(x,y).getBrightness()(x+y*ofGetWidth())) < threshold ) {  //if letter position is dark, stop letter
            
            //push letter up to follow the "edge"
            if( y > 0 && y != 0) {  //only push up if y pos is not at 0
                float _newY = y;  //temp y
                
                for( int i = int(y); i > 0; i-- ) {  //look at every single pixel above letter
                    if(pix.Brightness(x+i*ofGetWidth())) > threshold ) {  //if it is bright
                        _newY = i;  //make that new y position
//                        break;  //stop looking for next pixel
                    }
                }
                y = _newY;  //update y position
            }
        } else {  //move letter down
           y += 1;
            
        } 
    }

    
}

char Rain::generateString(){
    char string[4] = {'R','A','I','N'};
    char currentChar = string[rand() % 4];
    return currentChar;
}


void Rain::draw(){
    ofSetColor(color);
   // ofDrawCircle(x, y, dim);
    
    ofDrawBitmapString(letter, x, y);
}
