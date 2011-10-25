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
		//this->__logMessage( msg );
	}
	
	val = msg.getArgAsFloat(0);
	//slider values
	if( msg.getAddress() == "/1/fader1"){
		set( TOUCH_OSC_SLIDER_1_1 , val ); 
	}
	if( msg.getAddress() == "/1/fader2"){
		set( TOUCH_OSC_SLIDER_1_2 , val ); 
	}
	if( msg.getAddress() == "/1/fader3"){
		set( TOUCH_OSC_SLIDER_1_3 , val ); 
	}
	if( msg.getAddress() == "/1/fader4"){
		set( TOUCH_OSC_SLIDER_1_4 , val ); 
	}
	if( msg.getAddress() == "/2/fader1"){
		set( TOUCH_OSC_SLIDER_2_1 , val ); 
	}
	if( msg.getAddress() == "/2/fader2"){
		set( TOUCH_OSC_SLIDER_2_2 , val ); 
	}
	if( msg.getAddress() == "/2/fader3"){
		set( TOUCH_OSC_SLIDER_2_3 , val ); 
	}
	if( msg.getAddress() == "/2/fader4"){
		set( TOUCH_OSC_SLIDER_2_4 , val ); 
	}
	if( msg.getAddress() == "/2/fader5"){
		set( TOUCH_OSC_SLIDER_2_5 , val ); 
	}
	if( msg.getAddress() == "/2/fader6"){
		set( TOUCH_OSC_SLIDER_2_6 , val ); 
	}
	if( msg.getAddress() == "/2/fader7"){
		set( TOUCH_OSC_SLIDER_2_7 , val ); 
	}
	if( msg.getAddress() == "/2/fader8"){
		set( TOUCH_OSC_SLIDER_2_8 , val ); 
	}
	
	//push buttons
	if( msg.getAddress() == "/1/push1"){
		transitorySet( TOUCH_OSC_PUSH_BUTTON_1_1 , val ); 
	}
	if( msg.getAddress() == "/1/push2"){
		transitorySet( TOUCH_OSC_PUSH_BUTTON_1_2 , val ); 
	}
	if( msg.getAddress() == "/1/push3"){
		transitorySet( TOUCH_OSC_PUSH_BUTTON_1_3 , val ); 
	}
	if( msg.getAddress() == "/1/push4"){
		transitorySet( TOUCH_OSC_PUSH_BUTTON_1_4 , val ); 
	}
	if( msg.getAddress() == "/1/push5" ){
		transitorySet( TOUCH_OSC_PUSH_BUTTON_1_5 , val ); 
	}		

	//toggle buttons
	if( msg.getAddress() == "/1/toggle1"){
		set( TOUCH_OSC_TOGGLE_BUTTON_1_1 , val ); 
	}
	if( msg.getAddress() == "/1/toggle2"){
		set( TOUCH_OSC_TOGGLE_BUTTON_1_2 , val ); 
	}
	if( msg.getAddress() == "/1/toggle3"){
		set( TOUCH_OSC_TOGGLE_BUTTON_1_3 , val ); 
	}	
	if( msg.getAddress() == "/2/toggle1"){
		set( TOUCH_OSC_TOGGLE_BUTTON_2_1 , val ); 
	}
	if( msg.getAddress() == "/2/toggle2"){
		set( TOUCH_OSC_TOGGLE_BUTTON_2_2 , val ); 
	}
	if( msg.getAddress() == "/2/toggle3"){
		set( TOUCH_OSC_TOGGLE_BUTTON_2_3 , val ); 
	}
	if( msg.getAddress() == "/2/toggle4"){
		set( TOUCH_OSC_TOGGLE_BUTTON_2_4 , val ); 
	}
	if( msg.getAddress() == "/2/toggle5" ){
		set( TOUCH_OSC_TOGGLE_BUTTON_2_5 , val ); 
	}		
	if( msg.getAddress() == "/2/toggle6"){
		set( TOUCH_OSC_TOGGLE_BUTTON_2_6 , val ); 
	}
	if( msg.getAddress() == "/2/toggle7"){
		set( TOUCH_OSC_TOGGLE_BUTTON_2_7 , val ); 
	}
	if( msg.getAddress() == "/2/toggle8" ){
		set( TOUCH_OSC_TOGGLE_BUTTON_2_8 , val ); 
	}		

}

