// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "InputBase.h"

class Camera;

class OrbitalCameraInput : public InputBase
{
protected:
    ~OrbitalCameraInput() = default;

public:
    explicit OrbitalCameraInput(Camera* const camera);

    void HandleEvent(const SDL_Event& event) override;

private:
    bool _mouseRotating = false;
    Camera* _camera;
};