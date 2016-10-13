#ifndef SHADER_H
#define SHADER_H

#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include <GL/glew.h> //openGL headers

class Shader{

public:
	//program id
	GLuint Program;
	//constructor reads and builds shader
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);
	//use ~= glUseProgram
	void Use();

};

#endif