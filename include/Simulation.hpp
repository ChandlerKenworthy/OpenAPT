#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <iostream>
#include <fstream>
#include "Constants.hpp"
#include "Particle.hpp"
#include "Material.hpp"
#include "World.hpp"

class Simulation {
    public:
        explicit Simulation(U64 nParticles, U64 nSteps, World *world);
        ~Simulation() { delete[] _particles; } // destructor to free memory

        // Must run these functions before the simulation starts
        void prepare(std::string filePath);
        void step(int iStep);
        void run();

        // Utility
        void displayConfig() const;

        // Getters

        // Setters
        void setParticleType(U8 type) { _particleType = type; };
        void setDisplayEachStep(bool display) { _verbose = display; };

    private:
        void saveTrackingData(int nStep);

        World *_world; // world to simulate
        Particle *_particles; // array of particles to simulate
        U64 _nParticles; // number of particles to simulate
        U64 _nSteps; // number of steps to simulate
        bool _usePointSource; // use point source or not
        U8 _particleType; // type of particle to simulate
        U8 _verbose; // display each step or not
        std::vector<TrackRecord> _trackingData; // for recording track data
        std::ofstream _trackFile;

};

#endif