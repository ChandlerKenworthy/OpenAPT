#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Constants.hpp"

// Add pre-defined particles e.g. if you init with type=0 that is a neutron, type=1 is a proton, etc.

class Particle {
    public:
        Particle(); // creates an empty null particle at the origin of space
        Particle(U8 type, float pos[3], float mom[3]); // creates a particle of given type at the given position and momentum
        Particle(float mass, U8 q, float pos[3], float mom[3]); // creates a particle with given mass, charge, position and momentum

        // Getters
        float getEnergy() const;
        float getMass() const { return _mass; }
        U8 getCharge() const { return _q; }
        bool getIsAlive() const { return _alive; }
        const float* getPosition() const { return _pos; }
        const float* getMomentum() const { return _mom; }

        // Setters
        void setMass(float mass) { _mass = mass; }
        void setCharge(U8 q) { _q = q; }
        void setIsAlive(bool alive) { _alive = alive; }
        void setPosition(float pos[3]);
        void setMomentum(float mom[3]);

        // Other methods, mostly to be improved later
        void move(); // step the particle forward in time according to its momentum
        void apply(Interaction interaction); // apply the given interaction to the particle
        void moveTo(float x, float y, float z); // move the particle to the given position

    private:
        float _mass; // mass in MeV/c^2
        U8 _q; // charge in e
        float _pos[3]; // position in cartesian coordinates (mm)
        float _mom[3]; // momentum along each cartesian axis (MeV/c)
        bool _alive; // is the particle alive
};

#endif