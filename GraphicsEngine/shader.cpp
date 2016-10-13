#include "shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath){
	//retrieve shader source code
	string vertexCode;
	string fragmentCode;

	try{
		//open files
		fstream vShaderFile(vertexPath);
		fstream fShaderFile(fragmentPath);
		//create streams
		stringstream vShaderStream, fShaderStream;
		//read from file buffers into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//convert stream to string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (exception e){

		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;

	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	//compile shaders
	GLuint vertex, fragment;
	GLchar infoLog[512];
	GLint success;

	//vertex shader:
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	//fragment shader:
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	//Check for errors from compile
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success); //set success to 1 if successful, else 0
	if (!success) //print logs
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog); //set infolog to error message
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success); //set success to 1 if successful, else 0
	if (!success) //print logs
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog); //set infolog to error message
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//compile and link shader program:
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);

	//link errors
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success){

		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		cout << "ERROR::PROGRAM::SHADER::LINK_FAILED\n" << infoLog << endl;

	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::Use(){

	glUseProgram(this->Program);

}