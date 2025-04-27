#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <string>
#include "MonteCarlo.hpp"
#include "Material.hpp"
#include "Particle.hpp"
#include "Constants.hpp"

struct Boundary {
    Boundary() : x(0), y(0), z(0), distance(0), interact(Interaction::None) {}
    float x, y, z; // coordinates of the boundary
    float distance; // distance to the boundary
    Interaction interact; // type of interaction at the boundary
};

class Volume {
    public:
        Volume(Material *mat, const std::string &name) : _name(name), _material(mat), _rng(std::random_device{}()), _doesPhysics(true), _id(_rng.random_id()) { }
        virtual bool contains(float x, float y, float z) const = 0;
        virtual bool contains(const Particle& p) const = 0;
        virtual Boundary getNextBoundary(const Particle& p) const = 0; // returns the next boundary the particle will hit
        virtual ~Volume() = default;
        std::string getName() const { return _name; }
        Boundary getInteraction(const Particle& p) const; // use randomness + physics to pick an interaction if any based on incident particle energy and the type of material (cross-sections)...
        void setDoesPhysics(bool doesPhysics) { _doesPhysics = doesPhysics; } // set whether this volume has physics interactions
        bool getDoesPhysics() const { return _doesPhysics; } // get whether this volume has physics interactions
        U64 getID() { return _id; }
    private:
        U64 _id;
        std::string _name;
        Material *_material;
        MonteCarlo _rng;
        bool _doesPhysics; // does this volume have physics interactions
};

#endif