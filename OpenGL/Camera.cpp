#include "Camera.h"

Camera::Camera(const Resolution& _resolution, const float _near, const float _far)
{
	projection = glm::perspective(glm::radians(45.0f),
		(float)_resolution.width / (float)_resolution.height,
		_near,
		_far);

	view = glm::lookAt(
		glm::vec3(1, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
}