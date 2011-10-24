/*
 *  MIDIController.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MIDI_CONTROLLER_INCLUDED
#define MIDI_CONTROLLER_INCLUDED

#include "cinder/app/AppBasic.h"	//used for console()
#include "MidiIn.h"
#include "MidiMessage.h"
#include "MidiConstants.h"
#include <boost/lexical_cast.hpp>

#include "GenericController.h"

using namespace std;
using namespace ci;
using namespace ci::app;

class MIDIController : public GenericController
{

public:
	MIDIController();
	void setup();
	void setup( string portName );
	void setup( int port );
    void update();
    string getId();	

protected:
    void processMessage(midi::Message* msg);
	void __logMessage(midi::Message* msg);

	int _port;
	midi::Input midiIn;
	
};

#endif