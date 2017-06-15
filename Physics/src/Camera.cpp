#define GLM_SWIZZLE
#include "Camera.h"
#include <Input.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\geometric.hpp>
#include <Windows.h>
#include <gl\GLU.h>
Camera::Camera()
{
	m_forwardKey	= aie::INPUT_KEY_W;
	m_backKey		= aie::INPUT_KEY_S;
	m_leftKey		= aie::INPUT_KEY_A;
	m_rightKey		= aie::INPUT_KEY_D;

	m_mouseLookButton = aie::INPUT_MOUSE_BUTTON_RIGHT;
}
Camera::~Camera()
{

}

void Camera::Update(float deltaTime)
{
	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(m_forwardKey))
	{
		m_cameraPosition += m_cameraFront * m_cameraMoveSpeed * deltaTime;
	}

	if (input->isKeyDown(m_backKey))
	{
		m_cameraPosition -= m_cameraFront * m_cameraMoveSpeed * deltaTime;
	}

	if (input->isKeyDown(m_leftKey))
	{
		glm::vec3 dir = glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
		m_cameraPosition -= dir * m_cameraMoveSpeed * deltaTime;
	}

	if (input->isKeyDown(m_rightKey))
	{
		glm::vec3 dir = glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
		m_cameraPosition += dir * m_cameraMoveSpeed * deltaTime;
	}

	if (input->isMouseButtonDown(m_mouseLookButton) )
	{
		int mouseXPos, mouseYPos;
		input->getMouseXY(&mouseXPos, &mouseYPos);

		int deltaMouseX = mouseXPos - m_lastMouseXPos;
		int deltaMouseY = mouseYPos - m_lastMouseYPos;
		m_cameraYaw += deltaMouseX;
		m_cameraPitch += deltaMouseY;

		if (m_cameraPitch > 85.0f) m_cameraPitch = 85.0f;
		if (m_cameraPitch <-85.0f) m_cameraPitch = -85.0f;

		CalculateFront();
	}

	m_viewMatrix = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);

	// record the current mouse position for use next frame.
	input->getMouseXY(&m_lastMouseXPos, &m_lastMouseYPos);

}

void Camera::CalculateFront()
{
	glm::vec3 front;
	front.x = glm::cos(glm::radians(m_cameraYaw)) * glm::cos(glm::radians(m_cameraPitch));
	front.y = glm::sin(glm::radians(m_cameraPitch));
	front.z = glm::sin(glm::radians(m_cameraYaw)) * glm::cos(glm::radians(m_cameraPitch));
	m_cameraFront = glm::normalize(front);
}

void Camera::SetProjection(float fov, float aspect, float neara, float fara)
{
	m_projectionMatrix = glm::perspective(fov, aspect, neara, fara);
}

void Camera::SetPosition(const glm::vec3& pos)
{
	m_cameraPosition = pos;
}

void Camera::SetYawPitchRoll(float yaw, float pitch, float roll)
{
	m_cameraYaw = yaw;
	m_cameraPitch = pitch;
	m_cameraRoll = roll;

	CalculateFront();
}

glm::vec3& Camera::GetPosition()
{
	return m_cameraPosition;
}

float Camera::GetYaw()
{
	return m_cameraYaw;
}

float Camera::GetPitch()
{
	return m_cameraPitch;
}

float Camera::GetRoll()
{
	return m_cameraRoll;
}

glm::mat4& Camera::GetView()
{
	return m_viewMatrix;
}

glm::mat4& Camera::GetProjection()
{
	return m_projectionMatrix;
}

glm::mat4 Camera::GetProjectionView()
{
	return m_projectionMatrix * m_viewMatrix;
}

void Camera::Lookat(glm::vec3 target)
{
	glm::vec3 dir = glm::normalize(target - m_cameraPosition);
	m_cameraPitch = glm::degrees(glm::asin(dir.y));
	m_cameraYaw = glm::degrees(atan2(dir.y, dir.x));

	CalculateFront();
}

glm::vec3 Camera::mouse_click_callback(int mouse_x, int mouse_y)
{ 
	glm::vec3 currentRay = calculateMouseRay();
	glm::vec3 point = getPointOnRay(currentRay, 10);
	currentPoint = point;
	std::cout << "X " << (float)point.x << " Y " << (float)point.y << std::endl << " Z " << (float)point.z << std::endl;
	return currentPoint;
}

glm::vec3 Camera::calculateMouseRay() {
	aie::Input* input = aie::Input::getInstance();
	int mouseX = input->getMouseX();
	int mouseY = input->getMouseY();
	glm::vec2 normalizedCoords = getNormalisedDeviceCoordinates(mouseX, mouseY);
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
	glm::vec4 eyeCoords = toEyeCoords(clipCoords);
	glm::vec3 worldRay = toWorldCoords(eyeCoords);
	return worldRay;
}

glm::vec3 Camera::toWorldCoords(glm::vec4 eyeCoords) {
	glm::mat4 invertedView = glm::inverse(m_viewMatrix);
	glm::vec4 rayWorld = invertedView * eyeCoords;
	glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	glm::normalize(mouseRay);
	return mouseRay;
}

glm::vec4 Camera::toEyeCoords(glm::vec4 clipCoords) {
	glm::mat4 invertedProjection = glm::inverse(m_projectionMatrix);
	glm::vec4 eyeCoords = invertedProjection * clipCoords;
	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
}

glm::vec2 Camera::getNormalisedDeviceCoordinates(float mouseX, float mouseY) {
	float x = (2.0f * mouseX) / windowWidth - 1.0f;
	float y = (2.0f * mouseY) / windowHeight - 1.0f;
	return glm::vec2(x, y);
}

glm::vec3 Camera::getPointOnRay(glm::vec3 ray, float distance) {
	glm::vec3 camPos = this->GetPosition();
	glm::vec3 start = glm::vec3(camPos.x, camPos.y, camPos.z);
	glm::vec3 scaledRay = glm::vec3(ray.x * distance, ray.y * distance, ray.z * distance);
	glm::vec3 finalRay = start + scaledRay;

	return finalRay;
}
glm::vec3 Camera::binarySearch(int count, float start, float finish, glm::vec3 ray) {

	return glm::vec3();
}

bool Camera::intersectionInRange(float start, float finish, glm::vec3 ray) {

	return true;
}


void Camera::SetMovementKeys(int forwardKey, int backKey, int leftKey, int rightKey)
{
	m_forwardKey = forwardKey;
	m_backKey = backKey;
	m_leftKey = leftKey;
	m_rightKey = rightKey;
}

void Camera::SetMouseLookButton(int mouseButton)
{
	m_mouseLookButton = mouseButton;
}
