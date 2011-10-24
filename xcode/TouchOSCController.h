//
//  TouchOSCController.h
//  dodecaudionK20Visuals
//
//  Created by Piotr Barszczewski on 10/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef TOUCH_OSC_CONTROLLER_INCLUDED
#define TOUCH_OSC_CONTROLLER_INCLUDED

#include "OSCController.h"

#define TOUCH_OSC_PUSH_BUTTON_1 "button1"
#define TOUCH_OSC_PUSH_BUTTON_2 "button2"
#define TOUCH_OSC_PUSH_BUTTON_3 "button3"
#define TOUCH_OSC_PUSH_BUTTON_4 "button4"
#define TOUCH_OSC_PUSH_BUTTON_5 "button5"

#define TOUCH_OSC_TOGGLE_BUTTON_1 "button1"
#define TOUCH_OSC_TOGGLE_BUTTON_2 "button2"
#define TOUCH_OSC_TOGGLE_BUTTON_3 "button3"

#define TOUCH_OSC_SLIDER_1 "slider1"
#define TOUCH_OSC_SLIDER_2 "slider2"
#define TOUCH_OSC_SLIDER_3 "slider3"
#define TOUCH_OSC_SLIDER_4 "slider4"

//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class TouchOSCController : public OSCController
{
public:
    TouchOSCController();
	void update();
	void parseMessage(osc::Message msg);
    string getId();    
};

#endif