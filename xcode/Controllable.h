/*
 *  Controllable.h
 *  dodecaudionDrawTest
 *
 *  Created by Piotr Barszczewski on 10/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CONTROLLABLE_INCLUDED
#define CONTROLLABLE_INCLUDED

#include <string>
#include <vector>

using namespace std;

class Controllable 
{
  public:
	virtual ~Controllable(){}
	
	virtual void set(string key, float value) = 0;
	virtual float get(string key) = 0;
	virtual vector<string> keys() = 0;
	virtual string getId() = 0;
};

#endif