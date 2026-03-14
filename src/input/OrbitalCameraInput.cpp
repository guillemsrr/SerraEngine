#include "OrbitalCameraInput.h"

#include <imgui.h>

#include "graphics/Camera.h"

OrbitalCameraInput::OrbitalCameraInput(Camera* const camera) : _camera(camera)
{
}

void OrbitalCameraInput::HandleEvent(const SDL_Event& event)
{
    ImGuiIO& io = ImGui::GetIO();

    switch (event.type)
    {
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (io.WantCaptureMouse)
            {
                _mouseRotating = false;
                break;
            }

            _mouseRotating = true;
        }
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            _mouseRotating = false;
        }
        break;
    case SDL_EVENT_MOUSE_MOTION:
        if (io.WantCaptureMouse)
        {
            _mouseRotating = false;
            break;
        }

        if (_mouseRotating)
        {
            _camera->ApplyMotion(event.motion.xrel, event.motion.yrel);
        }
        break;
    case SDL_EVENT_MOUSE_WHEEL:
        if (io.WantCaptureMouse)
        {
            break;
        }

        _camera->AddRadius(event.wheel.y);
        break;
    }
}
