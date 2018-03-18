#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"
#include "cinder/qtime/AvfWriter.h"

#include "Particle.h"
#include "ParticleSystem.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class MovieWriterApp : public App {
    
  public:
	void setup() override;
	void update() override;
	void draw() override;
    
    qtime::MovieWriterRef mMovieExporter;
    const int maxFrames = 350;              // the app quits after writing n frames
    
    ParticleSystem* particleSystem;
    
    CueRef mCue;                            // this particle system is too basic, work around demonstrating the usage of a looping Cue
    void timerCalled();                     // re-initializes the particle system
};


void MovieWriterApp::setup() {
    
    fs::path path = getSaveFilePath();
    if ( ! path.empty() ) {
        auto format = qtime::MovieWriter::Format()
        .codec( qtime::MovieWriter::H264 )
        .fileType( qtime::MovieWriter::QUICK_TIME_MOVIE );
        mMovieExporter = qtime::MovieWriter::create( path, getWindowWidth(), getWindowHeight(), format );
    }
    
    particleSystem = new ParticleSystem();
    
    mCue = timeline().add( bind(&MovieWriterApp::timerCalled, this), timeline().getCurrentTime() + 0.4 );
    mCue->setDuration( 0.4 );
    mCue->setAutoRemove( false );
    mCue->setLoop();
}


void MovieWriterApp::timerCalled() {
    
    particleSystem = new ParticleSystem();
}


void MovieWriterApp::update() {
    
    particleSystem->update();
    
    if ( mMovieExporter && getElapsedFrames() > 1 && getElapsedFrames() < maxFrames )
        mMovieExporter->addFrame( copyWindowSurface() );
    else if ( mMovieExporter && getElapsedFrames() >= maxFrames ) {
        mMovieExporter->finish();
        mMovieExporter.reset();
        quit();
    }
}


void MovieWriterApp::draw() {
    
	gl::clear( Color( 0, 0, 0 ) );
    gl::setMatricesWindow( getWindowWidth(), getWindowHeight() );
    particleSystem->draw();
}


CINDER_APP (
    MovieWriterApp,
    RendererGl(RendererGl::Options().stencil().msaa(16)),
    [](App::Settings *settings) {
       settings->setFullScreen(true);
    }
)
