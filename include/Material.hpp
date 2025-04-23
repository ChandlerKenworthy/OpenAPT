#ifndef MATERIAL_HPP    
#define MATERIAL_HPP

#include <string>

class Material {
    public:
        // Contructor(s)
        Material(std::string &name, float sigma_t, float sigma_s, float sigma_a);

        // Setters
        void setSigmaT(float sigma_t) { _sigma_t = sigma_t; }
        void setSigmaS(float sigma_s) { _sigma_s = sigma_s; }
        void setSigmaA(float sigma_a) { _sigma_a = sigma_a; }

        // Getters
        float getSigmaT() const { return _sigma_t; }
        float getSigmaS() const { return _sigma_s; }
        float getSigmaA() const { return _sigma_a; }
        std::string getName() const { return _name; }
    private:
        std::string _name; // Name of the material
        float _sigma_t;  // Total cross-section
        float _sigma_s;  // Scattering cross-section
        float _sigma_a;  // Absorption cross-section


};

#endif