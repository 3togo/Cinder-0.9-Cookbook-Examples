//
//  ParticleSystem.cpp
//  Particles1
//
//

#include "ParticleSystem.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;


ParticleSystem::ParticleSystem() {
    
    particles.resize(180);
    generate(particles.begin(), particles.end(), [&] {
        float radius = randFloat(10, 100);
        float mass = 1.0;
        float drag = 1.0;
        auto position = vec2{ randFloat(), randFloat()} * vec2{ getWindowSize() };
        return make_shared<Particle>(position, radius, mass, drag);
    });
}

void ParticleSystem::update() {
    
    for ( auto const& particle: particles ) {
        particle->update();
    }
}

void ParticleSystem::draw() {
    
    for ( auto const& particle: particles ) {
        particle->draw();
    }
}

void ParticleSystem::addParticle(std::shared_ptr<Particle> particle) {
    
    particles.push_back(particle);
}

void ParticleSystem::destroyParticle(std::shared_ptr<Particle> particle) {
    
    particles.erase(std::remove(particles.begin(), particles.end(), particle), particles.end());
}
