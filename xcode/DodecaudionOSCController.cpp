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
	this->__logMessage( msg );
	
	//
	//TODO: add value reading here...
	//
}

