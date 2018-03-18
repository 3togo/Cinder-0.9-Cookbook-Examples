//
//  ParticleSystem.hpp
//  Particles1
//
//

#pragma once

#include "Particle.h"

class ParticleSystem {
public:
    ParticleSystem();
    void update();
    void draw();
    
    void addParticle( std::shared_ptr<Particle> particle );
    void destroyParticle( std::shared_ptr<Particle> particle );
    
    std::vector<std::shared_ptr<Particle>> particles;
};

