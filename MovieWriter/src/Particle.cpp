//
//  Particle.cpp
//  Particles1
//
//

#include "Particle.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;


void drawCircle(float cx, float cy, float r, int num_segments) {
    
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;
    
    float x = r;//we start at angle = 0
    float y = 0;
    
    gl::begin(GL_LINE_LOOP);
    for ( int ii = 0; ii < num_segments; ii++ ) {
        gl::vertex(x + cx, y + cy);
        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    gl::end();
}


Particle::Particle( const ci::vec2& position, float radius, float mass, float drag ) :
    position( position ),
    radius( radius ),
    mass( mass ),
    drag( drag ),
    prevPosition( position ),
    forces( ci::vec2() ) {
    
}

void Particle::update() {
    
    ci::vec2 temp = position;
    ci::vec2 vel = ( position - prevPosition ) * drag;
    position += vel + forces / mass;
    prevPosition = temp;
    forces = ci::vec2();
    
    radius -= radius / 24.0;
}

void Particle::draw() {
    
    drawCircle(position.x, position.y, radius, 200);
    
    
    //ci::gl::drawSolidCircle( position, radius );
}
