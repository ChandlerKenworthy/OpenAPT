#include "Box.hpp"
#include "Vector.hpp"

Box::Box(float x, float y, float z, float half_width_x, float half_width_y, float half_width_z, const std::string &name, Material *mat) : Volume(mat, name), _cx(x), _cy(y), _cz(z), _hwx(half_width_x), _hwy(half_width_y), _hwz(half_width_z) { }

bool Box::contains(float x, float y, float z) const {
    return (x >= _cx - _hwx && x <= _cx + _hwx &&
            y >= _cy - _hwy && y <= _cy + _hwy &&
            z >= _cz - _hwz && z <= _cz + _hwz);
}

bool Box::contains(const Particle& p) const {
    return contains(p.getPosition()[0], p.getPosition()[1], p.getPosition()[2]);
}

Boundary Box::getNextBoundary(const Particle& p) const {
    // TODO: Will need some updates for rotated (non-axis aligned) boxes
    const Linalg::Vector3 ray_origin(p.getPosition()[0], p.getPosition()[1], p.getPosition()[2]);
    Linalg::Vector3 ray_dir(p.getMomentum()[0], p.getMomentum()[1], p.getMomentum()[2]);
    ray_dir = ray_dir.norm(); // normalize the direction

    const float min_x = _cx - _hwx;
    const float max_x = _cx + _hwx;
    const float min_y = _cy - _hwy;
    const float max_y = _cy + _hwy;
    const float min_z = _cz - _hwz;
    const float max_z = _cz + _hwz;

    float tmin = (min_x - ray_origin.x) / ray_dir.x;
    float tmax = (max_x - ray_origin.x) / ray_dir.x;
    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (min_y - ray_origin.y) / ray_dir.y;
    float tymax = (max_y - ray_origin.y) / ray_dir.y;
    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return Boundary(); // Should not happen

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (min_z - ray_origin.z) / ray_dir.z;
    float tzmax = (max_z - ray_origin.z) / ray_dir.z;
    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return Boundary(); // Should not happen

    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    // tmin is now the distance along the ray to the nearest boundary
    float t = tmin > 0.0f ? tmin : tmax; // pick the positive root

    Boundary bound;
    bound.x = ray_origin.x + t * ray_dir.x;
    bound.y = ray_origin.y + t * ray_dir.y;
    bound.z = ray_origin.z + t * ray_dir.z;
    bound.distance = (ray_origin - Linalg::Vector3(bound.x, bound.y, bound.z)).mag();

    return bound;
}
