#ifndef GEOMETRY_SPHERE_HPP
#define GEOMETRY_SPHERE_HPP

#include "Volume.hpp"

class Sphere : public Volume {
    public:
        Sphere(float x, float y, float z, float r, const std::string &name, Material *mat);
        bool contains(float x, float y, float z) const override;
        bool contains(const Particle& p) const override;
    private:
        float _radius; // radius of the sphere
        float _cx; // center x-coordinate
        float _cy; // center y-coordinate
        float _cz; // center z-coordinate
};

#endif

