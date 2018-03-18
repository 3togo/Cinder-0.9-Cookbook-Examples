#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ImageInvertApp : public App {
    
  public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void update() override;
	void draw() override;
    
    void invert();
    
    Surface32f mSurface;
    params::InterfaceGl mParams;
    bool mInverted;
};

void ImageInvertApp::setup() {
    
    mParams = params::InterfaceGl("Parameters", vec2(200,400));
    mParams.addButton("Invert", std::bind(&ImageInvertApp::invert, this));
    auto img = loadImage( loadAsset( "image1.jpg" ) );
    mSurface = Surface32f(img);
}

void ImageInvertApp::mouseDown(MouseEvent event) {
    
}

void ImageInvertApp::update() {
    
}

void ImageInvertApp::invert() {
    
    Area area( 0, 0, mSurface.getWidth(), mSurface.getHeight());
    Surface32f::Iter iter = mSurface.getIter(area);
    while (iter.line()) {
        while (iter.pixel()) {
            iter.r() = 1.0 - iter.r();
            iter.g() = 1.0 - iter.g();
            iter.b() = 1.0 - iter.b();
        }
    }
}

void ImageInvertApp::draw() {
    
    gl::clear(Color(0, 0, 0));
    gl::draw( gl::Texture2d::create(mSurface), getWindowBounds());
    mParams.draw();
}

CINDER_APP(ImageInvertApp, RendererGl)
