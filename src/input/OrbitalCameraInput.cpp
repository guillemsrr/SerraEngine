#include "OrbitalCameraInput.h"

#include "graphics/Camera.h"

void OrbitalCameraInput::HandleEvent(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
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
        if (_mouseRotating)
        {
            _camera->ApplyMotion(event.motion.xrel, event.motion.yrel);
        }
        break;
    case SDL_EVENT_MOUSE_WHEEL:
        _camera->AddRadius(event.wheel.y);
        break;
    }
}