#include "Simulation.hpp"
#include <iostream>

Simulation::Simulation(U64 nParticles, U64 nSteps, World *world) : _world(world), _nParticles(nParticles), _nSteps(nSteps), _usePointSource(true), _particleType(0), _verbose(0) {
    // Allocate memory for particles
    _particles = new Particle[nParticles];
}

void Simulation::prepare(std::string filePath) {
    // Initialize particles with random positions and momenta
    for (U64 i = 0; i < _nParticles; ++i) {
        float pos[3] = {0.0f, 0.0f, 0.0f};
        float mom[3] = {0.0f, 14.0f, 0.0f};
        _particles[i] = Particle(_particleType, pos, mom);
    }

    std::cout << "[Simulation] " << _nParticles << " particles prepared\n";

    _trackFile.open(filePath);
    _trackFile << "id,step,x,y,z,px,py,pz\n"; // CSV header

    std::cout << "[Simulation] Data writing to " << filePath << "\n";

}

void Simulation::run() {
    // Run the simulation for the specified number of steps
    for (U64 nStep = 0; nStep < _nSteps; ++nStep) {
        step(nStep);
    }

    // Finished save the file
    _trackFile.close();
}

void Simulation::step(int iStep) {
    _trackingData.clear();
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
            } else {
                if(!obj->getDoesPhysics()) continue; // no physics interactions in this volume
                // does Monte-Carlo sampling to determine, which, if any physics interaction happens
                // based on the current volume (material) and the particle energy/direction
                Boundary bound = obj->getInteraction(_particles[i]); 
                if(bound.interact != Interaction::None) {
                    _particles[i].apply(bound.interact); 
                } else {
                    // Particle did not interact within the volume, so just jump it straight to the next boundary
                    _particles[i].moveTo(bound.x, bound.y, bound.z);
                }
            }
        }
        _trackingData.push_back(TrackRecord(
            _particles[i].getID(), _particles[i].getMass(), 
            _particles[i].getPosition()[0], _particles[i].getPosition()[1], _particles[i].getPosition()[2],
            _particles[i].getMomentum()[0], _particles[i].getMomentum()[1], _particles[i].getMomentum()[2]
        ));
    }
    // Save the tracking data for all particles after each step
    // saves I/O doing it for every particle
    saveTrackingData(iStep);
}

void Simulation::saveTrackingData(int nStep) {
    // id,step,x,y,z,px,py,pz
    for(const auto& record : _trackingData) {
        _trackFile << record.particleID << "," << nStep << "," <<
        record.x << "," << record.y << "," << record.z << "," <<
        record.px << "," << record.py << "," << record.pz << "\n";
    }
    _trackingData.clear();
}

void Simulation::displayConfig() const {
    std::cout << "Simulation Configuration:" << std::endl;
    std::cout << "Number of Particles: " << _nParticles << std::endl;
    std::cout << "Number of Steps: " << _nSteps << std::endl;
    std::cout << "Particle Type: " << static_cast<int>(_particleType) << std::endl;
}