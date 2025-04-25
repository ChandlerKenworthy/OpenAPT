#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstdint>

// Timestep granularity
constexpr float dt = 1e-9f; // nanoseconds

// Conversions
constexpr double SPEED_OF_LIGHT_MM_PER_NS = 299792458.0f / 1e6f; // mm/ns
constexpr double SPEED_OF_LIGHT_MM_PER_DT = (299792458.0f * 1.0e-9f) * 1.0e+3; // mm/ns

// Type definitions
typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

// Physics constants
constexpr double MASS_NEUTRON = 939.5654205f; // MeV/c^2
constexpr double MASS_PROTON = 938.27208816f; // MeV/c^2
constexpr double MASS_ELECTRON = 0.5109989461f; // MeV/c^2
constexpr double SPEED_OF_LIGHT = 299792458.0f; // m/s

// Interactions
enum class Interaction {
    Scatter,
    Absorb,
    Fission,
    None
};

#endif