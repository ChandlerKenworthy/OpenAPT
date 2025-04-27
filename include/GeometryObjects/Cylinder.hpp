#ifndef GEOMETRY_CYLINDER_HPP
#define GEOMETRY_CYLINDER_HPP

#include "Volume.hpp"

// TODO: Add roation etc?
// For now cylinder is AIXS ALIGNED i.e. particles by default travel along the z-axis and this is along the z-axis
class Cylinder : public Volume {
    public:
        Cylinder(float x, float y, float z, float radius, float half_height, const std::string &name, Material *mat);
        bool contains(float x, float y, float z) const override;
        bool contains(const Particle& p) const override;
        Boundary getNextBoundary(const Particle& p) const override;
    private:
        float _cx; // center x-coordinate
        float _cy; // center y-coordinate
        float _cz; // center z-coordinate
        float _radius; // radius of the cylinder
        float _half_height; // half height of the cylinder
};

#endif

