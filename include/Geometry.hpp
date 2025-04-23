#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <string>
#include "Material.hpp"
#include "Particle.hpp"

class GeometryObject {
    public:
        GeometryObject(Material *mat, std::string &name) : _name(name), _material(mat) {}
        virtual bool contains(float x, float y, float z) const = 0;
        virtual bool contains(const Particle& p) const = 0;
        // virtual double distance_to_boundary(const Particle& p) const = 0;
        virtual ~GeometryObject() = default;
        std::string getName() const { return _name; }
    private:
        std::string _name;
        Material *_material;
};

#endif