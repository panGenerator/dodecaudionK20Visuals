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

#include "boost/any.hpp"
#include "Controller.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

class GenericController : public Controller 
{
  public:
	GenericController();
	
	void update();
	void set(string key, float value);
	float get(string key);
    vector<string> keys();
	string getId();

  private:
	string *id;
    map<string,float> _values;
};

#endif