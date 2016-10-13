#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include "shader.h"
#include <sstream>
#include <assimp/Importer.hpp>

struct Vertex{

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;

};

struct Texture{

	GLuint id;
	std::string type;
	aiString path;

};

class Mesh {

public:
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<GLuint> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<GLuint> indices);
	void Draw(Shader shader);

	//deconstrutor

private:
	GLuint VAO, VBO, EBO;

	void setUpMesh();

};