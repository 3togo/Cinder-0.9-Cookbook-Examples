#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ci_nanovg_gl.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class NanoVgDemoApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    
    shared_ptr<nvg::Context> mCtx;
};

void NanoVgDemoApp::setup() {
    
    mCtx = make_shared<nvg::Context>(nvg::createContextGL());
    mCtx->createFont("roboto", getAssetPath("Roboto-Regular.ttf").string());
    
}

void NanoVgDemoApp::mouseDown( MouseEvent event ) {
    
}

void NanoVgDemoApp::update() {
    
}

void NanoVgDemoApp::draw() {
    
	gl::clear( Color( 1, 1, 1 ) );
    
    auto& vg = *mCtx;
    
    vg.beginFrame(getWindowSize(), getWindowContentScale());
    vg.beginPath();
    vg.roundedRect(10, 10, 300, 150, 3.0);
    vg.fillColor(Colorf(1.0, 0.0, 0.0));
    vg.fill();
    vg.endFrame();
    
    string mode = "NanoVG";
    vg.beginFrame(getWindowSize(), getWindowContentScale());
    vg.translate(10, getWindowHeight() - 10);
    vg.fontFace("roboto");
    vg.fontSize(24);
    vg.fillColor(Colorf::black());
    vg.text(vec2(), "Fps: " + to_string(getAverageFps()));
    vg.text(vec2(0, -20), "Mode: " + mode);
    vg.endFrame();
}

// NanoVG requires a stencil buffer in the main framebuffer and performs it's
// own anti-aliasing by default. Disable opengl's AA and enable stencil here
// to allow for this.
CINDER_APP(NanoVgDemoApp, RendererGl(RendererGl::Options().stencil().msaa(0)), [](App::Settings *settings) {
   settings->setHighDensityDisplayEnabled();
   settings->setMultiTouchEnabled();
})
