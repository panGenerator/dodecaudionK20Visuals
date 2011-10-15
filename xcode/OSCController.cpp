//
//  OSCController.cpp
//  dodecaudionK20Visuals
//
//  Created by Piotr Barszczewski on 10/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "OSCController.h"

OSCController::OSCController()
{
    displayMsgLog = true;
	displayMsgExtended = false;
}

#pragma mark Controller interface implementation

void OSCController::setup(int listenPort)
{
    port = listenPort;
    listener.setup( port );    
}

void OSCController::update()
{
    while (listener.hasWaitingMessages()) {
		osc::Message msg;
		listener.getNextMessage(&msg);
        parseMessage( msg );
    }
}


string OSCController::getId()
{
    return "osc";
}

#pragma mark Instance methods

/**
 * Process the incomming message
 */
void OSCController::parseMessage(osc::Message msg)
{
    __logMessage( msg );
}


/**
 * Log incomming OSC msgs
 * Taken from OSCListener example provided with the Cinder OSC block
 */
void OSCController::__logMessage( osc::Message msg )
{
    if( displayMsgLog ){
        console() << "Incomming OSC msg: @ " << getId() << std::endl;
		console() << "Address: " << msg.getAddress() << std::endl;
		if( displayMsgExtended ){
			console() << "Num Arg: " << msg.getNumArgs() << std::endl;
			for (int i = 0; i < msg.getNumArgs(); i++) {
				console() << "-- Argument " << i << std::endl;
				console() << "---- type: " << msg.getArgTypeName(i) << std::endl;
				if (msg.getArgType(i) == osc::TYPE_INT32){
					try {
						console() << "------ value: "<< msg.getArgAsInt32(i) << std::endl;
					}
					catch (...) {
						console() << "Exception reading argument as int32" << std::endl;
					}
					
				}else if (msg.getArgType(i) == osc::TYPE_FLOAT){
					try {
						console() << "------ value: " << msg.getArgAsFloat(i) << std::endl;
					}
					catch (...) {
						console() << "Exception reading argument as float" << std::endl;
					}
					
				}else if (msg.getArgType(i) == osc::TYPE_STRING){
					try {
						console() << "------ value: " << msg.getArgAsString(i).c_str() << std::endl;
					}
					catch (...) {
						console() << "Exception reading argument as string" << std::endl;
					}
					
				}
			}
		}

        
    }
}