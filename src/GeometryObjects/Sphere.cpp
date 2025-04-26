#include "Sphere.hpp"
#include "Vector.hpp"

Sphere::Sphere(float x, float y, float z, float r, const std::string &name, Material *mat) : Volume(mat, name), _cx(x), _cy(y), _cz(z) {
    if (r <= 0.0f) {
        throw std::invalid_argument("Sphere '" + name + "' radius must be positive.");
    }
    _radius = r;
}

bool Sphere::contains(float x, float y, float z) const {
    float dx = x - _cx, dy = y - _cy, dz = z - _cz;
    return (dx * dx + dy * dy + dz * dz) <= (_radius * _radius);
}

bool Sphere::contains(const Particle& p) const {
    return contains(p.getPosition()[0], p.getPosition()[1], p.getPosition()[2]);
}

Boundary Sphere::getNextBoundary(const Particle& p) const {
    // Find the position on the sphere where the particle will next hit assuming
    // it is moving in a straight line along its momentum vector

    const Linalg::Vector3 ray_origin(p.getPosition()[0], p.getPosition()[1], p.getPosition()[2]);
    Linalg::Vector3 ray_dir(p.getMomentum()[0], p.getMomentum()[1], p.getMomentum()[2]);
    ray_dir = ray_dir.norm(); // normalize the momentum vector
    const Linalg::Vector3 sphere_center(_cx, _cy, _cz);

    Linalg::Vector3 oc = ray_origin - sphere_center;
    float b = 2.0 * ray_dir.dot(oc);
    float c = oc.dot(oc) - _radius * _radius;
    float discriminant = b * b - 4.0 * c;
    
    // If discrimiant is negative, the ray does not intersect the sphere
    // but this is forced to be true as the particle is guaranteed within the volume

    float sqrt_disc = std::sqrt(discriminant);
    float t1 = (-b - sqrt_disc) * 0.5;
    float t2 = (-b + sqrt_disc) * 0.5;

    float t = t1 > t2 ? t1 : t2; // take the larger more positive root

    Boundary bound;
    bound.x = ray_origin.x + t * ray_dir.x;
    bound.y = ray_origin.y + t * ray_dir.y;
    bound.z = ray_origin.z + t * ray_dir.z;
    bound.distance = (ray_origin - Linalg::Vector3(bound.x, bound.y, bound.z)).mag(); // distance from the particle to the boundary

    return bound;
}