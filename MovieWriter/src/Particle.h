//
//  Particle.hpp
//  Particles1
//
//

#pragma once

class Particle {
    
public:
    Particle( const ci::vec2& position, float radius, float mass, float drag );
    
    void update();
    void draw();
    
    ci::vec2 position, prevPosition;
    ci::vec2 forces;
    float radius;
    float mass;
    float drag;
};

