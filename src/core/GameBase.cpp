#include "GameBase.h"
#include <imgui.h>

void SerraEngine::GameBase::Init(SDL_Window* window)
{
    _window = window;
}

ImU32 SerraEngine::GameBase::GetHUDColor()
{
    return IM_COL32(0, 0, 0, 255);
}

void SerraEngine::GameBase::RenderHUD()
{
    const float DISTANCE_FROM_EDGE = 10.0f;
    ImVec2 window_pos = ImVec2(DISTANCE_FROM_EDGE, DISTANCE_FROM_EDGE);
    ImVec2 window_pos_pivot = ImVec2(0.0f, 0.0f); // top-left

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImU32 HUDColor = GetHUDColor();
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