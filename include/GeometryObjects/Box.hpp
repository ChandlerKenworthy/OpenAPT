#ifndef GEOMETRY_BOX_HPP
#define GEOMETRY_BOX_HPP

#include "Geometry.hpp"

class Box : public GeometryObject {
    public:
        Box(float x, float y, float z, float half_width_x, float half_width_y, float half_width_z, const std::string &name, Material *mat);
        bool contains(float x, float y, float z) const override;
        bool contains(const Particle& p) const override;
    private:
        float _cx; // center x-coordinate
        float _cy; // center y-coordinate
        float _cz; // center z-coordinate
        float _hwx; // half width in x-direction
        float _hwy; // half width in y-direction
        float _hwz; // half width in z-direction
};

#endif

