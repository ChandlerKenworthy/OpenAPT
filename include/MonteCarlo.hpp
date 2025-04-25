#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include <random>

class MonteCarlo {
    public:
        MonteCarlo(unsigned int seed = std::random_device{}()) : _engine(seed), _dist(0.0, 1.0) {}
        float uniform() { return _dist(_engine); }
    private:
        std::mt19937 _engine;
        std::uniform_real_distribution<float> _dist;
};    

#endif