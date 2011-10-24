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
	
	val = msg.getArgAsFloat(0);
	//slider values
	if( msg.getAddress() == "/1/fader1"){
		this->set( TOUCH_OSC_SLIDER_1 , val ); 
	}
	if( msg.getAddress() == "/1/fader2"){
		this->set( TOUCH_OSC_SLIDER_2 , val ); 
	}
	if( msg.getAddress() == "/1/fader3"){
		this->set( TOUCH_OSC_SLIDER_3 , val ); 
	}
	if( msg.getAddress() == "/1/fader4"){
		this->set( TOUCH_OSC_SLIDER_4 , val ); 
	}
	//buttons
	if( msg.getAddress() == "/1/push1"){
		this->set( TOUCH_OSC_PUSH_BUTTON_1 , val ); 
	}
	if( msg.getAddress() == "/1/push2"){
		this->set( TOUCH_OSC_PUSH_BUTTON_2 , val ); 
	}
	if( msg.getAddress() == "/1/push3"){
		this->set( TOUCH_OSC_PUSH_BUTTON_3 , val ); 
	}
	if( msg.getAddress() == "/1/push4"){
		this->set( TOUCH_OSC_PUSH_BUTTON_4 , val ); 
	}
	if( msg.getAddress() == "/1/push5" ){
		this->set( TOUCH_OSC_PUSH_BUTTON_5 , val ); 
	}		
	

}

