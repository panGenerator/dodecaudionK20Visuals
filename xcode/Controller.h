/*
 *  Controller.h
 *  dodecaudionDrawTest
 *
 *  Created by Piotr Barszczewski on 10/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CONTROLLER_INCLUDED
#define CONTROLLER_INCLUDED

#include <string>

class Controller 
{
  public:
	~Controller(){}	
	virtual void update() = 0;
	virtual void set(std::string key, float value) = 0;
	virtual float get(std::string key) = 0;	

	virtual std::string getId() = 0;	
};

#endif