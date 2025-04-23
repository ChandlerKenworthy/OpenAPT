#ifndef GEOMETRY_CYLINDER_HPP
#define GEOMETRY_CYLINDER_HPP

#include "Geometry.hpp"

// TODO: Add roation etc?
class Cylinder : public GeometryObject {
    public:
        Cylinder(float x, float y, float z, float radius, float half_height, const std::string &name, Material *mat);
        bool contains(float x, float y, float z) const override;
        bool contains(const Particle& p) const override;
    private:
        float _cx; // center x-coordinate
        float _cy; // center y-coordinate
        float _cz; // center z-coordinate
        float _radius; // radius of the cylinder
        float _half_height; // half height of the cylinder
};

#endif

