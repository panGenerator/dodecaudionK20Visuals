//
//  DodecaudionOSCController.h
//  dodecaudionK20Visuals
//
//  Created by Piotr Barszczewski on 10/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef DODECAUDION_OSC_CONTROLLER_INCLUDED
#define DODECAUDION_OSC_CONTROLLER_INCLUDED

#include "OSCController.h"

#define DODECAUDION_OSC_WALL_1 "dodecaudionWall1"
#define DODECAUDION_OSC_WALL_2 "dodecaudionWall2"
#define DODECAUDION_OSC_WALL_3 "dodecaudionWall3"
#define DODECAUDION_OSC_WALL_4 "dodecaudionWall4"
#define DODECAUDION_OSC_WALL_5 "dodecaudionWall5"
#define DODECAUDION_OSC_WALL_6 "dodecaudionWall6"
#define DODECAUDION_OSC_WALL_7 "dodecaudionWall7"
#define DODECAUDION_OSC_WALL_8 "dodecaudionWall8"
#define DODECAUDION_OSC_WALL_9 "dodecaudionWall9"
#define DODECAUDION_OSC_WALL_10 "dodecaudionWall10"
#define DODECAUDION_OSC_WALL_11 "dodecaudionWall11"
#define DODECAUDION_OSC_WALL_12 "dodecaudionWall12"

//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class DodecaudionOSCController : public OSCController
{
public:
    DodecaudionOSCController();
	void update();
	void parseMessage(osc::Message msg);
    string getId();    
};

#endif