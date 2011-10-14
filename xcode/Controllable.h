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

class Controllable 
{
  public:
	virtual ~Controllable(){}
	
	virtual void set(std::string key, float value) = 0;
	virtual float get(std::string key) = 0;
	virtual std::string getId() = 0;
};

#endif