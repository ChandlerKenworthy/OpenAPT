#include "Sphere.hpp"

Sphere::Sphere(float x, float y, float z, float r, const std::string &name, Material *mat) : Volume(mat, name), _cx(x), _cy(y), _cz(z), _radius(r) { }

bool Sphere::contains(float x, float y, float z) const {
    float dx = x - _cx, dy = y - _cy, dz = z - _cz;
    return (dx * dx + dy * dy + dz * dz) <= (_radius * _radius);
}

bool Sphere::contains(const Particle& p) const {
    return contains(p.getPosition()[0], p.getPosition()[1], p.getPosition()[2]);
}