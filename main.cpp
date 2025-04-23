#include <iostream>
#include <string>

#include "World.hpp"
#include "Sphere.hpp"
#include "Simulation.hpp"
#include "Material.hpp"

int main() {
    
    std::string name = "Si";
    Material m(name, 0.1f, 0.2f, 0.3f);
    World world;
    std::string volumeName = "Sphere";
    world.add_object(new Sphere(0.0f, 0.0f, 0.0f, 100.0f, volumeName, &m));

    Simulation sim(1, 10, &world);

    sim.setParticleType(0); // 0 = neutrons
    sim.setDisplayEachStep(true);
    //sim.displayConfig();

    sim.prepare();
    sim.run();


    return 0;
}