#include "Volume.hpp"
#include "MonteCarlo.hpp"
#include "Constants.hpp"

Interaction Volume::getInteraction(const Particle& p) const {
    const float energy = p.getEnergy(); // MeV
    const float csAbsorb = _material->getCrossSection(energy, Interaction::Absorb);
    const float csScatter = _material->getCrossSection(energy, Interaction::Scatter);
    const float csFission = _material->getCrossSection(energy, Interaction::Fission);
    const float csTotal = csAbsorb + csScatter + csFission; 

    MonteCarlo mc; // TODO: probably should be a member of the world or something rather than constantly making a new one every time
    const float r = mc.uniform(); // random number between 0 and 1

    const float interaction_distance = -std::log(r) / csTotal; // if cross-section is [cm^-1], distance is in cm
    const Boundary bound = getNextBoundary(p);

    // Interacts before it leaves this volume
    if(interaction_distance < bound.distance) {
        const float pAbsorb = csAbsorb / csTotal;
        const float pScatter = csScatter / csTotal;
        const float pFission = csFission / csTotal;

        const float p = mc.uniform(); // random number between 0 and 1
        if(p < pAbsorb) return Interaction::Absorb;
        if(p < pAbsorb + pScatter) return Interaction::Scatter;
        if(p < pAbsorb + pScatter + pFission) return Interaction::Fission;
    }

    return Interaction::None;
}