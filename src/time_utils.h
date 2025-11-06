#pragma once
#include <chrono>

struct TimeStep {
    double dt;        // fixed engine dt (e.g., 1/120)
    double real;      // real frame time (optional)
};

inline double seconds(std::chrono::high_resolution_clock::duration d) {
    return std::chrono::duration<double>(d).count();
}
