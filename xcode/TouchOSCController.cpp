//
//  TouchOSCController.cpp
//  dodecaudionK20Visuals
//
//  Created by Piotr Barszczewski on 10/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "TouchOSCController.h"

#pragma mark Constructors/destructors

TouchOSCController::TouchOSCController()
{
    displayMsgLog = true;
	displayMsgExtended = true;
}

#pragma mark Controller interface implementation

void TouchOSCController::update()
{
    while (listener.hasWaitingMessages()) {
		osc::Message msg;
		listener.getNextMessage(&msg);
        parseMessage( msg );
    }
}

string TouchOSCController::getId()
{
    return "touchOsc";
}

#pragma mark Instance methods

/**
 * Parse incomming messages into controller state
 */
void TouchOSCController::parseMessage(osc::Message msg)
{
	float val;
	//parse accelerometer values
	//accelerometer values are eased 
	if( msg.getAddress() == "/accxyz" ){
		val = 0.6f * this->get( "accX" ) + 0.4f * msg.getArgAsFloat(0);
		this->set( "accX" , val );
		val = 0.6f * this->get( "accY" ) + 0.4f * msg.getArgAsFloat(1);
		this->set( "accY" , val );
		val = 0.6f * this->get( "accZ" ) + 0.4f * msg.getArgAsFloat(2);
		this->set( "accZ" , val );
	}
	//don't log accelerometer values since they are comming all the time
	else{
		this->__logMessage( msg );
	}
	
	//slider values
	//TODO: Replace the following conditions by a regexp
	if( msg.getAddress() == "/1/fader1" ){
		val = msg.getArgAsFloat(0);
		this->set( "slider1" , val );
	}
	if( msg.getAddress() == "/1/fader2" ){
		val = msg.getArgAsFloat(0);
		this->set( "slider2" , val );
	}
	if( msg.getAddress() == "/1/fader3" ){
		val = msg.getArgAsFloat(0);
		this->set( "slider3" , val );
	}
	if( msg.getAddress() == "/1/fader4" ){
		val = msg.getArgAsFloat(0);
		this->set( "slider4" , val );
	}
	

}

