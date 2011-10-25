/*
 *  RandomController.h
 *  dodecaudionDrawTest
 *
 *  Created by Piotr Barszczewski on 10/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GENERIC_CONTROLLER_INCLUDED
#define GENERIC_CONTROLLER_INCLUDED

#include "Controller.h"
#include "ValuesMap.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

class GenericController : public Controller 
{
  public:
	GenericController();
	void setup();
	void update();
	void set(string key, float value);
	void transitorySet(string key, float value);
	float get(string key, bool persistTransitory);
	void releaseTransitory();
	float get(string key);
    vector<string> keys();
	string getId();

  protected:
    ValuesMap _values;
};

#endif