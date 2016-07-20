#ifndef _MODEL_H_
#define _MODEL_H_

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "shaderHandle.h"
#include <iostream>
#include <vector>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "Mesh.h"

using namespace glm;
using namespace std;

class Model
{
public:
	Model(GLchar* path);
	void Draw(ShaderHandle* shader);
private:
	vector<Mesh> meshes;
	string directory;

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	GLuint TextureFromFile(const char* path, string directory);
};


#endif //_MODEL_H_