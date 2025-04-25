#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <string>
#include "Material.hpp"
#include "Particle.hpp"
#include "Constants.hpp"

struct Boundary {
    Boundary() : x(0), y(0), z(0), distance(0) {}
    float x, y, z; // coordinates of the boundary
    float distance; // distance to the boundary
};

class Volume {
    public:
        Volume(Material *mat, const std::string &name) : _name(name), _material(mat) {}
        virtual bool contains(float x, float y, float z) const = 0;
        virtual bool contains(const Particle& p) const = 0;
        virtual Boundary getNextBoundary(const Particle& p) const = 0; // returns the next boundary the particle will hit
        virtual ~Volume() = default;
        std::string getName() const { return _name; }
        Interaction getInteraction(const Particle& p) const; // use randomness + physics to pick an interaction if any based on incident particle energy and the type of material (cross-sections)...
    private:
        std::string _name;
        Material *_material;
};

#endif