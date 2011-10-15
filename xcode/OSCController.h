//
//  OSCController.h
//  dodecaudionK20Visuals
//
//  Created by Piotr Barszczewski on 10/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef OSC_CONTROLLER_INCLUDED
#define OSC_CONTROLLER_INCLUDED

#include "cinder/app/AppBasic.h"
#include "OscListener.h"
#include <string>
#include "GenericController.h"

//#define OSC_CONTROLLER_LOG_MESSAGES 1

//work in the cinder's namespace
using namespace std;
using namespace ci;
using namespace ci::app;

class OSCController : public GenericController
{
public:
    OSCController();
    void setup(int listenPort);
    void update();
    void parseMessage(osc::Message msg);
    string getId();
    
protected:
    void __logMessage( osc::Message msg );
    
    osc::Listener listener;
    int port;
    bool displayMsgLog,displayMsgExtended;
};


#endif