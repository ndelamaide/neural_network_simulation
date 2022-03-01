#include "random.h"

RandomNumbers::RandomNumbers(unsigned long int _seed) {
    initialize(_seed);
}

void RandomNumbers::initialize(unsigned long int _seed) {
    seed = _seed;
    if (seed == 0) {
        std::random_device rd;
        seed = rd();
    }
    rng = std::mt19937(seed);
}

double RandomNumbers::uniform_double(double lower, double upper) {
    std::uniform_real_distribution<> unif(lower, upper);
    return unif(rng);
}

double RandomNumbers::normal(double mean, double sd) {
    std::normal_distribution<> norm(mean, sd);
    return norm(rng);
}

int RandomNumbers::poisson(double mean) {
    std::poisson_distribution<> pois(mean);
    return pois(rng);
}
