#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "Drawable.h"
#include "Controller.h"

#include "GenericController.h"
#include "OSCController.h"
#include "TouchOSCController.h"
#include "Dodecahedron.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class dodecaudionK20Visuals : public AppBasic {
public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	
	void updateDrawableByController(Drawable *vis , Controller *ctrl);
	
	vector<Controller *> controllers;
	vector<Drawable *> visualObjects;
	
	//controllers for input (OSC, MIDI, etc.)
	GenericController genCtrl;
    OSCController oscCtrl;
	TouchOSCController touchOscCtrl;
	
	//visual stuff - drawn elements
	Dodecahedron dode;
    
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
	
	
	//init drawable objects
    dode = Dodecahedron();
	visualObjects.push_back( &dode );
        
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
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
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
			
			vis->set( "edgeColorR" , ctrl->get( "slider1" ) );
			vis->set( "edgeColorG" , ctrl->get( "slider2" ) );
			vis->set( "edgeColorB" , ctrl->get( "slider3" ) );
			
			vis->set( "rotationX" , ctrl->get( "accX" ) );
			vis->set( "rotationY" , ctrl->get( "accY" ) );
			vis->set( "rotationZ" , ctrl->get( "accZ" ) );
		}
		
	}
}

CINDER_APP_BASIC( dodecaudionK20Visuals, RendererGl );
