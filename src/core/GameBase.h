// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <vector>

#include "graphics/Camera.h"
#include "graphics/RendererBase.h"

#include "input/InputBase.h"

#include <SDL3/SDL_events.h>

namespace SerraEngine
{
    class GameBase
    {
    public:
        GameBase();
        virtual ~GameBase() = default;

        virtual void Init(SDL_Window* window);
        virtual void Update(float deltaTime) = 0;
        virtual void HandleEvent(const SDL_Event& e);
        virtual void Render() = 0;
        virtual void RenderHUD();
        virtual void Quit() = 0;

    protected:
        SDL_Window* _window = nullptr;
        Camera* _camera;
        RendererBase _rendererBase;

        virtual void RenderUI() = 0;

        void AddInputHandler(InputBase* inputHandler);

    private:
        std::vector<InputBase*> _inputHandlers;
    };
}