#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/Texture.h"
#include <boost/lexical_cast.hpp>
#include "cinder/ImageIo.h"

#include "Drawable.h"
#include "Controller.h"
#include "Filter.h"

#include "GenericController.h"
//#include "OSCController.h"
#include "DodecaudionOSCController.h"
#include "TouchOSCController.h"
#include "FFTController.h"
//#include "MIDIController.h"
#include "MIDINanoKontrolController.h"
#include "MIDINanoPadController.h"

#include "CameraDrawer.h"
#include "Dodecahedron.h"
#include "FFTVisualiser.h"
#include "Grid.h"


#include "ShaderFilter.h"


#define RES_PASS_THRU_SHADER_VERT			CINDER_RESOURCE( ../resources/, passThru.vert, 128, GLSL )
#define RES_SIMPLE_NOISE_SHADER_FRAG		CINDER_RESOURCE( ../resources/, simpleNoise.frag, 129, GLSL )
#define RES_VIGNETTE_SHADER_FRAG			CINDER_RESOURCE( ../resources/, vignette.frag, 130, GLSL )
#define RES_INVERT_SHADER_FRAG				CINDER_RESOURCE( ../resources/, invert.frag, 131, GLSL )
#define RES_BLUR__HORIZONTAL_SHADER_FRAG	CINDER_RESOURCE( ../resources/, blur-horizontal.frag, 132, GLSL )
#define RES_BLUR__VERTICAL_SHADER_FRAG		CINDER_RESOURCE( ../resources/, blur-vertical.frag, 133, GLSL )
#define RES_MULTIPLY_SHADER_FRAG			CINDER_RESOURCE( ../resources/, multiply.frag, 134, GLSL )
#define RES_GLITCH_SHADER_FRAG				CINDER_RESOURCE( ../resources/, glitch.frag, 135, GLSL )
#define RES_PASS_THRU_SHADER_FRAG			CINDER_RESOURCE( ../resources/, passThru.frag, 136, GLSL )





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
	void updateFilterByController(Filter *flt , Controller *ctrl);
	
	vector<Controller *> controllers;
	vector<Drawable *> visualObjects;
	vector<Filter *> visualFilters;
	
	gl::Fbo::Format fboFormat;
	gl::Fbo	fbo;
	gl::Texture fboTexture;
	
	
	//controllers for input (OSC, MIDI, etc.)
	GenericController genCtrl;
    DodecaudionOSCController dodecaudionOscCtrl;
	TouchOSCController touchOscCtrl;
	FFTController fftCtrl;
	MIDINanoKontrolController midiCtrlKontrol;
	MIDINanoPadController midiCtrlPad;
	
	//visual stuff - drawn elements
	CameraDrawer cam;
	Dodecahedron dode;
	FFTVisualiser fftVis;
	Grid grid;
    
	ShaderFilter noiseFlt,vignetteFlt,glitchFlt,passThruFlt,invertFlt,blurVFlt,blurHFlt,multFlt;
	
};

#pragma mark CINDER_APP_BASIC methods
	
void dodecaudionK20Visuals::prepareSettings(Settings *settings){
	settings->setFrameRate(60.0f);
	settings->setWindowSize(1280, 720);
}

