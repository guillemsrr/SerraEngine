#include "RendererBase.h"
#include <imgui_impl_opengl3_loader.h>

RendererBase::RendererBase(Camera* camera)
{
    _camera = camera;
}

void RendererBase::RenderBackground()
{
    glClearColor(255, 255, 255, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

ImU32 RendererBase::GetHUDColor()
{
    return IM_COL32(0, 0, 0, 255);
}

void RendererBase::SetViewPortSize(int new_width, int new_height)
{
    glViewport(0, 0, new_width, new_height);
}