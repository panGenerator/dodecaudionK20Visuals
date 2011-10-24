/*
 *  MidiNanoKontrolController.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MIDI_KORG_NANO_PAD_CONTROLLER_INCLUDED
#define MIDI_KORG_NANO_PAD_CONTROLLER_INCLUDED

#import "MIDIController.h"

//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class MIDINanoPadController : public MIDIController
{
public:
    MIDINanoPadController();
    void update();
	string getId();
	
protected:
	void processMessage(midi::Message* msg);

	
};

#endif