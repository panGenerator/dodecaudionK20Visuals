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

#define MIDI_KORG_PAD_TRIGGER_1_1 "trigger_1_1"
#define MIDI_KORG_PAD_TRIGGER_1_2 "trigger_1_2"
#define MIDI_KORG_PAD_TRIGGER_1_3 "trigger_1_3"
#define MIDI_KORG_PAD_TRIGGER_1_4 "trigger_1_4"
#define MIDI_KORG_PAD_TRIGGER_1_5 "trigger_1_5"
#define MIDI_KORG_PAD_TRIGGER_1_6 "trigger_1_6"
#define MIDI_KORG_PAD_TRIGGER_1_7 "trigger_1_7"
#define MIDI_KORG_PAD_TRIGGER_1_8 "trigger_1_8"
#define MIDI_KORG_PAD_TRIGGER_1_9 "trigger_1_9"
#define MIDI_KORG_PAD_TRIGGER_1_10 "trigger_1_10"
#define MIDI_KORG_PAD_TRIGGER_1_11 "trigger_1_11"
#define MIDI_KORG_PAD_TRIGGER_1_12 "trigger_1_12"

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