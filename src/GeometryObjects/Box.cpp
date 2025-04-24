#include "Box.hpp"

Box::Box(float x, float y, float z, float half_width_x, float half_width_y, float half_width_z, const std::string &name, Material *mat) : Volume(mat, name), _cx(x), _cy(y), _cz(z), _hwx(half_width_x), _hwy(half_width_y), _hwz(half_width_z) { }

bool Box::contains(float x, float y, float z) const {
    return (x >= _cx - _hwx && x <= _cx + _hwx &&
            y >= _cy - _hwy && y <= _cy + _hwy &&
            z >= _cz - _hwz && z <= _cz + _hwz);
}

bool Box::contains(const Particle& p) const {
    return contains(p.getPosition()[0], p.getPosition()[1], p.getPosition()[2]);
}