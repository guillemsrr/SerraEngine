// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "Camera.h"

class RendererBase
{
public:
    RendererBase(Camera* camera);

protected:
    Camera* _camera;
};