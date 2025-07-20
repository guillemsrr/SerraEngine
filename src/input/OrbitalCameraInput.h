// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "InputBase.h"

class Camera;

class OrbitalCameraInput : public InputBase
{
public:
    explicit OrbitalCameraInput(Camera* const camera)
        : _camera(camera)
    {
    }

    void HandleEvent(const SDL_Event& event) override;

    bool IsMouseRotating() const
    {
        return _mouseRotating;
    }

private:
    bool _mouseRotating = false;
    Camera* _camera;
};