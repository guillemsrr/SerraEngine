#include "Camera.h"

Camera::Camera(float aspectRatio): _target(), _viewMatrix(), _projectionMatrix(), _aspectRatio(aspectRatio)
{
}

Camera::Camera(float fov, float aspect, float nearP, float farP)
    : _target(), _fov(fov), _aspectRatio(aspect), _nearP(nearP), _farP(farP)
{
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

void Camera::AddOnCameraMovedListener(std::function<void()> listener) const
{
    OnCameraMovedListeners.push_back(listener);
}

void Camera::NotifyCameraMoved() const
{
    for (const auto& listener : OnCameraMovedListeners)
    {
        if (listener) listener();
    }
}

void Camera::SetTarget(const glm::vec3& target)
{
    if (_target != target)
    {
        _target = target;
        NotifyCameraMoved();
    }
}

void Camera::SetAspectRatio(float aspectRatio)
{
    if (_aspectRatio != aspectRatio)
    {
        _aspectRatio = aspectRatio;
        UpdateProjectionMatrix();
        NotifyCameraMoved();
    }
}

const glm::mat4& Camera::GetViewMatrix() const
{
    return _viewMatrix;
}

const glm::mat4& Camera::GetProjectionMatrix() const
{
    return _projectionMatrix;
}

glm::vec3 Camera::GetPosition() const
{
    return Position;
}

glm::vec3 Camera::GetForward() const
{
    glm::vec3 forward = glm::normalize(_target - Position);
    return forward;
}

glm::vec3 Camera::GetRight() const
{
    glm::vec3 forward = glm::normalize(_target - Position);
    glm::vec3 right = glm::normalize(glm::cross(forward, _upVector));
    return right;
}

glm::vec3 Camera::GetUp() const
{
    glm::vec3 forward = GetForward();
    glm::vec3 right = GetRight();
    return glm::normalize(glm::cross(right, forward));
}

void Camera::UpdatePosition()
{
    float camX = _radius * cosf(Rotation.x) * sinf(Rotation.y);
    float camY = _radius * sinf(Rotation.x);
    float camZ = _radius * cosf(Rotation.x) * cosf(Rotation.y);
    glm::vec3 newPosition = _target + glm::vec3(camX, camY, camZ);

    if (newPosition != Position)
    {
        Position = newPosition;
        UpdateViewMatrix();
        NotifyCameraMoved();
    }
}

void Camera::ApplyMotion(float xrel, float yrel)
{
    if (std::abs(xrel) < 1e-6f && std::abs(yrel) < 1e-6f) return;

    Rotation.y -= xrel * _sensitivity;
    Rotation.x -= yrel * _sensitivity;

    Rotation.x = glm::clamp(Rotation.x, -_pitchLimit, _pitchLimit);

    NotifyCameraMoved();
}

void Camera::AddRadius(float wheelValue)
{
    if (std::abs(wheelValue) < 1e-6f) return;

    float newRadius = glm::clamp(_radius - wheelValue * _zoomSensitivity, _minRadius, _maxRadius);
    if (newRadius != _radius)
    {
        _radius = newRadius;
        NotifyCameraMoved();
    }
}

void Camera::SetPosition(const glm::vec3& position)
{
    if (Position != position)
    {
        Position = position;
        UpdateViewMatrix();
        NotifyCameraMoved();
    }
}

void Camera::SetRotationAngles(float yaw, float pitch)
{
    SetYawAngle(yaw);
    SetPitchAngle(pitch);
}

void Camera::SetYawAngle(float yaw)
{
    float yawRad = glm::radians(yaw);
    if (Rotation.y != yawRad)
    {
        Rotation.y = yawRad;
        NotifyCameraMoved();
    }
}

void Camera::SetPitchAngle(float pitch)
{
    float pitchRad = glm::radians(pitch);
    if (Rotation.x != pitchRad)
    {
        Rotation.x = pitchRad;
        NotifyCameraMoved();
    }
}

void Camera::SetRadius(float radius)
{
    if (_radius != radius)
    {
        _radius = radius;
        NotifyCameraMoved();
    }
}

void Camera::SetFOV(float fov)
{
    if (_fov != fov)
    {
        _fov = fov;
        UpdateProjectionMatrix();
        NotifyCameraMoved();
    }
}

void Camera::SetNearPlane(float nearPlane)
{
    if (_nearP != nearPlane)
    {
        _nearP = nearPlane;
        UpdateProjectionMatrix();
        NotifyCameraMoved();
    }
}

void Camera::SetFarPlane(float farPlane)
{
    if (_farP != farPlane)
    {
        _farP = farPlane;
        UpdateProjectionMatrix();
        NotifyCameraMoved();
    }
}

void Camera::SetZoomSensitivity(float sensitivity)
{
    _zoomSensitivity = sensitivity;
}

float Camera::GetAspectRatio() const
{
    return _aspectRatio;
}

float Camera::GetFOV() const
{
    return _fov;
}

float Camera::GetFOVRad() const
{
    return glm::radians(GetFOV());
}

float Camera::GetPitchAngle() const
{
    return glm::degrees(Rotation.x);
}

void Camera::SetMaxRadius(int maxRadius)
{
    _maxRadius = maxRadius;
}

void Camera::UpdateViewMatrix()
{
    _viewMatrix = glm::lookAt(Position, _target, _upVector);
}

void Camera::UpdateProjectionMatrix()
{
    _projectionMatrix = glm::perspective(_fov, _aspectRatio, _nearP, _farP);
}
