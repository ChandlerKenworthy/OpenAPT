#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <string>
#include "Material.hpp"
#include "Particle.hpp"
#include "Constants.hpp"

class Volume {
    public:
        Volume(Material *mat, const std::string &name) : _name(name), _material(mat) {}
        virtual bool contains(float x, float y, float z) const = 0;
        virtual bool contains(const Particle& p) const = 0;
        // virtual double distance_to_boundary(const Particle& p) const = 0;
        virtual ~Volume() = default;
        std::string getName() const { return _name; }
        Interaction getInteraction(const Particle& p) const; // use randomness + physics to pick an interaction if any based on incident particle energy and the type of material (cross-sections)...
    private:
        std::string _name;
        Material *_material;
};

#endif