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

#define TOUCH_OSC_PUSH_BUTTON_1_1 "pushButton1_1"
#define TOUCH_OSC_PUSH_BUTTON_1_2 "pushButton1_2"
#define TOUCH_OSC_PUSH_BUTTON_1_3 "pushButton1_3"
#define TOUCH_OSC_PUSH_BUTTON_1_4 "pushButton1_4"
#define TOUCH_OSC_PUSH_BUTTON_1_5 "pushButton1_5"


#define TOUCH_OSC_TOGGLE_BUTTON_1_1 "toggleButton1_1"
#define TOUCH_OSC_TOGGLE_BUTTON_1_2 "toggleButton1_2"
#define TOUCH_OSC_TOGGLE_BUTTON_1_3 "toggleButton1_3"
#define TOUCH_OSC_TOGGLE_BUTTON_1_4 "toggleButton1_4"
#define TOUCH_OSC_TOGGLE_BUTTON_1_5 "toggleButton1_5"
#define TOUCH_OSC_TOGGLE_BUTTON_2_1 "toggleButton2_1"
#define TOUCH_OSC_TOGGLE_BUTTON_2_2 "toggleButton2_2"
#define TOUCH_OSC_TOGGLE_BUTTON_2_3 "toggleButton2_3"
#define TOUCH_OSC_TOGGLE_BUTTON_2_4 "toggleButton2_4"
#define TOUCH_OSC_TOGGLE_BUTTON_2_5 "toggleButton2_5"
#define TOUCH_OSC_TOGGLE_BUTTON_2_6 "toggleButton2_6"
#define TOUCH_OSC_TOGGLE_BUTTON_2_7 "toggleButton2_7"
#define TOUCH_OSC_TOGGLE_BUTTON_2_8 "toggleButton2_8"


#define TOUCH_OSC_SLIDER_1_1 "slider1_1"
#define TOUCH_OSC_SLIDER_1_2 "slider1_2"
#define TOUCH_OSC_SLIDER_1_3 "slider1_3"
#define TOUCH_OSC_SLIDER_1_4 "slider1_4"
#define TOUCH_OSC_SLIDER_2_1 "slider2_1"
#define TOUCH_OSC_SLIDER_2_2 "slider2_2"
#define TOUCH_OSC_SLIDER_2_3 "slider2_3"
#define TOUCH_OSC_SLIDER_2_4 "slider2_4"
#define TOUCH_OSC_SLIDER_2_5 "slider2_5"
#define TOUCH_OSC_SLIDER_2_6 "slider2_6"
#define TOUCH_OSC_SLIDER_2_7 "slider2_7"
#define TOUCH_OSC_SLIDER_2_8 "slider2_8"


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