#include <iostream>
#include <string>

#include "World.hpp"
#include "Sphere.hpp"
#include "Simulation.hpp"
#include "Material.hpp"
#include "Vector.hpp"

int main() {
    

    std::string name = "Si";
    Material m(name);
    World world;
    world.add_object(new Sphere(0.0f, 0.0f, 0.0f, 100.0f, "mySphere", &m));
    //world.add_object(new Box(0.0f, 200.0f, 0.0f, 5.0f, 100.0f, 5.0f, "myBox", &m));

    Simulation sim(1, 10, &world);

    sim.setParticleType(0); // 0 = neutrons
    sim.setDisplayEachStep(true);
    //sim.displayConfig();

    sim.prepare();
    sim.run();

    return 0;
}