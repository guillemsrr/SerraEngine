// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <SDL3/SDL.h>
#include <string>

namespace SerraEngine
{
    class GameBase;

    class App
    {
    public:
        App(int argc, char* argv[]);

        bool Init(const std::string& title, int width, int height);
        void StartGame(GameBase& game);

    private:
        int _argc;
        char** _argv;

        SDL_Window* _window = nullptr;
        SDL_GLContext _glContext;

        void InitIMGUI();
        void Quit();

        SDL_AppResult HandleEvent(const SDL_Event& sdl_event);
    };
}