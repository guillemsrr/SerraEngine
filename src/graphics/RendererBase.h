// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <imgui.h>
#include "Camera.h"

class RendererBase
{
public:
    RendererBase(Camera* camera);

    virtual void RenderBackground();

    virtual ImU32 GetHUDColor();
    void SetViewPortSize(int new_width, int new_height);

protected:
    Camera* _camera;
};