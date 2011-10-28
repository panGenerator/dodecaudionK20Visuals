//
//  DodecaudionOSCController.cpp
//  dodecaudionK20Visuals
//
//  Created by Piotr Barszczewski on 10/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "DodecaudionOSCController.h"

#pragma mark Constructors/destructors

DodecaudionOSCController::DodecaudionOSCController()
{
    displayMsgLog = true;
	displayMsgExtended = true;
}

#pragma mark Controller interface implementation

void DodecaudionOSCController::update()
{
    while (listener.hasWaitingMessages()) {
		osc::Message msg;
		listener.getNextMessage(&msg);
        parseMessage( msg );
    }
}

string DodecaudionOSCController::getId()
{
    return "dodecaudionOsc";
}

#pragma mark Instance methods

/**
 * Parse incomming messages into controller state
 */
void DodecaudionOSCController::parseMessage(osc::Message msg)
{
	//this->__logMessage( msg );
	
	if( msg.getAddress() == "/Instrument01" ){
		set( DODECAUDION_OSC_WALL_1 , msg.getArgAsFloat(0) );
		set( DODECAUDION_OSC_WALL_3 , msg.getArgAsFloat(1) );
		set( DODECAUDION_OSC_WALL_5 , msg.getArgAsFloat(2) );
		set( DODECAUDION_OSC_WALL_7 , msg.getArgAsFloat(3) );
		set( DODECAUDION_OSC_WALL_9 , msg.getArgAsFloat(4) );
		set( DODECAUDION_OSC_WALL_11 , msg.getArgAsFloat(5) );
	}
	
	if( msg.getAddress() == "/Instrument02" ){
		set( DODECAUDION_OSC_WALL_2 , msg.getArgAsFloat(0) );
		set( DODECAUDION_OSC_WALL_4 , msg.getArgAsFloat(1) );
		set( DODECAUDION_OSC_WALL_6 , msg.getArgAsFloat(2) );
		set( DODECAUDION_OSC_WALL_8 , msg.getArgAsFloat(3) );
		set( DODECAUDION_OSC_WALL_10 , msg.getArgAsFloat(4) );
		set( DODECAUDION_OSC_WALL_12 , msg.getArgAsFloat(5) );		
	}	
}