void dodecaudionK20Visuals::setup()
{
	//
	//init controllers
	//
	genCtrl.setup();
	controllers.push_back( &genCtrl );
    
    dodecaudionOscCtrl.setup(10000);
    controllers.push_back( &dodecaudionOscCtrl );

    touchOscCtrl.setup(10001);
    controllers.push_back( &touchOscCtrl );
	
	fftCtrl.setup(64);
	controllers.push_back( &fftCtrl );
	
	midiCtrlKontrol.setup("nanoKONTROL SLIDER/KNOB");
	controllers.push_back( &midiCtrlKontrol );

	midiCtrlPad.setup("nanoPAD PAD");
	controllers.push_back( &midiCtrlPad );
	
	//
	//init drawable objects
	//
	cam.setup();
	visualObjects.push_back( &cam );
	fftVis.setup();
	visualObjects.push_back( &fftVis );	
	//grid.setup();
	//visualObjects.push_back( &grid );	
	dode.setup();
	visualObjects.push_back( &dode );
	
	//
	//init filters
	//
	//
	//Important stuff: always add a %2 amount of filters. Otherwise output will be upside down.
	//
	invertFlt.setup("invert", loadResource(RES_PASS_THRU_SHADER_VERT),loadResource(RES_INVERT_SHADER_FRAG), getWindowSize());	
	visualFilters.push_back( &invertFlt );
	multFlt.setup("multiply", loadResource(RES_PASS_THRU_SHADER_VERT), loadResource(RES_MULTIPLY_SHADER_FRAG), getWindowSize());
	visualFilters.push_back( &multFlt );

	passThruFlt.setup("passThru", loadResource(RES_PASS_THRU_SHADER_VERT),loadResource(RES_PASS_THRU_SHADER_FRAG), getWindowSize());
	visualFilters.push_back( &passThruFlt );
	glitchFlt.setup("glitch", loadResource(RES_PASS_THRU_SHADER_VERT),loadResource(RES_GLITCH_SHADER_FRAG), getWindowSize());
	visualFilters.push_back( &glitchFlt );
	
	//Blur kills the GPU in fulscreen
	blurHFlt.setup("blur-horizontal", loadResource(RES_PASS_THRU_SHADER_VERT),loadResource(RES_BLUR__HORIZONTAL_SHADER_FRAG), getWindowSize());
	visualFilters.push_back( &blurHFlt );
	blurVFlt.setup("blur-vertical", loadResource(RES_PASS_THRU_SHADER_VERT),loadResource(RES_BLUR__VERTICAL_SHADER_FRAG), getWindowSize());
	visualFilters.push_back( &blurVFlt );

	vignetteFlt.setup("vignette", loadResource(RES_PASS_THRU_SHADER_VERT),loadResource(RES_VIGNETTE_SHADER_FRAG), getWindowSize());
	visualFilters.push_back( &vignetteFlt );
	noiseFlt.setup("noise", loadResource(RES_PASS_THRU_SHADER_VERT),loadResource(RES_SIMPLE_NOISE_SHADER_FRAG), getWindowSize());
	visualFilters.push_back( &noiseFlt );

	
	//
	//init FBO
	//
	fboFormat.setSamples(1);
	fboFormat.enableMipmapping(false);
	//fboFormat.setCoverageSamples(16);
	fbo = gl::Fbo( getWindowWidth(), getWindowHeight(),fboFormat);

	//pass the FBO to filters for later usage
	int counter = 0;
	for( vector<Filter *>::iterator flt = visualFilters.begin() ; flt != visualFilters.end() ; ++flt ){
		(*flt)->setFBO( &fbo );
	}
	
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
	
	//update all filters
	for( vector<Filter *>::iterator flt = visualFilters.begin() ; flt != visualFilters.end() ; ++flt ){
		for( vector<Controller *>::iterator ctrl = controllers.begin() ; ctrl != controllers.end() ; ++ctrl ){			
			//pass controller data to Drawable objects
			updateFilterByController( *flt, *ctrl );
		}				
		(*flt)->update();
	}

	//release all transitory vars if they were persisted
	for( vector<Controller *>::iterator ctrl = controllers.begin() ; ctrl != controllers.end() ; ++ctrl ){			
		(*ctrl)->releaseTransitory();
	}
	
}

/**
 * Draw the stage
 */
void dodecaudionK20Visuals::draw()
{
	gl::clear( Color(0,0,0) );

	//draw scene to FBO for later filter processing
	fbo.bindFramebuffer();
	
	//cam.lookAt( camPosition , Vec3f::zero() , -Vec3f::yAxis() );
		
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::clear( Color( 0, 0, 0 ) ); 

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
	
	//setup fog
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE,GL_EXP);
	glFogfv(GL_FOG_COLOR,Vec3f(0.0f,0.75f,0.0f));
	glFogf(GL_FOG_DENSITY,0.0004f);
	glHint(GL_FOG_HINT, GL_NICEST);
	
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glAlphaFunc(GL_GREATER, 0.5f);
	//glEnable(GL_ALPHA_TEST);
	//glEnable(GL_AUTO_NORMAL);
	
	//gl::enableAdditiveBlending();
	gl::enableAlphaBlending();
	glLoadIdentity();
		
	for( vector<Drawable *>::iterator vis = visualObjects.begin() ; vis != visualObjects.end() ; ++vis ){
		(*vis)->draw();
	}	
	
	fbo.unbindFramebuffer();


	gl::Texture tex = fbo.getTexture();
	//filter the FBO
	for( vector<Filter *>::iterator flt = visualFilters.begin() ; flt != visualFilters.end() ; ++flt ){
		(*flt)->apply(&tex);
	}	
	
	
	//draw the filtered output on the screen
	tex.enableAndBind();
	gl::setViewport( getWindowBounds() );
	gl::setMatricesWindow( getWindowSize() );
	gl::color( ColorAf( 1,1,1,1 ) );
	gl::drawSolidRect( getWindowBounds() );
	tex.unbind();
}

