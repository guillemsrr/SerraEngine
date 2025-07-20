#include "App.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <iostream>
#include "GameBase.h"

#include <glad/glad.h>

namespace SerraEngine
{
    App::App(int argc, char* argv[]) : _argc(argc), _argv(argv), _glContext(nullptr)
    {
    }

    bool App::Init(const std::string& title, int width, int height)
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("Couldn't initialize Video: %s", SDL_GetError());
            return false;
        }

        if (!SDL_Init(SDL_INIT_AUDIO))
        {
            SDL_Log("Couldn't initialize Audio: %s", SDL_GetError());
            return false;
        }

        if (!SDL_Init(SDL_INIT_EVENTS))
        {
            SDL_Log("Failed to initialize Events: %s", SDL_GetError());
            return false;
        }

        _window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!_window)
        {
            SDL_Log("Failed to create window: %s", SDL_GetError());
            SDL_Quit();
            return false;
        }

#ifndef __EMSCRIPTEN__
        SDL_Rect displayBounds;
        SDL_GetDisplayBounds(2, &displayBounds);
        int centeredX = displayBounds.x + (displayBounds.w - width) / 2;
        int centeredY = displayBounds.y + (displayBounds.h - height) / 2;
        SDL_SetWindowPosition(_window, centeredX, centeredY);
#endif

        _glContext = SDL_GL_CreateContext(_window);

        InitIMGUI();

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

#ifdef __EMSCRIPTEN__
        //no glad loader needed
#else
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            SDL_Log("Failed to initialize GLAD");
            return false;
        }
#endif

        glViewport(0, 0, width, height);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //glEnable(GL_DEPTH_TEST);

        return true;
    }

    void App::Quit()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

        if (_glContext)
        {
            SDL_GL_DestroyContext(_glContext);
            _glContext = nullptr;
        }

        if (_window)
        {
            SDL_DestroyWindow(_window);
            _window = nullptr;
        }
        SDL_Quit();
    }

    void App::InitIMGUI()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup scaling
        float main_scale = SDL_GetWindowDisplayScale(_window);
        ImGuiStyle& style = ImGui::GetStyle();
        style.ScaleAllSizes(main_scale);
        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
        style.FontScaleDpi = main_scale;
        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

        // Setup Platform/Renderer backends
        ImGui_ImplSDL3_InitForOpenGL(_window, _glContext);

        const char* glsl_version = "#version 300 es";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    SDL_AppResult App::HandleEvent(const SDL_Event& sdl_event)
    {
        if (sdl_event.type == SDL_EVENT_QUIT)
        {
            return SDL_APP_SUCCESS;
        }

        if (sdl_event.type == SDL_EVENT_KEY_DOWN && sdl_event.key.key == SDLK_ESCAPE)
        {
            return SDL_APP_SUCCESS;
        }

        return SDL_APP_CONTINUE;
    }

    void App::StartGame(GameBase& game)
    {
        uint64_t lastCounter = SDL_GetPerformanceCounter();
        const double freq = static_cast<double>(SDL_GetPerformanceFrequency());
        game.Init(_window);

        SDL_Event e;
        SDL_AppResult appResult = SDL_APP_CONTINUE;
        while (appResult == SDL_APP_CONTINUE)
        {
            while (SDL_PollEvent(&e))
            {
                appResult = HandleEvent(e);
                game.HandleEvent(e);
            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();

            uint64_t currentCounter = SDL_GetPerformanceCounter();
            double deltaTime = static_cast<double>(currentCounter - lastCounter) / freq;
            lastCounter = currentCounter;
            game.Update(static_cast<float>(deltaTime));
            game.Render();
            game.RenderHUD();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(_window);
        }

        game.Quit();
        Quit();
    }
}