#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include "Constants.hpp"
#include <random>

class MonteCarlo {
    public:
        MonteCarlo(unsigned int seed = std::random_device{}()) : _engine(seed), _longEngine(seed), _dist(0.0, 1.0), _int_dist(0, UINT64_MAX) {}
        
        float uniform() const { 
            return const_cast<std::uniform_real_distribution<float>&>(_dist)(
                const_cast<std::mt19937&>(_engine)
            );
        }
    
        U64 random_id() const {
            return const_cast<std::uniform_int_distribution<uint64_t>&>(_int_dist)(
                const_cast<std::mt19937_64&>(_longEngine)
            );
        }

    private:
        mutable std::mt19937 _engine;
        mutable std::mt19937_64 _longEngine;
        mutable std::uniform_real_distribution<float> _dist;
        mutable std::uniform_int_distribution<uint64_t> _int_dist;
};    

#endif