/*
 *  RandomController.h
 *  dodecaudionDrawTest
 *
 *  Created by Piotr Barszczewski on 10/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "boost/any.hpp"
#include "Controller.h"
#include <string>


class GenericController : public Controller 
{
  public:
	GenericController();
	
	void update();
	void set(std::string key, float value);
	float get(std::string key);
	std::string getId();

  private:
	std::string *id;
	float _value;
};