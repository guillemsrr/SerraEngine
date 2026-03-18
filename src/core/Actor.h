// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <glm/fwd.hpp>
#include <glm/detail/type_quat.hpp>

#include <glm/gtc/quaternion.hpp>

class Actor
{
public:
    Actor() = default;
    virtual ~Actor() = default;

    glm::vec3 Position = glm::vec3(0.0f);
    glm::quat Rotation = glm::quat();
    glm::vec3 Scale = glm::vec3(1.0f);

    void SetRotation(const glm::quat& rotation) { Rotation = rotation; }
    void SetRotation(const glm::mat3& rotation) { Rotation = glm::quat_cast(rotation); }
};
