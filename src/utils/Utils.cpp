#include "Utils.h"
#include <random>
#include <glm/geometric.hpp>

float Utils::LengthSquared(const glm::vec3& v)
{
    return glm::dot(v, v);
}

uint8_t Utils::FloatToByte255(float value)
{
    return static_cast<uint8_t>(255.999f * value);
}

uint32_t Utils::ConvertToRGBA(const glm::vec4& color)
{
    uint8_t r = FloatToByte255(color.r);
    uint8_t g = FloatToByte255(color.g);
    uint8_t b = FloatToByte255(color.b);
    uint8_t a = FloatToByte255(color.a);

    return (a << 24) | (b << 16) | (g << 8) | r;
}

float Utils::RandomFloat()
{
    return std::rand() / (RAND_MAX + 1.0);
}

float Utils::RandomInRange(float min, float max)
{
    return min + (max - min) * RandomFloat();
}