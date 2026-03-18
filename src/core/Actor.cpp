#include "Actor.h"

void Actor::SetPosition(vec3 position)
{
    Position = position;
}

void Actor::SetRotation(const glm::quat& rotation)
{
    Rotation = rotation;
}

void Actor::SetRotation(const glm::mat3& rotation)
{
    Rotation = glm::quat_cast(rotation);
}
