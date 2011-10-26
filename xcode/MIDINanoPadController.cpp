/*
 *  MidiNanoKontrolController.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 *
 *  Object handling incomming midi messages from Kor Nano pads
 */

#include "MIDINanoPadController.h"

#pragma mark Constructors/destructors

MIDINanoPadController::MIDINanoPadController()
{
}

#pragma mark Controller interface implementation

void MIDINanoPadController::update()
{
	while( midiIn.hasWaitingMessages() ){
		midi::Message msg;
		midiIn.getNextMessage(&msg);
		processMessage(&msg);
	}
}



string MIDINanoPadController::getId()
{
	return "midi:nanoPAD PAD";
}

#pragma mark Instance methods
/**
 *
 */
void MIDINanoPadController::processMessage( midi::Message* msg )
{
	//console() << "Pad" << std::endl;
	__logMessage( msg );	
	
	int keyId = (int)msg->byteOne;
	float val = (float)msg->byteTwo;
	
	//all keys are mapped to "key"+byteOne by default
	string key = "key" + boost::lexical_cast<string>( msg->byteOne );
	
	//64 is sent on note off. any other value is sent on noteOn
	if( val == 64.0f ){
		val = 0;
	}else{
		val = val/127.0;
	}
	
	switch( keyId ){
		case 39:
			set( MIDI_KORG_PAD_TRIGGER_1_1 , val ); break;
		case 48:
			set( MIDI_KORG_PAD_TRIGGER_1_2 , val ); break;
		case 45:
			set( MIDI_KORG_PAD_TRIGGER_1_3 , val ); break;
		case 43:
			set( MIDI_KORG_PAD_TRIGGER_1_4 , val ); break;
		case 51:
			set( MIDI_KORG_PAD_TRIGGER_1_5 , val ); break;
		case 49:
			set( MIDI_KORG_PAD_TRIGGER_1_6 , val ); break;
		
	}
	
	//set( key , val );
}