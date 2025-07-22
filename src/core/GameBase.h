// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <vector>

#include "graphics/Camera.h"
#include "input/InputBase.h"
#include <SDL3/SDL_events.h>

class RendererBase;
class AudioEngine;

namespace SerraEngine
{
    class GameBase
    {
    public:
        GameBase();
        virtual ~GameBase() = default;

        virtual void Init(SDL_Window* window);
        virtual void Update(float deltaTime) = 0;
        virtual void HandleEvent(const SDL_Event& event);
        virtual void Render() = 0;
        virtual void RenderHUD();
        virtual void Quit() = 0;

    protected:
        SDL_Window* _window = nullptr;
        Camera* _camera;

        virtual void RenderUI() = 0;

        void SetRenderer(RendererBase* renderer);
        void SetAudioEngine(AudioEngine* audioEngine);
        void AddInputHandler(InputBase* inputHandler);

    private:
        RendererBase* _rendererBase;
        AudioEngine* _audioEngine;
        std::vector<InputBase*> _inputHandlers;
        float GetAspectRatio(int width, int height);
    };
}