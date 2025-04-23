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
        float mom[3] = {0.0f, 100.0f, 0.0f};
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
    if(_verbose == 1) {
        std::cout << "[Step " << iStep + 1 << "/" << _nSteps << "]" << std::endl;
        for (U64 i = 0; i < _nParticles; ++i) {
            std::cout << "Particle " << i + 1 << " position: (" << _particles[i].getPosition()[0] << ", " << _particles[i].getPosition()[1] << ", " << _particles[i].getPosition()[2] << ")" << std::endl;
        }
    }
    for (U64 i = 0; i < _nParticles; ++i) {
        if (_particles[i].getIsAlive()) {
            _particles[i].move();
            // TODO: For now just kill the particle if it goes out of bounds of the world i.e. not in a GeometryObject
            // this should be updated to interact based on the material of the GeometryObject it is bound within
            GeometryObject *obj = _world->get_volume(_particles[i].getPosition()[0], _particles[i].getPosition()[1], _particles[i].getPosition()[2]);
            if (obj == nullptr) {
                _particles[i].setIsAlive(false);
                std::cout << "Particle " << i + 1 << " is out of bounds and has been killed." << std::endl;
                // TODO: Save all tracking information
            } else {
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