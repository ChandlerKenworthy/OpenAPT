#include "Simulation.hpp"
#include <iostream>

Simulation::Simulation(U64 nParticles, U64 nSteps, World *world) : _world(world), _nParticles(nParticles), _nSteps(nSteps), _usePointSource(true), _particleType(0), _verbose(0) {
    // Allocate memory for particles
    _particles = new Particle[nParticles];
}

void Simulation::prepare() {
    // Initialize particles with random positions and momenta
    for (U64 i = 0; i < _nParticles; ++i) {
        float pos[3] = {0.0f, 0.0f, 0.0f};
        float mom[3] = {0.0f, 14.0f, 0.0f};
        _particles[i] = Particle(_particleType, pos, mom);
    }
}

void Simulation::run() {
    // Run the simulation for the specified number of steps
    for (U64 nStep = 0; nStep < _nSteps; ++nStep) {
        step(nStep);
    }
}

void Simulation::step(int iStep) {
    // TODO: Save all tracking information
    if(_verbose == 1) {
        std::cout << "[Step " << iStep + 1 << "/" << _nSteps << "]" << std::endl;
        for (U64 i = 0; i < _nParticles; ++i) {
            std::cout << "Particle " << i + 1 << " position: (" << _particles[i].getPosition()[0] << ", " << _particles[i].getPosition()[1] << ", " << _particles[i].getPosition()[2] << ")" << std::endl;
        }
    }
    for (U64 i = 0; i < _nParticles; ++i) {
        if (_particles[i].getIsAlive()) {
            _particles[i].move(); // move the particle forward it time 1 ns
            Volume *obj = _world->get_volume(_particles[i].getPosition()[0], _particles[i].getPosition()[1], _particles[i].getPosition()[2]);
            if (obj == nullptr) { // somehow the particle is outside the world
                _particles[i].setIsAlive(false);
                std::cout << "Particle " << i + 1 << " is out of bounds and has been killed." << std::endl;
            } else {
                // does Monte-Carlo sampling to determine, which, if any physics interaction happens
                // based on the current volume (material) and the particle energy/direction
                Boundary bound = obj->getInteraction(_particles[i]); 
                if(bound.interact != Interaction::None) {
                    std::cout << "Particle " << i + 1 << " is interacting with the volume: " << obj->getName() << " with process " << (int)bound.interact << std::endl;
                    _particles[i].apply(bound.interact); 
                } else {
                    // Particle did not interact within the volume, so just jump it straight to the next boundary
                    std::cout << "No interaction happened, jumping to next boundary\n";
                    _particles[i].moveTo(bound.x, bound.y, bound.z);
                }
                std::cout << "Particle " << i + 1 << " is within the volume: " << obj->getName() << std::endl;
            }
        }
    }
}

void Simulation::displayConfig() const {
    std::cout << "Simulation Configuration:" << std::endl;
    std::cout << "Number of Particles: " << _nParticles << std::endl;
    std::cout << "Number of Steps: " << _nSteps << std::endl;
    std::cout << "Particle Type: " << static_cast<int>(_particleType) << std::endl;
}