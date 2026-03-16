#include "Camera.h"

Camera::Camera(float aspectRatio): _position(), _target(), _viewMatrix(), _projectionMatrix(), _aspectRatio(aspectRatio)
{
}

Camera::Camera(float fov, float aspect, float nearP, float farP)
    : _position(), _target(), _fov(fov), _aspectRatio(aspect), _nearP(nearP), _farP(farP)
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
    return _position;
}

glm::vec3 Camera::GetForward() const
{
    glm::vec3 forward = glm::normalize(_target - _position);
    return forward;
}

glm::vec3 Camera::GetRight() const
{
    glm::vec3 forward = glm::normalize(_target - _position);
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
    float camX = _radius * cosf(_pitchRad) * sinf(_yawRad);
    float camY = _radius * sinf(_pitchRad);
    float camZ = _radius * cosf(_pitchRad) * cosf(_yawRad);
    glm::vec3 newPosition = _target + glm::vec3(camX, camY, camZ);

    if (newPosition != _position)
    {
        _position = newPosition;
        UpdateViewMatrix();
        NotifyCameraMoved();
    }
}

void Camera::ApplyMotion(float xrel, float yrel)
{
    if (std::abs(xrel) < 1e-6f && std::abs(yrel) < 1e-6f) return;

    _yawRad -= xrel * _sensitivity;
    _pitchRad -= yrel * _sensitivity;

    _pitchRad = glm::clamp(_pitchRad, -_pitchLimit, _pitchLimit);

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
    if (_position != position)
    {
        _position = position;
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
    if (_yawRad != yawRad)
    {
        _yawRad = yawRad;
        NotifyCameraMoved();
    }
}

void Camera::SetPitchAngle(float pitch)
{
    float pitchRad = glm::radians(pitch);
    if (_pitchRad != pitchRad)
    {
        _pitchRad = pitchRad;
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
    return glm::degrees(_pitchRad);
}

void Camera::SetMaxRadius(int maxRadius)
{
    _maxRadius = maxRadius;
}

void Camera::UpdateViewMatrix()
{
    _viewMatrix = glm::lookAt(_position, _target, _upVector);
}

void Camera::UpdateProjectionMatrix()
{
    _projectionMatrix = glm::perspective(_fov, _aspectRatio, _nearP, _farP);
}