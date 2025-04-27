#include "Cylinder.hpp"
#include "Vector.hpp"

Cylinder::Cylinder(float x, float y, float z, float radius, float half_height, const std::string &name, Material *mat) : Volume(mat, name), _cx(x), _cy(y), _cz(z), _radius(radius), _half_height(half_height) { }

bool Cylinder::contains(float x, float y, float z) const {
    float dx = x - _cx, dy = y - _cy, dz = z - _cz;
    bool inHeight = (dz >= _cz - _half_height && dz <= _cz + _half_height);
    return ((dx * dx + dy * dy) <= (_radius * _radius)) && inHeight;
}

bool Cylinder::contains(const Particle& p) const {
    return contains(p.getPosition()[0], p.getPosition()[1], p.getPosition()[2]);
}

Boundary Cylinder::getNextBoundary(const Particle& p) const {
    const Linalg::Vector3 ray_origin(p.getPosition()[0], p.getPosition()[1], p.getPosition()[2]);
    Linalg::Vector3 ray_dir(p.getMomentum()[0], p.getMomentum()[1], p.getMomentum()[2]);
    ray_dir = ray_dir.norm(); // normalize the momentum vector

    const float ox = p.getPosition()[0];
    const float oy = p.getPosition()[1];
    const float oz = p.getPosition()[2];
    const float dx = p.getMomentum()[0];
    const float dy = p.getMomentum()[1];
    const float dz = p.getMomentum()[2];

    // Intersect with the curved side of the cylinder
    const float a = dx * dx + dy * dy;
    const float b = 2.0f * (dx * (ox - _cx) + dy * (oy - _cy));
    const float c = (ox - _cx) * (ox - _cx) + (oy - _cy) * (oy - _cy) - _radius * _radius;

    float t_side = std::numeric_limits<float>::max();
    const float discriminant = b * b - 4.0f * a * c;
    if (discriminant >= 0 && a != 0.0) { // a == 0 means particle is parallel to cylinder axis
        const float sqrt_disc = std::sqrt(discriminant);
        const float t1 = (-b - sqrt_disc) / (2.0f * a);
        const float t2 = (-b + sqrt_disc) / (2.0f * a);

        // Find the smallest positive t
        if (t1 > 1e-8) t_side = t1;
        else if (t2 > 1e-8) t_side = t2;
    }

    // Intersect with the caps (planes at cz +/- height/2)
    const float z_top = _cz + _half_height;
    const float z_bottom = _cz - _half_height;
    float t_cap = std::numeric_limits<float>::max();

    // Check intersection with bottom cap
    if (std::abs(dz) > 1e-8) { // avoid divide by zero
        float t_bot = (z_bottom - oz) / dz;
        if (t_bot > 1e-8) {
            float x_bot = ox + t_bot * dx;
            float y_bot = oy + t_bot * dy;
            float r2_bot = (x_bot - _cx)*(x_bot - _cx) + (y_bot - _cy)*(y_bot - _cy);
            if (r2_bot <= _radius * _radius + 1e-8) { // inside the disk
                t_cap = t_bot;
            }
        }

        // Check intersection with top cap
        float t_top = (z_top - oz) / dz;
        if (t_top > 1e-8) {
            float x_top = ox + t_top * dx;
            float y_top = oy + t_top * dy;
            float r2_top = (x_top - _cx)*(x_top - _cx) + (y_top - _cy)*(y_top - _cy);
            if (r2_top <= _radius * _radius + 1e-8) {
                if (t_top < t_cap) t_cap = t_top;
            }
        }
    }

    // Choose whichever happens first
    float t_exit = std::min(t_side, t_cap);

    Boundary bound;
    bound.x = ray_origin.x + t_exit * ray_dir.x;
    bound.y = ray_origin.y + t_exit * ray_dir.y;
    bound.z = ray_origin.z + t_exit * ray_dir.z;
    bound.distance = (ray_origin - Linalg::Vector3(bound.x, bound.y, bound.z)).mag(); // distance from the particle to the boundary

    return bound;
}
