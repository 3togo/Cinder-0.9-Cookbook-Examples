#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "OcvVideo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class OcvVideoPlayerApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    gl::Texture2dRef    mTexture    = nullptr;
    OcvVideoPlayer      mVideoPlayer;
    float               mPlayhead    = 0.0f;
};

void OcvVideoPlayerApp::setup() {   
    
    
    const fs::path filepath = getOpenFilePath();
    if ( mVideoPlayer.load( filepath ) ) {
        console() << mVideoPlayer.getFilePath() << " loaded successfully: ";
        
        console() << " > Codec: "        << mVideoPlayer.getCodec() << endl;
        console() << " > Duration: "    << mVideoPlayer.getDuration() << endl;
        console() << " > FPS: "        << mVideoPlayer.getFrameRate() << endl;
        console() << " > Num frames: "    << mVideoPlayer.getNumFrames() << endl;
        console() << " > Size: "        << mVideoPlayer.getSize() << endl;
        
        const ivec2& sz = mVideoPlayer.getSize();
        setWindowSize( sz );
        setWindowPos( ( getDisplay()->getSize() - sz ) / 2 );
        mVideoPlayer.play();
    } else {
        console() << "Unable to load movie" ;
        quit();
    }
    
}

void OcvVideoPlayerApp::mouseDown( MouseEvent event ) {
    
}

void OcvVideoPlayerApp::update() {
    
    if ( mVideoPlayer.update() ) {
        Surface8uRef s = mVideoPlayer.createSurface();
        if ( s != nullptr ) {
            mTexture = gl::Texture2d::create( *s );
        }
    }
}

void OcvVideoPlayerApp::draw() {
    
    gl::setMatricesWindow( getWindowSize() );
    gl::clear();
    
    if ( mTexture != nullptr ) {
        gl::draw( mTexture, mTexture->getBounds(), getWindowBounds() );
    }
}

CINDER_APP( OcvVideoPlayerApp, RendererGl )
