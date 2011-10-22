#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include <boost/lexical_cast.hpp>

#include "Drawable.h"
#include "Controller.h"

#include "GenericController.h"
#include "OSCController.h"
#include "TouchOSCController.h"
#include "FFTController.h"
#include "MIDIController.h"

#include "Dodecahedron.h"
#include "FFTVisualiser.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class dodecaudionK20Visuals : public AppBasic {
public:
	void setup();
	void resize( ResizeEvent event );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	
	void updateDrawableByController(Drawable *vis , Controller *ctrl);
	
	vector<Controller *> controllers;
	vector<Drawable *> visualObjects;
	CameraPersp	cam;
	
	
	//controllers for input (OSC, MIDI, etc.)
	GenericController genCtrl;
    OSCController oscCtrl;
	TouchOSCController touchOscCtrl;
	FFTController fftCtrl;
	MIDIController midiCtrl;
	
	//visual stuff - drawn elements
	Dodecahedron dode;
	FFTVisualiser fftVis;
    
};

void dodecaudionK20Visuals::setup()
{
	//init controllers
	genCtrl.setup();
	controllers.push_back( &genCtrl );
    
    oscCtrl.setup(10001);
    controllers.push_back( &oscCtrl );

    touchOscCtrl.setup(10000);
    controllers.push_back( &touchOscCtrl );
	
	fftCtrl.setup(128);
	controllers.push_back( &fftCtrl );
	
	midiCtrl.setup(0);
	controllers.push_back( &midiCtrl );
	
	//init drawable objects
	dode.setup();
	visualObjects.push_back( &dode );
	visualObjects.push_back( &fftVis );	
	
	cam.lookAt( Vec3f(20,0,-600) , Vec3f::zero() , Vec3f::yAxis() );
}

void dodecaudionK20Visuals::resize( ResizeEvent event )
{
	cam.setAspectRatio( getWindowAspectRatio() );
}

void dodecaudionK20Visuals::mouseDown( MouseEvent event )
{
}

/**
 * Update all inputs
 */
void dodecaudionK20Visuals::update()
{
	//update inputs
	for( vector<Controller *>::iterator ctrl = controllers.begin() ; ctrl != controllers.end() ; ++ctrl ){			
		(*ctrl)->update();
		//test
		(*ctrl)->set( "framesCount" , getElapsedFrames() );		
	}
    
	//update all drawable objects
	for( vector<Drawable *>::iterator vis = visualObjects.begin() ; vis != visualObjects.end() ; ++vis ){
		for( vector<Controller *>::iterator ctrl = controllers.begin() ; ctrl != controllers.end() ; ++ctrl ){			
			//pass controller data to Drawable objects
			updateDrawableByController( *vis, *ctrl );
		}				
		//recalculate after changing values
		(*vis)->update();
	}
}

/**
 * Draw the stage
 */
void dodecaudionK20Visuals::draw()
{
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::clear( Color( 0, 0, 0 ) ); 

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glLoadIdentity();
	gl::setMatrices( cam );
		
	for( vector<Drawable *>::iterator vis = visualObjects.begin() ; vis != visualObjects.end() ; ++vis ){
		(*vis)->draw();
	}
	
	
}

/**
 * Perform updating of all Drawable+Controllable object by controllers. 
 * This is where mapping of Controller values to Drawable params is done
 * TODO: Replace this by some way of mapping the controls to visuals - maybe a file?
 */

void dodecaudionK20Visuals::updateDrawableByController(Drawable *vis , Controller *ctrl)
{
	//console() << "Updating vis: " << vis->getId() <<  " with ctrl: " << ctrl->getId() << std::endl;
	//generic controller updates
	if( ctrl->getId() ==  "generic" ){
		vis->set( "framesCount" , ctrl->get("framesCount") );
	}
	//touchOSC controls mapping
	if( ctrl->getId() == "touchOsc" ){
		//Dodecaudion
		if( vis->getId() == "dodecahedron" ){
			vis->set( "radius" , ctrl->get( "slider4" ) );
			
			//0.5 + 0.5f *    <= so shape is always visible, even if no TouchOSC input
			vis->set( "edgeColorR" , 0.5f + 0.5f * ctrl->get( "slider1" ) );
			vis->set( "edgeColorG" , 0.5f + 0.5f * ctrl->get( "slider2" ) );
			vis->set( "edgeColorB" , 0.5f + 0.5f * ctrl->get( "slider3" ) );
			
			vis->set( "rotationX" , ctrl->get( "accX" ) );
			vis->set( "rotationY" , ctrl->get( "accY" ) );
			vis->set( "rotationZ" , ctrl->get( "accZ" ) );
		}
		//update fft
		if( vis->getId() == "fftVisualiser" ){
			vis->set( "blockSize" , ctrl->get( "slider4" ) );
		}
	}
	//FFT controls mapping
	if( ctrl->getId() == "fft" ){
		//update dodecaudion
		if( vis->getId() == "dodecaudion" ){
			//vis->set( "edgeColorR" , ctrl->get( "band1" ) );
//			vis->set( "edgeColorB" , ctrl->get( "band2" ) );
//			vis->set( "edgeColorG" , ctrl->get( "band3" ) );
		}
		//update fft
		if( vis->getId() == "fftVisualiser" ){
			vector<string> values = ctrl->keys();
			for( vector<string>::iterator it = values.begin() ; it != values.end() ; ++it ){
				vis->set( *it , ctrl->get( *it ) );
			}
		}
	}
}

CINDER_APP_BASIC( dodecaudionK20Visuals, RendererGl );
