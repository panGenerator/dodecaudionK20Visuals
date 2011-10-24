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

void MIDIController::setup( string portName )
{
	//Never remove this line. mPortNames is populated during requesting listing of port names... which only outputs the list. strange.
	midiIn.listPorts();
	int portCount = midiIn.getNumPorts();
	for( int port = 0 ; port < portCount ; port++ ){
		string _portName = midiIn.mPortNames[port];
		if( _portName == portName ){
			console() << "Midi will open : " << _portName << ", requested " << portName << std::endl;
			setup( port );
		}
	}
}

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
	string portName;
	if( _port != 0 ){
		portName = midiIn.mPortNames[_port];
	}
	return "midi:" + portName;//boost::lexical_cast<string>( _port );
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