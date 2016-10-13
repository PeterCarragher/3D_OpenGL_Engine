#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "globals.h"

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 5.0f;
const GLfloat SENSITIVTY = 0.25f;
const float ZOOM = 45.0f;


class Camera{

public:

	// constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH); //defaults supplied at definition, front is always set facing forward
	//constructor with floats
	Camera(GLfloat posx = 0.0f, GLfloat posy = 0.f, GLfloat posz = 0.f, 
		GLfloat upx = 0.f, GLfloat upy = 1.0f, GLfloat upz = 0.f, GLfloat yaw = YAW, GLfloat pitch = PITCH);
	//return view matrix
	glm::mat4 GetCameraViewMatrix();
	
	void ProcessKeyboardInput(Camera_Movement movement, GLfloat deltaTime);
	void ProcessMouseInput(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch);
	void ProcessScrollInput(float offset);

	glm::vec3 getPos(){ return this->position; };
	glm::vec3 getDir(){ return this->direction; };
	float getYaw(){ return this->yaw; };
	float getPitch(){ return this->pitch; };

	float zoom;

private:
	GLfloat yaw;
	GLfloat pitch;
	
	GLfloat mouseSensitivity;
	GLfloat movementSpeed;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;
	glm::vec3 worldUp;
	glm::vec3 right;

	void UpdateCameraVectors();

};

#endif