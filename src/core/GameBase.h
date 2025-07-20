// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <SDL3/SDL_events.h>

namespace SerraEngine
{
    class GameBase
    {
    public:
        virtual ~GameBase() = default;

        virtual void Init() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void HandleEvent(const SDL_Event& e) = 0;
        virtual void Render() = 0;
        virtual void RenderHUD() = 0;
        virtual void Quit() = 0;
    };
}