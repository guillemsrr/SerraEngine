// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once

#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera(float aspectRatio);
    Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

    mutable std::function<void()> OnCameraMoved;

    void SetTarget(const glm::vec3& target);
    void SetAspectRatio(float aspectRatio);
    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetProjectionMatrix() const;

    glm::vec3 GetPosition() const;
    glm::vec3 GetForward() const;
    glm::vec3 GetRight() const;
    glm::vec3 GetUp() const;

    void UpdatePosition();
    void ApplyMotion(float xrel, float yrel);
    void AddRadius(float wheelValue);
    void SetPosition(const glm::vec3& position);
    void SetRotationAngles(float yaw, float pitch);
    void SetYawAngle(float yaw);

    void SetPitchAngle(float pitch);
    void SetRadius(float radius);
    void SetFOV(float fov);
    void SetNearPlane(float nearPlane);
    void SetFarPlane(float farPlane);
    void SetZoomSensitivity(float sensitivity);

    float GetAspectRatio() const;
    float GetFOV() const;
    float GetFOVRad() const;
    float GetPitchAngle() const;
    void SetMaxRadius(int maxRadius);

private:
    glm::vec3 _position;
    glm::vec3 _target;
    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;

    float _yawRad = 0.f;
    float _pitchRad = 0.f;
    float _radius = 30.f;
    float _minRadius = 1.f;
    float _maxRadius = 100.f;

    float _fov = glm::radians(45.f);
    float _aspectRatio;
    float _nearP = 0.1f;
    float _farP = 100.f;

    glm::vec3 _upVector = {0.f, 1.f, 0.f};

    const float _sensitivity = 0.005f;
    float _zoomSensitivity = 0.5f;
    const float _pitchLimit = glm::radians(89.0f);

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();
};