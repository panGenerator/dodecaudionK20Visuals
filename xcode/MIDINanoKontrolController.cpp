/*
 *  MidiNanoKontrolController.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "MIDINanoKontrolController.h"

#pragma mark Constructors/destructors

MIDINanoKontrolController::MIDINanoKontrolController()
{
}

#pragma mark Controller interface implementation

void MIDINanoKontrolController::update()
{
	while( midiIn.hasWaitingMessages() ){
		midi::Message msg;
		midiIn.getNextMessage(&msg);
		
		processMessage(&msg);
	}
}

string MIDINanoKontrolController::getId()
{
	return "midi:nanoKONTROL SLIDER/KNOB";
}


#pragma mark Instance methods
/**
 *
 */
void MIDINanoKontrolController::processMessage( midi::Message* msg )
{
	console() << "Slider" << std::endl;
	__logMessage( msg );	
	

	int keyId = (int)msg->byteOne;
	float val = (float)msg->byteTwo/127.0;
	
	//all keys are mapped to "key"+byteOne by default for reference
	string key = "key" + boost::lexical_cast<string>( msg->byteOne );
	set( key , val );
	
	
	//attach values to predefined variables
	switch( keyId ){
		//Scene #1 sliders
		case 2:
			set( MIDI_KORG_NANO_KONTROL_SLIDER_1_1 , val ); break;
		case 3:
			set( MIDI_KORG_NANO_KONTROL_SLIDER_1_2 , val ); break;
		case 4:
			set( MIDI_KORG_NANO_KONTROL_SLIDER_1_3 , val ); break;
		case 5:
			set( MIDI_KORG_NANO_KONTROL_SLIDER_1_4 , val ); break;
		case 6:
			set( MIDI_KORG_NANO_KONTROL_SLIDER_1_5 , val ); break;
		case 7:
			set( MIDI_KORG_NANO_KONTROL_SLIDER_1_6 , val ); break;
		case 8:
			set( MIDI_KORG_NANO_KONTROL_SLIDER_1_7 , val ); break;
		case 9:
			set( MIDI_KORG_NANO_KONTROL_SLIDER_1_8 , val ); break;
		case 10:
			set( MIDI_KORG_NANO_KONTROL_SLIDER_1_9 , val ); break;
		//Scene #1 knobs
		case 14:
			set( MIDI_KORG_NANO_KONTROL_KNOB_1_1 , val ); break;
		case 15:
			set( MIDI_KORG_NANO_KONTROL_KNOB_1_2 , val ); break;
		case 16:
			set( MIDI_KORG_NANO_KONTROL_KNOB_1_3 , val ); break;
		case 17:
			set( MIDI_KORG_NANO_KONTROL_KNOB_1_4 , val ); break;
		case 18:
			set( MIDI_KORG_NANO_KONTROL_KNOB_1_5 , val ); break;
		case 19:
			set( MIDI_KORG_NANO_KONTROL_KNOB_1_6 , val ); break;
		case 20:
			set( MIDI_KORG_NANO_KONTROL_KNOB_1_7 , val ); break;
		case 21:
			set( MIDI_KORG_NANO_KONTROL_KNOB_1_8 , val ); break;
		case 22:
			set( MIDI_KORG_NANO_KONTROL_KNOB_1_9 , val ); break;			
		//Scene * - transport buttons (play,stop, etc.)
		case 47:
			transitorySet( MIDI_KORG_NANO_KONTROL_BUTTON_REW , val ); break;
		case 45:
			transitorySet( MIDI_KORG_NANO_KONTROL_BUTTON_START , val ); break;
		case 48:
			transitorySet( MIDI_KORG_NANO_KONTROL_BUTTON_FWD , val ); break;
		case 49:
			transitorySet( MIDI_KORG_NANO_KONTROL_BUTTON_LOOP , val ); break;
		case 46:
			transitorySet( MIDI_KORG_NANO_KONTROL_BUTTON_STOP , val ); break;
			
	}
	
}