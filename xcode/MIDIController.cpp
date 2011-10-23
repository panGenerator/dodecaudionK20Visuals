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
		midiIn.listPorts();
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
	string portName = midiIn.mPortNames[_port];
	return "midi:" + portName;//boost::lexical_cast<string>( _port );
}


#pragma mark Instance methods
/**
 *
 */
void MIDIController::processMessage( midi::Message* msg )
{
	__logMessage( msg );	
	string key = "key" + boost::lexical_cast<string>( msg->byteOne );
	float val;
	
	val = (float)msg->byteTwo / (float)127.0f;
	//twaks for nano pad
	
	if( getId() == "midi:nanoPAD PAD" ){
		//64 is sent on note off
		if( msg->byteTwo == 64 ){
			val = 0;
		}else{
			val = (float)msg->byteTwo/127.0;
		}
	}
	
	//console() << key << " will be set to " << val << std::endl;
	set( key , val );
}

/**
 *
 */
void MIDIController::__logMessage( midi::Message* msg )
{
	console() << "midi port: " << msg->port << " ch: " << msg->channel << " status: " << msg->status;
	console() << " byteOne: " << msg->byteOne << " byteTwo: " << msg->byteTwo << std::endl;
	
}