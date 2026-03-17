// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include <glm/vec4.hpp>

using color = glm::vec4;

namespace Colors {
    inline const color White       = color(1.0f, 1.0f, 1.0f, 1.0f);
    inline const color Black       = color(0.0f, 0.0f, 0.0f, 1.0f);
    inline const color Red         = color(1.0f, 0.0f, 0.0f, 1.0f);
    inline const color Green       = color(0.0f, 1.0f, 0.0f, 1.0f);
    inline const color Blue        = color(0.0f, 0.0f, 1.0f, 1.0f);
    inline const color Cyan        = color(0.0f, 1.0f, 1.0f, 1.0f);
    inline const color Magenta     = color(1.0f, 0.0f, 1.0f, 1.0f);
    inline const color Yellow      = color(1.0f, 1.0f, 0.0f, 1.0f);
    inline const color Gray        = color(0.5f, 0.5f, 0.5f, 1.0f);
    inline const color Transparent = color(0.0f, 0.0f, 0.0f, 0.0f);
}
