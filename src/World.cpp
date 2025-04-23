#include "World.hpp"

void World::add_object(GeometryObject *obj) {
    _objects.push_back(obj);
}

GeometryObject* World::get_volume(float x, float y, float z) const {
    // Determine the volume at the given coordinates, could be none or multiple

    // TODO: This is slow and nasty, instead use some sort of hashmap and spatial partitioning
    for (const auto& obj : _objects) {
        if (obj->contains(x, y, z)) {
            return obj;
        }
    }
    return nullptr; // No object found at the given coordinates   
}