#pragma mark helper methods
	
/**
 * Perform updating of all Drawable+Controllable object by controllers. 
 * This is where mapping of Controller values to Drawable params is done
 * TODO: Replace this by some way of mapping the controls to visuals - maybe a file?
 */
void dodecaudionK20Visuals::updateDrawableByController(Drawable *vis , Controller *ctrl)
{

	//console() << ctrl->getId() << std::endl;
	//
	//generic controller updates
	//
	if( ctrl->getId() ==  "generic" ){
		vis->set( "framesCount" , ctrl->get("framesCount") );
		
		//update camera settings
		if( vis->getId() == "camera" ){
			//Vec3f camPosition = Vec3f( 500 * sin( getElapsedFrames() / 100.0f ) , 120 , -750 );	
			/*
			vis->set( "camPositionX" , camPosition.x );
			vis->set( "camPositionY" , camPosition.y );
			vis->set( "camPositionZ" , camPosition.z );
			 */
		}
		if( vis->getId() == "dodecahedron" ){
			//for testing only
			string wallId;
			for( int wall = 0 ; wall < WALL_COUNT ; wall++ ){
				wallId = "wall" + boost::lexical_cast<string>( wall );
				vis->set( wallId , ( (getElapsedFrames() - wall * 10) % 120 ) / 120.0f );
			}
		}
	}
	//
	//touchOSC controls mapping
	//
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
		if( vis->getId() == "camera" ){
			
			//START:: THIS IS FOR TESTING WITOUT MIDI
			if( ctrl->get( TOUCH_OSC_PUSH_BUTTON_1_1 , true ) > 0 ){
				vis->set( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_NEXT , 1 );
			}
			else if( ctrl->get( TOUCH_OSC_PUSH_BUTTON_1_5 , true ) > 0 ){
				vis->set( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_PREV , 1 );
			}
			else if( ctrl->get( TOUCH_OSC_PUSH_BUTTON_1_3 , true ) > 0 ){
				vis->set( DRAWABLE_CAMERA_FLAG_CAM_PREDEFINED_LOOP_START , 1 );
			}
			else if( ctrl->get( TOUCH_OSC_PUSH_BUTTON_1_2 , true ) > 0 ){
				vis->set( DRAWABLE_CAMERA_FLAG_CAM_PREDEFINED_LOOP_STOP , 1 );
			}
			
			//other variables
			vis->set( DRAWABLE_CAMERA_VAR_CAM_MOVEMENT_SPEED , ctrl->get( TOUCH_OSC_SLIDER_1_1 ) );
			vis->set( DRAWABLE_CAMERA_VAR_CAM_SHAKE_FACTOR , ctrl->get( TOUCH_OSC_SLIDER_1_2 ) );
			
			vis->set( DRAWABLE_CAMERA_VAR_FOV , ctrl->get( TOUCH_OSC_SLIDER_1_4 ) );			
			//END::THIS IS FOR TESTING WITOUT MIDI
		}
		//update grid
		if( vis->getId() == "grid" ){
			vis->set( DRAWABLE_GRID_VAR_BRIGTNESS , ctrl->get( TOUCH_OSC_SLIDER_1_1 ) );
			vis->set( DRAWABLE_GRID_VAR_CELL_SIZE , ctrl->get( TOUCH_OSC_SLIDER_1_1 ) );
			vis->set( DRAWABLE_GRID_VAR_WAVE_AMPLITUDE , ctrl->get( TOUCH_OSC_SLIDER_1_2 ) );
			vis->set( DRAWABLE_GRID_VAR_WAVE_FREQUENCY , ctrl->get( TOUCH_OSC_SLIDER_1_3 ) );
			vis->set( DRAWABLE_GRID_VAR_WAVE_FADEOUT_SPEED , ctrl->get( TOUCH_OSC_SLIDER_1_4 ) );
			vis->set( DRAWABLE_GRID_FLAG_START_WAVE , ctrl->get( TOUCH_OSC_PUSH_BUTTON_1_5 , true ) );
		}
	}
	//
	//FFT controls mapping
	//
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
	//Midi slider mapping
	if( ctrl->getId() == "midi:nanoKONTROL SLIDER/KNOB" ){
		if( vis->getId() == "camera" ){

			//switch between predefined positions
			if( ctrl->get( MIDI_KORG_NANO_KONTROL_BUTTON_FWD ) > 0 ){
				vis->set( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_NEXT , 1 );
			}
			else if( ctrl->get( MIDI_KORG_NANO_KONTROL_BUTTON_REW ) > 0 ){
				vis->set( DRAWABLE_CAMERA_FLAG_PREDEFINED_POS_PREV , 1 );
			}
			else if( ctrl->get( MIDI_KORG_NANO_KONTROL_BUTTON_LOOP ) > 0 ){
				vis->set( DRAWABLE_CAMERA_FLAG_CAM_PREDEFINED_LOOP_START , 1 );
			}
			else if( ctrl->get( MIDI_KORG_NANO_KONTROL_BUTTON_STOP ) > 0 ){
				vis->set( DRAWABLE_CAMERA_FLAG_CAM_PREDEFINED_LOOP_STOP , 1 );
			}
			
			//other variables
			vis->set( DRAWABLE_CAMERA_VAR_CAM_MOVEMENT_SPEED , ctrl->get( MIDI_KORG_NANO_KONTROL_SLIDER_1_1 ) );
			vis->set( DRAWABLE_CAMERA_VAR_CAM_SHAKE_FACTOR , ctrl->get( MIDI_KORG_NANO_KONTROL_KNOB_1_1 ) );

			vis->set( DRAWABLE_CAMERA_VAR_FOV , ctrl->get( MIDI_KORG_NANO_KONTROL_KNOB_1_2 ) );			
		}
	}
	
}
	
