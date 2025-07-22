#include "Utils.h"
#include <random>
#include <glm/geometric.hpp>

float Utils::LengthSquared(const glm::vec3& v)
{
    return glm::dot(v, v);
}

uint8_t Utils::FloatToByte255(float value)
{
    value = std::clamp(value, 0.0f, 1.0f);
    return static_cast<uint8_t>(255.999f * value);
}

double Utils::random_double()
{
    return std::rand() / (RAND_MAX + 1.0);
}

double Utils::random_double(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}