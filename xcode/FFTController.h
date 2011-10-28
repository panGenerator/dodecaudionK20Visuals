/*
 *  FFTController.h
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FFT_CONTROLLER_INCLUDED
#define FFT_CONTROLLER_INCLUDED

#include "cinder/app/AppBasic.h"	//used for console()
#include "cinder/audio/Input.h"
#include "cinder/audio/FftProcessor.h"
#include <boost/lexical_cast.hpp>

#include "GenericController.h"

#define BANDS_COUNT_KEY "bands"

#define FFT_BANDS_AVG "bandsAvg"

using namespace std;
using namespace ci;
using namespace ci::app;

class FFTController : public GenericController
{
	
public:
	FFTController();
	void setup(int bands);
    void update();
    string getId();	

private: 
	int bandsCount;
	
	audio::Input audioInput;
	boost::shared_ptr<float> fftData;
	audio::PcmBuffer32fRef pcmBuffer;

	
	void readFFT();
	
};

#endif