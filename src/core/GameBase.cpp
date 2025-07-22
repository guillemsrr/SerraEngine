#include "GameBase.h"
#include <imgui.h>
#include <memory>

#include "audio/AudioEngine.h"

#include "graphics/RendererBase.h"

SerraEngine::GameBase::GameBase(): _camera(nullptr), _rendererBase(nullptr)
{
}

void SerraEngine::GameBase::Init(SDL_Window* window)
{
    _window = window;

    int windowWidth, windowHeight;
    SDL_GetWindowSizeInPixels(window, &windowWidth, &windowHeight);
    float aspectRatio = GetAspectRatio(windowWidth, windowHeight);
    _camera = new Camera(aspectRatio);
}

void SerraEngine::GameBase::HandleEvent(const SDL_Event& event)
{
    if (event.window.type == SDL_EVENT_WINDOW_RESIZED || event.window.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
    {
        int newWidth = event.window.data1;
        int newHeight = event.window.data2;

        float aspectRatio = GetAspectRatio(newWidth, newHeight);
        _camera->SetAspectRatio(aspectRatio);
        _rendererBase->SetViewPortSize(newWidth, newHeight);
    }

    for (InputBase* const& inputHandler : _inputHandlers)
    {
        inputHandler->HandleEvent(event);
    }
}

void SerraEngine::GameBase::SetRenderer(RendererBase* renderer)
{
    _rendererBase = renderer;
}

void SerraEngine::GameBase::SetAudioEngine(AudioEngine* audioEngine)
{
    _audioEngine = audioEngine;
}

void SerraEngine::GameBase::AddInputHandler(InputBase* inputHandler)
{
    _inputHandlers.push_back(inputHandler);
}

void SerraEngine::GameBase::RenderHUD()
{
    const float DISTANCE_FROM_EDGE = 10.0f;
    ImVec2 window_pos = ImVec2(DISTANCE_FROM_EDGE, DISTANCE_FROM_EDGE);
    ImVec2 window_pos_pivot = ImVec2(0.0f, 0.0f); // top-left

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImU32 HUDColor = _rendererBase->GetHUDColor();
    ImGui::PushStyleColor(ImGuiCol_Text, HUDColor);

    ImGui::Begin("HUD",
                 nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing
                 | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);

    RenderUI();

    ImGui::End();

    window_pos = ImVec2(ImGui::GetIO().DisplaySize.x - DISTANCE_FROM_EDGE, DISTANCE_FROM_EDGE);
    window_pos_pivot = ImVec2(1.0f, 0.0f); // top-right

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    ImGui::SetNextWindowBgAlpha(0.f);

    ImGui::Begin("FPS",
                 nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing
                 | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);

    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::PopStyleColor();
}

float SerraEngine::GameBase::GetAspectRatio(int width, int height)
{
    return static_cast<float>(width) / static_cast<float>(height);
}