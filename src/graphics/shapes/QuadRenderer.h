// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "ShapeRenderer.h"

class QuadRenderer : public ShapeRenderer
{
public:
    void Init() override;
    void Draw() override;
};