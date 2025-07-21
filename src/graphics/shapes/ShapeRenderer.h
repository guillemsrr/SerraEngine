// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

class ShapeRenderer
{
protected:
    unsigned int VAO = 0, VBO = 0, EBO = 0;

    virtual void Init() = 0;
    virtual void Draw() = 0;
    virtual void Cleanup();
};