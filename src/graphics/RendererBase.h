// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <imgui.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Camera.h"

class RendererBase
{
public:
    RendererBase(Camera* camera);
    virtual ~RendererBase() = default;

    virtual void RenderBackground();

    glm::vec3 FilterSurfaceColor(const glm::vec3& color, float audioEmission = 0.0f) const;
    glm::vec4 FilterSurfaceColor(const glm::vec4& color, float audioEmission = 0.0f) const;
    glm::vec3 GetAudioGlowColor(float energy = 1.0f) const;

    virtual ImU32 GetHUDColor();
    void SetViewPortSize(int new_width, int new_height);

protected:
    const Camera* _camera;
};
