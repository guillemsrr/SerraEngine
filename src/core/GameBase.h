// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <imgui.h>

#include <SDL3/SDL_events.h>

namespace SerraEngine
{
    class GameBase
    {
    public:
        virtual ~GameBase() = default;

        virtual void Init(SDL_Window* window);
        virtual void Update(float deltaTime) = 0;
        virtual void HandleEvent(const SDL_Event& e) = 0;
        virtual void Render() = 0;
        virtual void RenderHUD();
        virtual void Quit() = 0;

    protected:
        SDL_Window* _window = nullptr;
        
        virtual ImU32 GetHUDColor();
        virtual void RenderUI() = 0;
    };
}