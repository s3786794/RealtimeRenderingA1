#include "Camera.h"

Camera::Camera() {
    cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -3.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, -3.0f);
    cameraWUp = cameraUp;
    cameraSpeed = 1.0f;
    deltaTime = 0.0f;
    lastFrame = 0.0f;

    checkMouse = true;
    pitch = 0.0f;
    yaw = -90.0f;
    lastX = width / 2.0f;
    lastY = height / 2.0f;
    fov = 45.0f;
}

void Camera::ImmediateCamera() {
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(proj));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));

    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

void Camera::ModernCamera() {
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(proj));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));
}

void Camera::Mouse_Callback(SDL_Window* window, double xpos, double ypos) {
    SDL_GetWindowSize(window, &width, &height);

    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;

    /*SDL_WarpMouseInWindow(window, (float)width / 2.0f, (float)height / 2.0f);*/

    if (checkMouse) {
        lastX = xpos;
        lastY = ypos;
        checkMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(direction);

    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraWUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

void Camera::SetCameraPos(glm::vec3 cameraPos)
{
    this->cameraPos = cameraPos;
}

void Camera::SetCameraFront(glm::vec3 cameraFront)
{
    this->cameraFront = cameraFront;
}

void Camera::SetCameraUp(glm::vec3 cameraUp)
{
    this->cameraUp = cameraUp;
}

void Camera::SetPitch(float pitch)
{
    this->pitch = pitch;
}

void Camera::SetYaw(float yaw)
{
    this->yaw = yaw;
}

void Camera::SetLastX(float lastX)
{
    this->lastX = lastX;
}

void Camera::SetLastY(float lastY)
{
    this->lastY = lastY;
}

void Camera::SetFov(float fov)
{
    this->fov = fov;
}

glm::vec3* Camera::GetCameraPos()
{
    glm::vec3* cameraNum = &cameraPos;
    return cameraNum;
}

glm::vec3* Camera::GetCameraFront()
{
    glm::vec3* cameraNum = &cameraFront;
    return cameraNum;
}

glm::vec3* Camera::GetCameraUp()
{
    glm::vec3* cameraNum = &cameraUp;
    return cameraNum;
}

const float* Camera::GetCameraSpeed() {
    const float* speed = &cameraSpeed;
    return speed;
}

float* Camera::GetDeltaTime()
{
    float currentFrame = SDL_GetTicks();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    deltaTime /= 1000;

    float* deltaPtr = &deltaTime;
    return deltaPtr;
}

float* Camera::GetPitch()
{
    float* num = &pitch;
    return num;
}

float* Camera::GetYaw()
{
    float* num = &yaw;
    return num;
}

float* Camera::GetLastX()
{
    float* num = &lastX;
    return num;
}

float* Camera::GetLastY()
{
    float* num = &lastY;
    return num;
}

float* Camera::GetFov()
{
    float* num = &fov;
    return num;
}