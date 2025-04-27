#include "Volume.hpp"
#include "MonteCarlo.hpp"
#include "Constants.hpp"
#include <iostream>

Boundary Volume::getInteraction(const Particle& p) const {
    const float energy = p.getEnergy(); // MeV
    const float csAbsorb = _material->getCrossSection(energy, Interaction::Absorb);
    const float csScatter = _material->getCrossSection(energy, Interaction::Scatter);
    const float csFission = _material->getCrossSection(energy, Interaction::Fission);
    const float csTotal = csAbsorb + csScatter + csFission; 

    const float r = _rng.uniform(); // random number between 0 and 1

    const float interaction_distance = -std::log(r) / csTotal; // if cross-section is [cm^-1], distance is in cm

    // Boundary always has to be re-calculated. e.g. particle may have scattered and changed direction
    // but not left the current volume in the last step
    Boundary bound = getNextBoundary(p);

    // Interacts before it leaves this volume
    if(interaction_distance < bound.distance) {
        const float pAbsorb = csAbsorb / csTotal;
        const float pScatter = csScatter / csTotal;
        const float pFission = csFission / csTotal;
        const float p = _rng.uniform(); // random number between 0 and 1

        if(p < pAbsorb) {
            bound.interact = Interaction::Absorb;
        } else if(p > pAbsorb && p < pAbsorb + pScatter) {
            bound.interact = Interaction::Scatter;
        } else if(p > pAbsorb + pScatter && p < pAbsorb + pScatter + pFission) {
            bound.interact = Interaction::Fission;
        }
    }

    return bound;
}