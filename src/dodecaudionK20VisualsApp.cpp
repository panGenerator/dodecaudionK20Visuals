#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Camera.h"
#include <boost/lexical_cast.hpp>
#include "cinder/ImageIo.h"

#include "Drawable.h"
#include "Controller.h"
#include "Filter.h"

#include "GenericController.h"
#include "OSCController.h"
#include "TouchOSCController.h"
#include "FFTController.h"
#include "MIDIController.h"

#include "Dodecahedron.h"
#include "FFTVisualiser.h"

#include "ShaderFilter.h"


#define RES_GENERIC_FILTER_SHADER_VERT		CINDER_RESOURCE( ../resources/, passThru_vert.glsl, 128, GLSL )
#define RES_GENERIC_FILTER_SHADER_FRAG		CINDER_RESOURCE( ../resources/, simpleNoise_frag.glsl, 129, GLSL )



using namespace ci;
using namespace ci::app;
using namespace std;

class dodecaudionK20Visuals : public AppBasic {
public:
	void prepareSettings(Settings *settings);	
	void setup();
	void resize( ResizeEvent event );
	void mouseDown( MouseEvent event );	
	void keyDown( KeyEvent event );
	void update();
	void draw();
	
	void updateDrawableByController(Drawable *vis , Controller *ctrl);
	
	vector<Controller *> controllers;
	vector<Drawable *> visualObjects;
	vector<Filter *> visualFilters;
	
	CameraPersp	cam;
	
	gl::Fbo::Format fboFormat;
	gl::Fbo	fbo;
	gl::Texture fboTexture;
	
	
	//controllers for input (OSC, MIDI, etc.)
	GenericController genCtrl;
    OSCController oscCtrl;
	TouchOSCController touchOscCtrl;
	FFTController fftCtrl;
	MIDIController midiCtrl;
	
	//visual stuff - drawn elements
	Dodecahedron dode;
	FFTVisualiser fftVis;
    
	ShaderFilter shaderFlt;
	
};

#pragma mark CINDER_APP_BASIC methods
	
void dodecaudionK20Visuals::prepareSettings(Settings *settings){
	settings->setFrameRate(60.0f);
	settings->setWindowSize(800, 800);
}

void dodecaudionK20Visuals::setup()
{
	//init controllers
	genCtrl.setup();
	controllers.push_back( &genCtrl );
    
    oscCtrl.setup(10001);
    controllers.push_back( &oscCtrl );

    touchOscCtrl.setup(10000);
    controllers.push_back( &touchOscCtrl );
	
	fftCtrl.setup(64);
	controllers.push_back( &fftCtrl );
	
	midiCtrl.setup(0);
	controllers.push_back( &midiCtrl );
	
	//init drawable objects
	dode.setup();
	visualObjects.push_back( &dode );
	visualObjects.push_back( &fftVis );	
	
	
	//init filters
	shaderFlt.setup(loadResource(RES_GENERIC_FILTER_SHADER_VERT),loadResource(RES_GENERIC_FILTER_SHADER_FRAG));
	visualFilters.push_back( &shaderFlt );
	
	//init FBO
	fboFormat.setSamples(4);
	fboFormat.enableMipmapping(false);
	fboFormat.setCoverageSamples(16);
	fbo = gl::Fbo( getWindowWidth(), getWindowHeight(),fboFormat);
	
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
	gl::clear( Color(0,0,0) );

	//draw scene to FBO
	fbo.bindFramebuffer();
	
	cam.lookAt( Vec3f(20,0,-500) , Vec3f::zero() , Vec3f::yAxis() );
		
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::clear( Color( 0, 0, 0 ) ); 

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	gl::enableAdditiveBlending();
	glLoadIdentity();
	gl::setMatrices( cam );
		
	for( vector<Drawable *>::iterator vis = visualObjects.begin() ; vis != visualObjects.end() ; ++vis ){
		(*vis)->draw();
	}	
	fbo.unbindFramebuffer();


	//filter the FBO
	fbo.bindTexture(0);
	for( vector<Filter *>::iterator flt = visualFilters.begin() ; flt != visualFilters.end() ; ++flt ){
		(*flt)->bind();
	}
	
	
	//display the output FBO
	gl::setViewport( getWindowBounds() );
	gl::setMatricesWindow( getWindowSize() );
	gl::color( ColorAf( 1,1,1,1 ) );
	gl::drawSolidRect( getWindowBounds() );
	
	for( vector<Filter *>::iterator flt = visualFilters.begin() ; flt != visualFilters.end() ; ++flt ){
		(*flt)->unbind();
	}
	
	fbo.unbindTexture();
	
}

#pragma mark helper methods
	
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
	
	
#pragma mark Application event handlers
	
void dodecaudionK20Visuals::resize( ResizeEvent event )
{
	fbo = gl::Fbo( getWindowWidth(), getWindowHeight(), fboFormat );
	cam.setAspectRatio( getWindowAspectRatio() );
}

void dodecaudionK20Visuals::mouseDown( MouseEvent event )
{
}

void dodecaudionK20Visuals::keyDown( KeyEvent event ){
	char ch = event.getChar();
	if( ch == 'f' ){
		setFullScreen( !isFullScreen() );
		gl::clear(Color(0,0,0));
	}
}
	

CINDER_APP_BASIC( dodecaudionK20Visuals, RendererGl );
