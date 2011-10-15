//
//  TouchOSCController.h
//  dodecaudionK20Visuals
//
//  Created by Piotr Barszczewski on 10/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "OSCController.h"

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