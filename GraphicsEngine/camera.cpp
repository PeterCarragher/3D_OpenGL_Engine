#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
	:direction(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM)
{

	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->UpdateCameraVectors();

}

Camera::Camera(GLfloat posx, GLfloat posy, GLfloat posz, 
	GLfloat upx, GLfloat upy, GLfloat upz, GLfloat yaw, GLfloat pitch)
	:direction(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM)
{

	this->position = glm::vec3(posx, posy, posz);
	this->worldUp = glm::vec3(upx, upy, upz);
	this->yaw = yaw;
	this->pitch = pitch;
	this->UpdateCameraVectors();

}

glm::mat4 Camera::GetCameraViewMatrix(){
	return glm::lookAt(position, position + direction, worldUp);
}

void Camera::ProcessKeyboardInput(Camera_Movement movement, GLfloat deltaTime){

	GLfloat cameraSpeed = this->movementSpeed * deltaTime; //standardises cameraSpeed across all processor speeds
	if (movement == FORWARD){
		glm::vec3 dir = glm::vec3(direction.x, 0, direction.z);
		position += cameraSpeed * dir;
	}
	else if (movement == BACKWARD){
		glm::vec3 dir = glm::vec3(direction.x, 0, direction.z);
		position -= cameraSpeed * dir;
	}
	else if (movement == LEFT){
		position -= cameraSpeed * right;
	}
	else if (movement == RIGHT){
		position += cameraSpeed * right;

	}
}

void Camera::ProcessMouseInput(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = GL_TRUE){
	
	yaw += xoffset * (this->mouseSensitivity);
	pitch += yoffset * (this->mouseSensitivity);

	if (constrainPitch == GL_TRUE){
		if (pitch > 89.0f){
			pitch = 89.0f;
		}
		else if (pitch < -89.0f){
			pitch = -89.0f;
		}
	}

	this->UpdateCameraVectors();
}

void Camera::ProcessScrollInput(float yoffset)
{
	if (this->zoom >= 1.0f && this->zoom <= 45.0f)
		this->zoom -= yoffset;
	if (this->zoom < 1.0f)
		this->zoom = 1.0f;
	if (this->zoom > 45.0f)
		this->zoom = 45.0f;
}

void Camera::UpdateCameraVectors(){
	glm::vec3 Dir;
	Dir.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw)); //the ratio of x:y changes with pitch, so must recompute x with pitch
	Dir.y = sin(glm::radians(pitch));
	Dir.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	direction = glm::normalize(Dir);
	this->right = glm::normalize(glm::cross(direction, worldUp));

	this->up = glm::normalize(glm::cross(right, direction));
}
