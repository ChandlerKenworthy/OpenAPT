#include "Vector.hpp"
#include <cmath>

using namespace Linalg;

Vector3 Vector3::norm() {
    const float mag = this->mag();
    return Vector3(x / mag, y / mag, z / mag);
}