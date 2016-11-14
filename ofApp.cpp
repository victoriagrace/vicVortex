#include "ofApp.h"

//--------------------------------------------------------------
// setup() -- Setup our application
//--------------------------------------------------------------
void ofApp::setup(){
    //-AUDIO----------------------------------------------------
   	int bufferSize		= MY_BUFFERSIZE;
    
    lAudio.assign(MY_BUFFERSIZE, 0.0);
    rAudio.assign(MY_BUFFERSIZE, 0.0);
    
    soundStream.printDeviceList();
    
    
    // Setup the sound stream
    soundStream.setup(this, MY_CHANNELS, MY_CHANNELS, MY_SRATE, MY_BUFFERSIZE, MY_NBUFFERS);
    
    // Resize and initialize left and right buffers...
    left.resize( MY_BUFFERSIZE, 0 );
    right.resize( MY_BUFFERSIZE, 0 );
    faustLeft.resize( MY_BUFFERSIZE, 0 );
    faustRight.resize( MY_BUFFERSIZE, 0 );
    audioBuffer = new float*[2];
    audioBuffer[0] = &faustLeft[0];
    audioBuffer[1] = &faustRight[0];

    // Resize and initialize left and right history buffers...
    leftHistory.resize(  MY_BUFFERHISTORY, left  );
    rightHistory.resize( MY_BUFFERHISTORY, right );
    
    disIntensity=1.0;
    mouse1 = 1.0;
    mouse2 = 1.0;
    mouse3 = 1.0;
    addSub = 1.03;
    fftSwitch = false;
    catMode = false;
    catMode2 = false;
    catMode3 = false;

    speed = 0.0001;
    
    //Faust--------------------------
    effect.init(MY_SRATE); // initializing the Faust module
    effect.buildUserInterface(&effectControl); // linking the Faust module to the controler
    
    for(int i=0; i<effectControl.getParamsCount(); i++){
//        std::cout << effectControl.getParamAdress(i) << "\n";
    }
    
    
    // setting default values for the Faust module parameters
    effectControl.setParamValue("/saw/delayLength",3600);
    

    
    //-VIDEO----------------------------------------------------
    
    // Sync video refresh rate for our computer
    ofSetVerticalSync(true);
    
    // Set background color grayish
    ofBackground(54, 54, 54);
    
    // Tell OpenFrameworks to use smooth edges
    ofEnableSmoothing();
    
    // FFT ------
    fft = ofxFft::create(MY_BUFFERSIZE, OF_FFT_WINDOW_HAMMING);
    
    // Initialize rotation
    rotIncr = 0;

}

