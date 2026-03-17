#include "RendererBase.h"
#include <imgui_impl_opengl3_loader.h>

#include <glm/common.hpp>

RendererBase::RendererBase(Camera* camera)
{
    _camera = camera;
}

void RendererBase::RenderBackground()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
}

glm::vec3 RendererBase::FilterSurfaceColor(const glm::vec3& color, float audioEmission) const
{
    /*
    if (_renderMode == SerraEngine::RenderMode::Light)
    {
        return color;
    }
    */

    const float luminance = glm::dot(color, glm::vec3(0.299f, 0.587f, 0.114f));
    const glm::vec3 darkSurface = glm::vec3(luminance * 0.18f);
    const glm::vec3 glow = glm::vec3(glm::clamp(audioEmission, 0.0f, 1.0f));
    return glm::clamp(darkSurface + glow, glm::vec3(0.0f), glm::vec3(1.0f));
}

color RendererBase::FilterSurfaceColor(const color& color, float audioEmission) const
{
    return glm::vec4(FilterSurfaceColor(glm::vec3(color), audioEmission), color.a);
}

glm::vec3 RendererBase::GetAudioGlowColor(float energy) const
{
    const float intensity = glm::clamp(energy, 0.0f, 1.0f);
    return glm::vec3(intensity);
}

ImU32 RendererBase::GetHUDTextColor()
{
    return IM_COL32(0, 0, 0, 255);
}

ImU32 RendererBase::GetHUDBackgroundColor()
{
    return IM_COL32(255, 255, 255, 180);
}

void RendererBase::SetViewPortSize(int new_width, int new_height)
{
    glViewport(0, 0, new_width, new_height);
}

ImGuiWindowFlags RendererBase::GetHUDFlags()
{
    return ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize /*| ImGuiWindowFlags_NoFocusOnAppearing
        | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove*/
    ;
}
