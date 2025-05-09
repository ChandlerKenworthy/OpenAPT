#ifndef MATERIAL_HPP    
#define MATERIAL_HPP

#include <string>
#include "Constants.hpp"

class Material {
    public:
        // Contructor(s)
        Material(std::string &name);

        float getCrossSection(const float energy, Interaction interaction) const; // getss the macroscopic cross-section for the material at the given energy and interaction type
        std::string getName() const { return _name; }
    private:
        std::string _name; // Name of the material


};

#endif