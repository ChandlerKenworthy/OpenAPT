#include "Cylinder.hpp"

Cylinder::Cylinder(float x, float y, float z, float radius, float half_height, const std::string &name, Material *mat) : Volume(mat, name), _cx(x), _cy(y), _cz(z), _radius(radius), _half_height(half_height) { }

bool Cylinder::contains(float x, float y, float z) const {
    float dx = x - _cx, dy = y - _cy, dz = z - _cz;
    bool inHeight = (dz >= _cz - _half_height && dz <= _cz + _half_height);
    return ((dx * dx + dy * dy + dz * dz) <= (_radius * _radius)) && inHeight;
}

bool Cylinder::contains(const Particle& p) const {
    return contains(p.getPosition()[0], p.getPosition()[1], p.getPosition()[2]);
}