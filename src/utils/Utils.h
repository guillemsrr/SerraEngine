// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Utils
{
public:
    static float LengthSquared(const glm::vec3& v);
    static uint8_t FloatToByte255(float value);
    static uint32_t ConvertToRGBA(const glm::vec4& color);
    
    static float RandomFloat();
    static float RandomInRange(float min, float max);
};