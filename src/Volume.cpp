#include "Volume.hpp"
#include "Constants.hpp"

Interaction Volume::getInteraction(const Particle& p) const {
    // some random logic to determine what type of interaction occurs

    // get cross-sections for each interaction from the material at the partilce energy
    // use the cross-sections to determine the probability of each interaction
    // use a random number to determine which interaction occurs
    // return the interaction type

    const float energy = p.getEnergy(); // MeV
    const float csAbsorb = _material->getCrossSection(energy, Interaction::Absorb);
    const float csScatter = _material->getCrossSection(energy, Interaction::Scatter);
    const float csFission = _material->getCrossSection(energy, Interaction::Fission);
    const float csTotal = csAbsorb + csScatter + csFission; 

    // sample from total cross-seciton, could also be Interaction::None

    return Interaction::None;
}