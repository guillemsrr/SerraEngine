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

void Camera::SetTarget(const glm::vec3& target)
{
    _target = target;
}

void Camera::SetAspectRatio(float aspectRatio)
{
    _aspectRatio = aspectRatio;
    UpdateProjectionMatrix();
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
    _position = _target + glm::vec3(camX, camY, camZ);

    UpdateViewMatrix();
}

void Camera::ApplyMotion(float xrel, float yrel)
{
    _yawRad -= xrel * _sensitivity;
    _pitchRad -= yrel * _sensitivity;

    _pitchRad = glm::clamp(_pitchRad, -_pitchLimit, _pitchLimit);

    if (OnCameraMoved)
    {
        OnCameraMoved();
    }
}

void Camera::AddRadius(float wheelValue)
{
    _radius -= wheelValue * _zoomSensitivity;
    _radius = glm::clamp(_radius, _minRadius, _maxRadius);

    if (OnCameraMoved)
    {
        OnCameraMoved();
    }
}

void Camera::SetPosition(const glm::vec3& position)
{
    _position = position;
    UpdateViewMatrix();
}

void Camera::SetRotationAngles(float yaw, float pitch)
{
    SetYawAngle(yaw);
    SetPitchAngle(pitch);
}

void Camera::SetYawAngle(float yaw)
{
    _yawRad = glm::radians(yaw);
}

void Camera::SetPitchAngle(float pitch)
{
    _pitchRad = glm::radians(pitch);
}

void Camera::SetRadius(float radius)
{
    _radius = radius;
}

void Camera::SetFOV(float fov)
{
    _fov = fov;
}

void Camera::SetNearPlane(float nearPlane)
{
    _nearP = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
    _farP = farPlane;
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