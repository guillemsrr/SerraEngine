#include "Utils.h"

#include <glm/detail/func_geometric.inl>

float Utils::LengthSquared(const glm::vec3& v)
{
    return glm::dot(v, v);
}