//--------------------------------------------------------------
void ofApp::update(){
    // Update audio buffer history with most recent buffer
    leftHistory.push_back( left );
    rightHistory.push_back( right );
    
    // Remove oldest buffers
    leftHistory.erase(  leftHistory.begin(),  leftHistory.begin()+1  );
    rightHistory.erase( rightHistory.begin(), rightHistory.begin()+1 );
    
    // ----- FFT -------------------------------------
//    // Normalize the left channel waveform
    float maxValue = 0;
    for(int i = 0; i < left.size(); i++) {
        if(abs(left[i]) > maxValue) { maxValue = abs(left[i]); }
    }
    for(int i = 0; i < left.size(); i++) { left[i] /= maxValue; }
    
    // Take the FFT of the left channel
    fft->setSignal(&left[0]);
    
    // Get the magnitudes and copy them to audioBins
    float* fftData = fft->getAmplitude();
    
    // Now normalize the FFT magnitude values
    maxValue = 0;
    for(int i = 0; i < fft->getBinSize(); i++) {
        if(abs(fftData[i]) > maxValue) { maxValue = abs(fftData[i]); }
    }
    for(int i = 0; i < fft->getBinSize(); i++) { fftData[i] /= maxValue; }
    
//  std::cout << fft->getBinSize() << "\n";
    // Update the bokeh with its amplitude value (taken from an FFT bin)
   
    for(int i=0; i<N_BINS; i++){
        fade= 255*(i/(float)MY_BUFFERHISTORY);
        //std::cout << fade << "\n";
        
        myCol[i].update(fftData[int( i * fft->getBinSize() / N_BINS )],fade) ;
        
        
    }

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    int wh = ofGetWindowHeight();
    int ww = ofGetWindowWidth();
    
//    float waveform_amp   = 0.5 * wh;
//    float waveform_width = 0.5 * ww;
    
    float waveform_amp   = wh * 0.15;
    float waveform_base   = wh * 0.15;
    
    float waveform_width = ww;
    float pi_inc = (float)(2 * MY_PIE) / MY_BUFFERSIZE;
    float xcorr = 0.0;
    float ycorr = 0.0;
    float total_radius = 0.0;
    float distance = 0.0;
    float disVar = 0.0;
    float disVarInv = 0.0;
    
    // Draw waveform for left channel
    ofPushStyle();
    ofPushMatrix();
    
        ofTranslate(0, wh, 0);
        ofSetLineWidth(1);
        ofNoFill();
    if (catMode3 == true) {

        ofRotateX(rotIncr);
        rotIncr += 0.3;
        rotIncr = fmod(rotIncr, 360);
    }
//
//    ofRotateX(rotIncr);
//    rotIncr += 1.0;
//    rotIncr = fmod(rotIncr, 360);
    
        // Loop over the buffer history. Most recent is last, oldest is first.
        // Thus int j starts from max, and loops to zero
    distance = 1.0;
        for ( int j = MY_BUFFERHISTORY-1; j >= 0; j--){
            
            // Each older buffer is further back by this amount
            //ofTranslate( 0, 0, -30);
            
            // Waveforms have the same color, but their alpha value is less for
            // older buffers
           
            if (fftSwitch == true) {
                myCol[j + 20].setColor(); // start at bin number 20

            }
            else if (fftSwitch == false)
            {
                ofSetColor(255.0/(disIntensity), 255*(j/(float)MY_BUFFERHISTORY), 100*(disIntensity/5), 256*(j/(float)MY_BUFFERHISTORY));
              
                
            }
            if (catMode == true) {
                
                ofRotateX(rotIncr);
                rotIncr += speed;
                rotIncr = fmod(rotIncr, 360);
            }
            
            if (catMode2 == true) {
                
                ofRotateY(rotIncr);
                rotIncr += speed;
                rotIncr = fmod(rotIncr, 360);
            }
           

            // Start the line for this particular waveform
            ofBeginShape();
                // Make a vertex for each sample value
                for (unsigned int i = 0; i < MY_BUFFERSIZE; i++){
                    
                    disVar=(leftHistory[j][i]*disIntensity)+ distance;
                    
                    if (myDis == true) {
                        disVarInv=1.0/disVar;
                    }
                    else{
                        disVarInv=1.0;
 
                    }
                    
//                    disVarInv=1.0/disVar;
                    total_radius = (waveform_base + waveform_amp * leftHistory[j][i]) *(disVar*disVarInv);


    
//                    total_radius = (waveform_base + waveform_amp * leftHistory[j][i]) *(disVar);
                    xcorr = mouse1*total_radius * (0.5 * cos(i * pi_inc)) + ww * 0.5;
                    ycorr = mouse2*total_radius * (0.5 * sin(i * pi_inc)) - wh * 0.5;
                 
                    /*
                    ofVertex(i*waveform_width/(float)MY_BUFFERSIZE, // X coord
                             waveform_amp * leftHistory[j][i],      // Y coord
                             0); 
                     */  // Z coord
                    
                   // std::cout << node.getScale() << "\n";
 
                    ofVertex(xcorr, ycorr, 0);
                }
            
            distance *= addSub;
            // End line. False == Don't connect first and last points.
            ofEndShape(true);
        }
    
    ofPopMatrix();
    ofPopStyle();
    
    
    // Similarly, draw waveform for left channel
//    ofPushStyle();
//    ofPushMatrix();
//    
//        ofTranslate(waveform_width, wh * 0.8, 0);
//        
//        ofSetLineWidth(3);
//        ofNoFill();
//        
//        for ( int j = MY_BUFFERHISTORY-1; j >= 0; j--){
//        //    ofTranslate( 0, 0, -50);
//            ofSetColor(245, 58, 135, 256*(j/(float)MY_BUFFERHISTORY));
//            ofBeginShape();
//            for (unsigned int i = 0; i < MY_BUFFERSIZE; i++){
//                ofVertex(i*waveform_width/(float)MY_BUFFERSIZE,
//                         waveform_amp * rightHistory[j][i],
//                         0);
    
    
    
    
//            }
//            ofEndShape(false);
//        }
//    
//    ofPopMatrix();
//    ofPopStyle();
    
    
}


//--------------------------------------------------------------
// audioIn() -- deal with incoming audio buffer
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    // Write incoming audio to buffer. Note: samples are interleaved.
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2];
        right[i]	= input[i*2+1];
        
    }
    
}


void ofApp::audioOut(float * output, int bufferSize, int nChannels){
   
    float *inBuf[2] = { &right[0], &right[0] };
    
    //--- effect stuff
    if (effectOn == true) {
    effect.compute(bufferSize, inBuf, audioBuffer); // computing one block with Faust
        
        // Interleave the output buffer
        for (int i = 0; i < bufferSize; i++)
        {
            output[2*i] = faustLeft[i]; //audioBuffer[0][i];
            output[2*i+1] = faustRight[i]; //audioBuffer[1][i];
        }
    }
//
//    effect.compute(bufferSize, audioBuffer, audioBuffer); // computing one block with Faust

}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // to change
    if (key == 'q'){
        disIntensity=32.0; // do something
    }
    if (key == 'w'){
        disIntensity=10.0; // do something
    }
    if (key == 'e'){
        disIntensity=5.0; // do something
    }
    if (key == 'r'){
        disIntensity=2.0; // do something
    }
    if (key == 't'){
        disIntensity=1.0; // do something
    }
    if (key == 'o'){
        disIntensity=0.01; // do something
    }
//    if (key == 'a'){
//        myDis= true; // do something
//    }
    if (key == 'a'){
        
        if(myDis == true) myDis = false;
        else myDis = true;// do something
    }
    if (key == 'v'){
        effectOn = true;    // turn effect on and off
    }
    if (key == 'b'){
        effectOn = false;    // turn effect on and off
    }
    if (key == 32){
        if(fftSwitch == true) fftSwitch = false;
        else fftSwitch = true;// turn effect on and off
    }
   
    if (key == 359){
        addSub = addSub-0.001;    // turn effect on and off
    }
    if (key == 357){
        addSub = addSub+ 0.001;    // turn effect on and off
    }
   // std::cout << key << "\n";
    if (key == 'z'){
        if(catMode3 == true) catMode3 = false;
        else catMode3 = true;
    }
    if (key == 'x'){
        if(catMode == true) catMode = false;
        else {
            catMode = true;
            rotIncr = 0;
        }
    }
    if (key == 'c'){
        if(catMode2 == true) catMode2 = false;
        else catMode2 = true;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//      std::cout << y << "\n";
    speed=y/100000.0;

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    mouse1=(x+100)/100;
    mouse2=(y+100)/100;
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