/**
 * Perform updating of all Filter+Controllable object by controllers. 
 * This is where mapping of Controller values to Filter params is done
 * TODO: Replace this by some way of mapping the controls to visuals - maybe a file?
 */
void dodecaudionK20Visuals::updateFilterByController(Filter *flt , Controller *ctrl)
{
	if( ctrl->getId() == "generic" ){
		flt->set( "framesCount" , ctrl->get( "framesCount" ) );
	}

	//MIDI: Nano Pad
	if( ctrl->getId() == "midi:nanoPAD PAD" ){
		if( flt->getId() == "invert" ){
			if( ctrl->get( MIDI_KORG_PAD_TRIGGER_1_6 ) > 0 ){
				flt->set( FILTER_SHADER_PARAM_1 , ctrl->get( MIDI_KORG_PAD_TRIGGER_1_6 ) );
			}
		}
	}
	
	//Midi slider mapping
	if( ctrl->getId() == "midi:nanoKONTROL SLIDER/KNOB" ){	
		//blur filters manipulation
		if( flt->getId() == "blur-horizontal" || flt->getId() == "blur-vertical" ){
			flt->set( FILTER_SHADER_PARAM_1 , pow( ctrl->get( MIDI_KORG_NANO_KONTROL_KNOB_1_8 ),4) );
			flt->set( FILTER_SHADER_PARAM_2 , pow( ctrl->get( MIDI_KORG_NANO_KONTROL_SLIDER_1_8 ),4) );
		}
		//glitch
		if( flt->getId() == "glitch" ){
			flt->set( FILTER_SHADER_PARAM_1 , pow( ctrl->get( MIDI_KORG_NANO_KONTROL_KNOB_1_7 ),4) );
			flt->set( FILTER_SHADER_PARAM_2 , pow( ctrl->get( MIDI_KORG_NANO_KONTROL_SLIDER_1_7 ),4) );
		}
		//vignette
		if( flt->getId() == "vignette" ){
			flt->set( FILTER_SHADER_PARAM_1 , 1.0 - pow( ctrl->get( MIDI_KORG_NANO_KONTROL_KNOB_1_9 ),4) );
		}		
		if( flt->getId() == "invert" ){
			//aply easing by slider
			flt->set( FILTER_SHADER_EASE_PARAM_1 , 1.0 - pow( ctrl->get( MIDI_KORG_NANO_KONTROL_SLIDER_1_6 ) , 3 ) );
		}
	}
	
}

#pragma mark Application event handlers
	
void dodecaudionK20Visuals::resize( ResizeEvent event )
{
	fbo = gl::Fbo( getWindowWidth(), getWindowHeight(), fboFormat );	
	cam.set( "aspectRatio" , getWindowAspectRatio() );
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
