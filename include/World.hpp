#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include "Geometry.hpp"

class World {
    public:
        explicit World() = default;
        ~World() = default;
        void add_object(GeometryObject *obj); // add a geometry object to the world
        GeometryObject* get_volume(float x, float y, float z) const; // get the volume at the given coordinates
    private:
        std::vector<GeometryObject*> _objects; // list of geometry objects in the world
};

#endif