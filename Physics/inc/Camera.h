#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>
class Camera
{
public:

	Camera();

	virtual ~Camera();

	virtual void Update(float deltaTime);

	void SetPosition(const glm::vec3 &pos);
	void SetYawPitchRoll(float yaw, float pitch, float roll);
	void SetProjection(float fov, float aspect, float near, float far);

	glm::vec3& GetPosition();
	glm::vec3& GetFront() {
		return m_cameraFront;
	}
	float GetYaw();
	float GetPitch();
	float GetRoll();

	glm::mat4& GetView();
	glm::mat4& GetProjection();
	glm::mat4 GetProjectionView();

	void Lookat(glm::vec3 target);

	glm::vec3 mouse_click_callback(int mouse_x, int mouse_y);
	void SetMovementKeys(int forwardKey, int backKey, int leftKey, int rightKey);
	void SetMouseLookButton(int mouseButton);

	glm::vec3 calculateMouseRay();
	glm::vec2 getNormalisedDeviceCoordinates(float mouseX, float mouseY);

	glm::vec4 toEyeCoords(glm::vec4 clipCoords);
	glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
	glm::vec3 getPointOnRay(glm::vec3 ray, float distance);

	bool intersectionInRange(float start, float finish, glm::vec3 ray);
	glm::vec3 binarySearch(int count, float start, float finish, glm::vec3 ray);
	glm::vec3 currentPoint = glm::vec3(0);
protected:

	void CalculateFront();

protected:

	const int RECURSION_COUNT = 200;
	const float RAY_RANGE = 600;
	glm::vec3 m_cameraPosition = glm::vec3(0, 2, -2);
	glm::vec3 m_cameraFront = glm::vec3(0, 0, 1);
	glm::vec3 m_cameraUp = glm::vec3(0, 1, 0);

	float m_cameraYaw = 0.0f;
	float m_cameraPitch = 0.0f;
	float m_cameraRoll = 0.0f;

	float m_cameraMoveSpeed = 10.0f;

	int m_lastMouseXPos, m_lastMouseYPos;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	// movement keys
	int m_forwardKey;	// defaults to W
	int m_backKey;		// defaults to S
	int m_leftKey;		// defaults to A
	int m_rightKey;		// defaults to D

	int m_mouseLookButton; // defaults to right mouse button

	int windowWidth = 1280;
	int windowHeight = 720;

private:
};
