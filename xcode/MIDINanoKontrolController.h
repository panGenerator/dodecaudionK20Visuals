/*
 *  MidiNanoKontrolController.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MIDI_KORG_NANO_KONTROL_CONTROLLER_INCLUDED
#define MIDI_KORG_NANO_KONTROL_CONTROLLER_INCLUDED

#import "MIDIController.h"


#define MIDI_KORG_NANO_KONTROL_BUTTON_START "start"
#define MIDI_KORG_NANO_KONTROL_BUTTON_STOP "stop"
#define MIDI_KORG_NANO_KONTROL_BUTTON_REW "fwd"
#define MIDI_KORG_NANO_KONTROL_BUTTON_FWD "fwd"
#define MIDI_KORG_NANO_KONTROL_BUTTON_LOOP "loop"

#define MIDI_KORG_NANO_KONTROL_SLIDER_1_1 "slider1"
#define MIDI_KORG_NANO_KONTROL_SLIDER_1_2 "slider2"
#define MIDI_KORG_NANO_KONTROL_SLIDER_1_3 "slider3"
#define MIDI_KORG_NANO_KONTROL_SLIDER_1_4 "slider4"
#define MIDI_KORG_NANO_KONTROL_SLIDER_1_5 "slider5"
#define MIDI_KORG_NANO_KONTROL_SLIDER_1_6 "slider6"
#define MIDI_KORG_NANO_KONTROL_SLIDER_1_7 "slider7"
#define MIDI_KORG_NANO_KONTROL_SLIDER_1_8 "slider8"
#define MIDI_KORG_NANO_KONTROL_SLIDER_1_9 "slider9"

#define MIDI_KORG_NANO_KONTROL_KNOB_1_1 "knob1"
#define MIDI_KORG_NANO_KONTROL_KNOB_1_2 "knob2"
#define MIDI_KORG_NANO_KONTROL_KNOB_1_3 "knob3"
#define MIDI_KORG_NANO_KONTROL_KNOB_1_4 "knob4"
#define MIDI_KORG_NANO_KONTROL_KNOB_1_5 "knob5"
#define MIDI_KORG_NANO_KONTROL_KNOB_1_6 "knob6"
#define MIDI_KORG_NANO_KONTROL_KNOB_1_7 "knob7"
#define MIDI_KORG_NANO_KONTROL_KNOB_1_8 "knob8"
#define MIDI_KORG_NANO_KONTROL_KNOB_1_9 "knob9"


//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class MIDINanoKontrolController : public MIDIController
{
	
public:
    MIDINanoKontrolController();
    void update();
	string getId();
	
protected:
	void processMessage(midi::Message* msg);

};

#endif