/*
 *  FFTController.cpp
 *  dodecaudionK20Visuals
 *
 *  Created by Piotr Barszczewski on 10/15/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "FFTController.h"


#pragma mark Constructors/destructors

FFTController::FFTController()
{
	bandsCount = 0;
	set( BANDS_COUNT_KEY , bandsCount );
}


#pragma mark Controller interface implementation

void FFTController::setup( int bands )
{
	//iterate input devices and print their names to the console
	/*
	const std::vector<audio::InputDeviceRef>& devices = audio::Input::getDevices();
	for( std::vector<audio::InputDeviceRef>::const_iterator iter = devices.begin(); iter != devices.end(); ++iter ) {
		console() << (*iter)->getName() << std::endl;
	}
	*/
	
	if( bands >= 0 ){
		set( BANDS_COUNT_KEY , bands );
	}	
	audioInput = audio::Input();
	audioInput.start();
}

void FFTController::update()
{
	bandsCount = get( BANDS_COUNT_KEY );
	readFFT();
}

string FFTController::getId()
{
	return "fft";
}


#pragma mark Instance methods

void FFTController::readFFT()
{
	pcmBuffer = audioInput.getPcmBuffer();
	if( pcmBuffer ){
		float avg;
		int bandsCount = (int) get( BANDS_COUNT_KEY );
		string bandId;
		float bandVal;
		
		fftData = audio::calculateFft( pcmBuffer->getChannelData( audio::CHANNEL_FRONT_LEFT ) , bandsCount );
		
		float *fftFloatData = fftData.get();
		if( fftFloatData ){
			for( int band = 0 ; band < bandsCount ; band++ ){
				bandId = "band" + boost::lexical_cast<string>( band );
				
				//easing
				bandVal = 0.5 * get( bandId ) + 0.4 * fftFloatData[band];
				avg += bandVal;
				set( bandId , bandVal );			
			}
			if( bandsCount > 0 ){
				avg /= bandsCount;
				set( FFT_BANDS_AVG , avg );
			}
		}
	}	
}