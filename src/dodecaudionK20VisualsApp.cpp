#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "Drawable.h"
#include "Controller.h"

#include "GenericController.h"
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
	
	//visual stuff - drawn elements
	Dodecahedron dode;
};

void dodecaudionK20Visuals::setup()
{
	//init controllers
	genCtrl = GenericController();
	controllers.push_back( &genCtrl );
	
	//init drawable objects
    dode = Dodecahedron();
	visualObjects.push_back( &dode );
}

void dodecaudionK20Visuals::mouseDown( MouseEvent event )
{
}

void dodecaudionK20Visuals::update()
{
    //update all drawable objects
	for( vector<Drawable *>::iterator vis = visualObjects.begin() ; vis != visualObjects.end() ; ++vis ){
		for( vector<Controller *>::iterator ctrl = controllers.begin() ; ctrl != controllers.end() ; ++ctrl ){
			(*ctrl)->update();
			
			//test
			(*ctrl)->set( "framesCount" , getElapsedFrames() );
			
			updateDrawableByController( *vis, *ctrl );
		}		
		
		//recalculate after changing values
		(*vis)->update();
	}
}

void dodecaudionK20Visuals::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	for( vector<Drawable *>::iterator vis = visualObjects.begin() ; vis != visualObjects.end() ; ++vis ){
		(*vis)->draw();
	}
}

void dodecaudionK20Visuals::updateDrawableByController(Drawable *vis , Controller *ctrl)
{
	console() << "Updating vis: " << vis->getId() <<  " with ctrl: " << ctrl->getId() << std::endl;
	//generic controller updates
	if( ctrl->getId().compare( "genericController" ) == 0 ){
		vis->set( "framesCount" , ctrl->get("framesCount") );
	}
	
}

CINDER_APP_BASIC( dodecaudionK20Visuals, RendererGl );
