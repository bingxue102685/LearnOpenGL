#include "CubmapStudy_r.h"
#include "BrowseDir.h"
#include <SOIL\SOIL.h>


CubMapStudyR::CubMapStudyR()
{
	skyboxShader = new ShaderHandle("cubmapstudy2");
	cubeShader = new ShaderHandle("cubmapcube2");
	camera = new Camera();
	glEnable(GL_DEPTH_TEST);
	initTextrueID();
	initVAO();
	GLFWwindow* window = RenderDelegate::getInstance()->getWindowHandle();
	glfwSetKeyCallback(window, &Camera::key_callback);
	glfwSetCursorPosCallback(window, &Camera::mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, &Camera::scroll_callback);
}

void CubMapStudyR::initTextrueID()
{
	//初始化天空盒子纹理
	BrowseDir* browseDir = BrowseDir::getInstance("skybox");
	map<string, string> filePath = browseDir->getAllFilePath();
	vector<string> fileNames = browseDir->getAllFileNames();

	glGenTextures(1, &this->skyBoxTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyBoxTextureID);

	//大小过滤器
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//环绕方式
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	unsigned char* image = nullptr;
	int width, height, channels;
	for (size_t i = 0 ; i < fileNames.size(); i ++ )
	{
		cout << filePath[fileNames[i]].c_str() << endl;
		image = SOIL_load_image(filePath[fileNames[i]].c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	//初始化物体纹理
	glGenTextures(1, &this->cubeTexutrueID);
	glBindTexture(GL_TEXTURE_2D, this->cubeTexutrueID);
	//大小过滤器
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	image = SOIL_load_image("../resource/container.jpg", &width, &height, &channels, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);
}


void CubMapStudyR::initVAO()
{
	GLfloat cubeVertices[] = {
          // Positions          // Normals
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
	GLfloat skyboxVertices[] = {
        // Positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
  
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
  
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
   
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
  
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
  
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

	//天空盒子
	GLuint skyboxVBO;
	glGenBuffers(1, &skyboxVBO);
	glGenVertexArrays(1, &this->skyBoxVAO);
	
	glBindVertexArray(this->skyBoxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	//盒子中物体
	GLuint cubeVBO;
	glGenBuffers(1, &cubeVBO);
	glGenVertexArrays(1, &this->cubeVAO);

	glBindVertexArray(this->cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

void CubMapStudyR::render()
{
	//先渲染天空盒子
	//renderSkyBoxFirst();
	//先渲染人物体
	//renderCubeFirst();
	//反射
	renderReflect();
}

void CubMapStudyR::renderReflect()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->camera->setDeltaTime(glfwGetTime());
	this->camera->DoMovement();

	mat4 model(1.0f);
	mat4 view(1.0f);
	mat4 projection(1.0f);
	view = this->camera->GetLookAt();
	projection = perspective(radians(Camera::aspect), 800.0f / 600.0f, 0.1f, 1000.0f);

	//绘制物体
	model = translate(model, vec3(0.0f, 0.0f, 0.7f));
	model = scale(model, vec3(0.3f, 0.3f, 0.3f));
	
	cubeShader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, this->cubeTexutrueID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyBoxTextureID);
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniform3fv(glGetUniformLocation(cubeShader->getProgram(), "cameraPos"),1, value_ptr(Camera::cameraPos));
	glUniform1i(glGetUniformLocation(cubeShader->getProgram(), "skybox"), 0);
	//glUniform1i(glGetUniformLocation(cubeShader->getProgram(), "Texture1"), 0);

	glBindVertexArray(this->cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//绘制天空盒子
	glDepthFunc(GL_LEQUAL);
	skyboxShader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyBoxTextureID);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(mat4(mat3(view))));
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniform1i(glGetUniformLocation(skyboxShader->getProgram(), "cubemap"), 0);

	glBindVertexArray(this->skyBoxVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDepthFunc(GL_LESS);
}

void CubMapStudyR::renderCubeFirst()
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->camera->setDeltaTime(glfwGetTime());
	this->camera->DoMovement();

	mat4 model(1.0f);
	mat4 view(1.0f);
	mat4 projection(1.0f);
	view = this->camera->GetLookAt();
	projection = perspective(radians(Camera::aspect), 800.0f / 600.0f, 0.1f, 1000.0f);

	//绘制物体
	model = translate(model, vec3(0.0f, 0.0f, 0.7f));
	model = scale(model, vec3(0.3f, 0.3f, 0.3f));
	
	cubeShader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->cubeTexutrueID);
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniform1i(glGetUniformLocation(cubeShader->getProgram(), "Texture1"), 0);

	glBindVertexArray(this->cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//绘制天空盒子
	glDepthFunc(GL_LEQUAL);
	skyboxShader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyBoxTextureID);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(mat4(mat3(view))));
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniform1i(glGetUniformLocation(skyboxShader->getProgram(), "cubemap"), 0);

	glBindVertexArray(this->skyBoxVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDepthFunc(GL_LESS);
}
void CubMapStudyR::renderSkyBoxFirst()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->camera->setDeltaTime(glfwGetTime());
	this->camera->DoMovement();

	mat4 model(1.0f);
	mat4 view(1.0f);
	mat4 projection(1.0f);
	
	view = this->camera->GetLookAt();
	projection = perspective(radians(Camera::aspect), 800.0f / 600.0f, 0.1f, 1000.0f);

	//绘制天空盒子
	glDepthMask(GL_FALSE);
	skyboxShader->UseProgram();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->skyBoxTextureID);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(mat4(mat3(view))));
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniform1i(glGetUniformLocation(skyboxShader->getProgram(), "cubemap"), 0);

	glBindVertexArray(this->skyBoxVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDepthMask(GL_TRUE);

	//绘制物体
	model = translate(model, vec3(0.0f, 0.0f, 0.7f));
	model = scale(model, vec3(0.3f, 0.3f, 0.3f));
	
	cubeShader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->cubeTexutrueID);
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader->getProgram(), "model"), 1, GL_FALSE, value_ptr(model));
	glUniform1i(glGetUniformLocation(cubeShader->getProgram(), "Texture1"), 0);

	glBindVertexArray(this->cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

