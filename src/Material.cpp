#include "Material.hpp"

Material::Material(std::string &name) : _name(name) {
    
}

float Material::getCrossSection(const float energy, Interaction interaction) const {
    // TODO: Implement the logic to return the cross-section based on the energy and interaction type
    return 0.1f;
}