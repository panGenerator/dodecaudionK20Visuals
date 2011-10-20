/*
 *  MIDIController.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "MIDIController.h"

#pragma mark Constructors/destructors

MIDIController::MIDIController()
{
}

#pragma mark Controller interface implementation

void MIDIController::setup( int port )
{
	_port = port;
	if( midiIn.getNumPorts() > 0 ){
		//midiIn.listPorts();
		midiIn.openPort(_port);
	}
}

void MIDIController::update()
{
	while( midiIn.hasWaitingMessages() ){
		midi::Message msg;
		midiIn.getNextMessage(&msg);
		
		processMessage(&msg);
	}
}

string MIDIController::getId()
{
	if( _port != 0 ){
		return "midi" + boost::lexical_cast<string>( _port );
	}
	return "midi";
}


#pragma mark Instance methods
/**
 *
 */
void MIDIController::processMessage( midi::Message* msg )
{
	__logMessage( msg );
}

/**
 *
 */
void MIDIController::__logMessage( midi::Message* msg )
{
	console() << "midi port: " << msg->port << " ch: " << msg->channel << " status: " << msg->status;
	console() << " byteOne: " << msg->byteOne << " byteTwo: " << msg->byteTwo << std::endl;
	
}