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