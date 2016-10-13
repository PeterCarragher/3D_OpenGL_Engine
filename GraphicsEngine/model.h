#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

GLint TextureFromFile(const char* path, string directory);
using namespace std;

class Model{

public:
	Model(GLchar* path){ this->loadModel(path); }
	void Draw(Shader shader);

private:
	vector<Mesh> meshes;
	vector<Texture> loadedTextures;
	string directory;
	void loadModel(string path);

	//for assimp functions
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};