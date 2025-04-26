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
    Sphere *s = new Sphere(0.0f, 0.0f, 0.0f, 100.0f, "mySphere", &m);
    s->setDoesPhysics(true); // diable physics in the sphere
    world.add_object(s);
    //world.add_object(new Box(0.0f, 200.0f, 0.0f, 5.0f, 100.0f, 5.0f, "myBox", &m));

    Simulation sim(1, 10, &world);

    sim.setParticleType(0); // 0 = neutrons
    sim.setDisplayEachStep(false);
    //sim.displayConfig();

    sim.prepare("B:\\Documents\\Coding\\OpenAPT\\test.csv");
    sim.run();

    return 0;
}