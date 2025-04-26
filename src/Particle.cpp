#include "Particle.hpp"
#include "MonteCarlo.hpp"
#include <cmath>

Particle::Particle(float mass, U8 q, float pos[3], float mom[3]) : _mass(mass), _q(q), _alive(true) {
    // Initialize position and momentum
    for (int i = 0; i < 3; ++i) {
        _pos[i] = pos[i];
        _mom[i] = mom[i];
    }
    _id = MonteCarlo(std::random_device{}()).random_id();
}

Particle::Particle() : _mass(0), _q(0), _alive(true) {
    // Initialize position and momentum to zero
    for (int i = 0; i < 3; ++i) {
        _pos[i] = 0.0f;
        _mom[i] = 0.0f;
    }
    _id = MonteCarlo(std::random_device{}()).random_id();
}

Particle::Particle(U8 type, float pos[3], float mom[3]) : _alive(true) {
    // Initialize mass and charge based on particle type
    switch (type) {
        case 0: // neutron
            _mass = MASS_NEUTRON;
            _q = 0;
            break;
        case 1: // proton
            _mass = MASS_PROTON;
            _q = 1;
            break;
        case 2: // electron
            _mass = MASS_ELECTRON;
            _q = -1;
            break;
        default:
            _mass = 0.0f;
            _q = 0;
            break;
    }

    // Initialize position and momentum
    for (int i = 0; i < 3; ++i) {
        _pos[i] = pos[i];
        _mom[i] = mom[i];
    }
    _id = MonteCarlo(std::random_device{}()).random_id();
}

void Particle::setPosition(float pos[3]) {
    for (int i = 0; i < 3; ++i) {
        _pos[i] = pos[i];
    }
}

void Particle::setMomentum(float mom[3]) {
    for (int i = 0; i < 3; ++i) {
        _mom[i] = mom[i];
    }
}

float Particle::getEnergy() const {
    // Calculate the energy of the particle using E = sqrt(p^2c^2 + m^2c^4)
    float p_squared = 0.0;
    for (int i = 0; i < 3; ++i) {
        p_squared += _mom[i] * _mom[i];
    }
    float m_squared = _mass * _mass;
    return sqrtf(p_squared + m_squared);
}

void Particle::moveTo(float x, float y, float z) {
    // Move the particle to the specified position
    _pos[0] = x;
    _pos[1] = y;
    _pos[2] = z;
}

void Particle::move() {
    // Move the particle forward in time according to its momentum
    const float energy = getEnergy();
    float v[3]; 
    v[0] = _mom[0] / energy; // units of speed of light
    v[1] = _mom[1] / energy; // units of speed of light
    v[2] = _mom[2] / energy; // units of speed of light

    for (int i = 0; i < 3; ++i) {
        _pos[i] += v[i] * SPEED_OF_LIGHT_MM_PER_DT;
    }
}

void Particle::apply(Interaction interaction) {
    // TODO: switch on the interaction type and apply physics appropriately...
    switch (interaction) {
        case Interaction::Absorb:
            _alive = false; // Particle is absorbed
            break;
        case Interaction::Scatter:
            _mom[0] *= 0.5f;
            _mom[1] *= 0.5f;
            break;
        case Interaction::Fission:
            _alive = false; // Particle is fissioned
            break;
        default:
            break; // No interaction
    }
}