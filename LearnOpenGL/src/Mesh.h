#ifndef _MESH_H_
#define _MESH_H_

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "shaderHandle.h"
#include <iostream>
#include <vector>


using namespace glm;
using namespace std;

struct  Vertex
{
	vec3 Position;  //顶点位置
	vec3 Normal;	//法线向量
	vec2 TexCoords; //纹理坐标
};


struct Texture
{
	GLuint id;
	string type;
	string path;
};

class Mesh 
{
public:
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	~Mesh();
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	void Draw(ShaderHandle* shader);

private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};




















#endif //_MESH_H_

