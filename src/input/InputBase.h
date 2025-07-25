﻿// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <SDL3/SDL_events.h>

class InputBase
{
protected:
    ~InputBase() = default;

public:
    virtual void HandleEvent(const SDL_Event& event) = 0;
};