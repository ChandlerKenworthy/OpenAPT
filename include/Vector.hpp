#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <iostream>

namespace Linalg {
    struct Vector3 {
        float x, y, z;

        Vector3() : x(0), y(0), z(0) {}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        Vector3 norm(); // get the unit vector
        void display() { std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl; };

        Vector3 operator+(const Vector3& other) const {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        Vector3 operator-(const Vector3& other) const {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        float dot(const Vector3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        float mag() const { return std::sqrtf(x * x + y * y + z * z); }

        Vector3 cross(const Vector3& other) const {
            return Vector3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            );
        }
    };
};

#endif