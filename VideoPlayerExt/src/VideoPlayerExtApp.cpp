#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/qtime/QuickTimeGl.h"
#include "cinder/params/Params.h"
#include "cinder/Utilities.h"
#include "cinder/ip/Grayscale.h"
#include "cinder/ip/Flip.h"
#include "CinderOpenCV.h" // not used yet!

using namespace ci;
using namespace ci::app;
using namespace std;

class VideoPlayerExtApp : public App {
    
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    static void prepareSettings( Settings *settings );
    
    qtime::MovieSurfaceRef    mMovie;
    SurfaceRef                mSurface;
    SurfaceRef                mDestSurface;
    
    float mMoviePosition, mPrevMoviePosition;
    float mMovieRate, mPrevMovieRate;
    float mMovieVolume, mPrevMovieVolume;
    bool mMoviePlay, mPrevMoviePlay;
    bool mMovieLoop, mPrevMovieLoop;
    bool mGrayscale;
    bool mFlipH;
    bool mFlipV;
    
    params::InterfaceGl mParams;
};

void VideoPlayerExtApp::prepareSettings( Settings *settings ) {
    
    settings->setWindowSize( 800, 600 );
    settings->setFullScreen( false );
    settings->setResizable( true );
}

void VideoPlayerExtApp::setup() {
    
    fs::path moviePath = getOpenFilePath();
    if( ! moviePath.empty() ) {
        try {
            mMovie = qtime::MovieSurface::create( moviePath );
            console() << "Dimensions:" << mMovie->getWidth() << " x " << mMovie->getHeight() << std::endl;
            console() << "Duration:  " << mMovie->getDuration() << " seconds" << std::endl;
            console() << "Frames:    " << mMovie->getNumFrames() << std::endl;
            console() << "Framerate: " << mMovie->getFramerate() << std::endl;
            console() << "Has audio: " << mMovie->hasAudio() << " Has visuals: " << mMovie->hasVisuals() << std::endl;
            mMovie->setLoop( true, true );
            mMovie->seekToStart();
            mMovie->play();
            setFrameRate(mMovie->getFramerate());
        }
        catch( ci::Exception &exc ) {
            console() << "Exception caught trying to load the movie from path: " << moviePath << ", what: " << exc.what() << std::endl;
            mMovie.reset();
        }
    }
    
    mMoviePosition = 0.0f;
    mPrevMoviePosition = mMoviePosition;
    mMovieRate = 1.0f;
    mPrevMovieRate = mMovieRate;
    mMoviePlay = true;
    mPrevMoviePlay = mMoviePlay;
    mMovieLoop = false;
    mPrevMovieLoop = mMovieLoop;
    mMovieVolume = 1.0f;
    mPrevMovieVolume = mMovieVolume;
    
    mParams = params::InterfaceGl("Movie Controller", vec2( 200, 300 ));
    if( mMovie ){
        string max = ci::toString( mMovie->getDuration());
        mParams.addParam("Position", &mMoviePosition, "min=0.0 max=" + max + " step=0.5");
        mParams.addParam("Rate", &mMovieRate, "step=0.01");
        mParams.addParam("Play/Pause", &mMoviePlay);
        mParams.addParam("Loop", &mMovieLoop);
        mParams.addParam("Grayscale", &mGrayscale);
        mParams.addParam("Flip V", &mFlipV);
        mParams.addParam("Flip H", &mFlipH);
        mParams.addParam("Volume", &mMovieVolume, "min=0.0 max=1.0 step=0.01");
    }
}

void VideoPlayerExtApp::mouseDown( MouseEvent event ) {
    
}

void VideoPlayerExtApp::update() {
    
    if (mMovie) {
        
        mSurface = mMovie->getSurface();
        if ( ! mSurface ) return;
        
        mDestSurface = Surface::create(*mSurface);
        
        if ( mGrayscale ) {
            ip::grayscale( *mSurface, &*mDestSurface );
        }
        
        if ( mFlipH ) {
            ip::flipHorizontal( &*mDestSurface );
        }
        
        if ( mFlipV ) {
            ip::flipVertical( &*mDestSurface );
        }
        
        if (mMoviePosition != mPrevMoviePosition) {
            mPrevMoviePosition = mMoviePosition;
            mMovie->seekToTime(mMoviePosition);
        } else {
            mMoviePosition = mMovie->getCurrentTime();
            mPrevMoviePosition = mMoviePosition;
        }
        if (mMovieRate != mPrevMovieRate) {
            mPrevMovieRate = mMovieRate;
            mMovie->setRate(mMovieRate);
        }
        if (mMoviePlay != mPrevMoviePlay) {
            mPrevMoviePlay = mMoviePlay;
            if( mMoviePlay ){
                mMovie->play();
            } else {
                mMovie->stop();
            }
        }
        if (mMovieLoop != mPrevMovieLoop ) {
            mPrevMovieLoop = mMovieLoop;
            mMovie->setLoop(mMovieLoop);
        }
        if (mMovieVolume != mPrevMovieVolume ) {
            mPrevMovieVolume = mMovieVolume;
            mMovie->setVolume(mMovieVolume);
        }
    }
}

void VideoPlayerExtApp::draw() {
    
    gl::clear( Color( 0, 0, 0 ) );
    gl::enableAlphaBlending( true );
    
    if( ( ! mMovie ) || ( ! mSurface ) ) return;
    
    Rectf frect = Rectf( mSurface->getBounds() ).getCenteredFit( getWindowBounds(), true );
    gl::draw( gl::Texture::create( *mDestSurface), frect );
    
    mParams.draw();
}

CINDER_APP( VideoPlayerExtApp, RendererGl, VideoPlayerExtApp::prepareSettings )
