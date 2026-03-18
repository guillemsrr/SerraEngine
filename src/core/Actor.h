// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <glm/fwd.hpp>
#include <glm/detail/type_quat.hpp>

#include <glm/gtc/quaternion.hpp>

using vec3 = glm::vec3;

class Actor
{
public:
    Actor() = default;
    virtual ~Actor() = default;

    vec3 Position = vec3(0.0f);
    glm::quat Rotation = glm::quat();
    vec3 Scale = vec3(1.0f);

    void SetPosition(vec3 position);
    void SetRotation(const glm::quat& rotation);
    void SetRotation(const glm::mat3& rotation);
};
