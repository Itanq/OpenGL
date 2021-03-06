#include<cmath>
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<SOIL.h>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "camera.h"

typedef GLint Int;
typedef GLuint Uint;
typedef GLchar Char;
typedef GLfloat Float;

Uint WIDTH = 800, HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

Float lastX = 400.0;
Float lastY = 300.0;

bool keys[1025];
Float deltaTime = 0.0f;
Float lastFrame = 0.0f;
bool firstMouse = GL_TRUE;
//glm::vec3 lightPos(0.5f, 0.4f, 1.0f);
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;

}

void do_movement()
{
    // Camera controls
    if(keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //cout << key << endl;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS)
            keys[key] = true;
        else if(action == GLFW_RELEASE)
            keys[key] = false;	
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}	

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

GLFWwindow* InitWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "BasicLighting", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// 键盘回调函数
	glfwSetKeyCallback(window, keyboard);
	// 鼠标(光标)回调函数
	glfwSetCursorPosCallback(window, mouse_callback);
	// 滚轮回调函数
	glfwSetScrollCallback(window, scroll_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, WIDTH, HEIGHT);
	return window;
}

void SetContainerAttrib(Shader containerShader, GLuint &containerVAO, GLuint &texture1, GLuint &texture2)
{
	GLfloat vertices[] = {
        // Positions           // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

	Uint VBO;
	glGenVertexArrays(1,&containerVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(containerVAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 顶点位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// 每个点的法向量
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// 每个点的纹理坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}

void SetTextureAttrib(GLuint& texture, GLchar* textureName)
{
	glGenTextures(1, &texture);
	int width, height;
	unsigned char* image = SOIL_load_image(textureName, &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SetLampAttrib(Shader lampShader, GLuint &lampVAO)
{
	GLfloat lampvertices[] = {
	    -0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f, -0.5f,
	     0.5f,  0.5f, -0.5f,
	     0.5f,  0.5f, -0.5f,
	    -0.5f,  0.5f, -0.5f,
	    -0.5f, -0.5f, -0.5f,

	    -0.5f, -0.5f,  0.5f,
	     0.5f, -0.5f,  0.5f,
	     0.5f,  0.5f,  0.5f,
	     0.5f,  0.5f,  0.5f,
	    -0.5f,  0.5f,  0.5f,
	    -0.5f, -0.5f,  0.5f,

	    -0.5f,  0.5f,  0.5f,
	    -0.5f,  0.5f, -0.5f,
	    -0.5f, -0.5f, -0.5f,
	    -0.5f, -0.5f, -0.5f,
	    -0.5f, -0.5f,  0.5f,
	    -0.5f,  0.5f,  0.5f,

	     0.5f,  0.5f,  0.5f,
	     0.5f,  0.5f, -0.5f,
	     0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f,  0.5f,
	     0.5f,  0.5f,  0.5f,

	    -0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f,  0.5f,
	     0.5f, -0.5f,  0.5f,
	    -0.5f, -0.5f,  0.5f,
	    -0.5f, -0.5f, -0.5f,

	    -0.5f,  0.5f, -0.5f,
	     0.5f,  0.5f, -0.5f,
	     0.5f,  0.5f,  0.5f,
	     0.5f,  0.5f,  0.5f,
	    -0.5f,  0.5f,  0.5f,
	    -0.5f,  0.5f, -0.5f
	};

	GLuint VBO;
	glGenVertexArrays(1, &lampVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(lampVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lampvertices), lampvertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void SetDirectionLight(Shader& containerShader)
{
	Uint lightAmbientLoc = glGetUniformLocation(containerShader.Program, "dirLight.ambient");
	Uint lightDiffuseLoc = glGetUniformLocation(containerShader.Program, "dirLight.diffuse");
	Uint lightSpecularLoc = glGetUniformLocation(containerShader.Program, "dirLight.specular");
	glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(lightDiffuseLoc, 0.8f, 0.8f, 0.8f);
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.direction"), -0.2f,-1.0f,-0.3f);
}
void SetPointLight(Shader &containerShader, glm::vec3 pointLightPositions[5])
{
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[0].position"), pointLightPositions[0].x,pointLightPositions[0].y,pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[0].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[0].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[0].quadratic"), 0.032f);

		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[1].position"), pointLightPositions[1].x,pointLightPositions[1].y,pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[1].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[1].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[1].quadratic"), 0.032f);

		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[2].position"), pointLightPositions[2].x,pointLightPositions[2].y,pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[2].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[2].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[2].quadratic"), 0.032f);

		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[3].position"), pointLightPositions[3].x,pointLightPositions[3].y,pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[3].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLightPositions[3].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLight[3].quadratic"), 0.032f);
}

void SetFlushLight(Shader &containerShader)
{
	glUniform3f(glGetUniformLocation(containerShader.Program, "flushLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "flushLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "flushLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "flushLight.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "flushLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "flushLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "flushLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "flushLight.quadratic"), 0.032f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "flushLight.cutOff"), glm::radians(12.5f));
	glUniform1f(glGetUniformLocation(containerShader.Program, "flushLight.outerCutOff"), glm::radians(15.0f));
}

int main()
{
	GLFWwindow* window = InitWindow();

	const Char* vertexPath = "E:\\OpenGL\\OpenGL_test1\\Shader\\vertexShader.glsl";
	const Char* fragmentPath = "E:\\OpenGL\\OpenGL_test1\\Shader\\fragmentShader.glsl";

	const Char* lampVertex = "E:\\OpenGL\\OpenGL_test1\\Shader\\lampvertexShader.glsl";
	const Char* lampFragment = "E:\\OpenGL\\OpenGL_test1\\Shader\\lampFragmentShader.glsl";

	Shader containerShader(vertexPath, fragmentPath);
	Shader lampShader(lampVertex, lampFragment);

	GLuint containerVAO, texture1, texture2;
	SetContainerAttrib(containerShader, containerVAO, texture1, texture2);

	GLuint diffuseTexture = 0;
	GLuint specularTexture = 0;
	SetTextureAttrib(diffuseTexture, "container2.png");
	SetTextureAttrib(specularTexture, "container2_specular.png");

	// 分别设置diffuse贴图和specular贴图单元
	containerShader.Use();
	glUniform1i(glGetUniformLocation(containerShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(containerShader.Program, "material.specular"), 1);

	GLuint lampVAO;
	SetLampAttrib(lampShader, lampVAO);

	glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		do_movement();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		// 立方体
		containerShader.Use();

		// 光源位置
		//lightPos.x = cos(glfwGetTime() / 2.0f)*1.0f;
		//lightPos.y = sin(glfwGetTime() / 2.0f)*1.0f;

		// 用于specular光照的观察方向向量
		Uint viewPosLoc = glGetUniformLocation(containerShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
		// 物体材质属性设置
		Uint shinnessLoc = glGetUniformLocation(containerShader.Program, "material.shininess");
		glUniform1f(shinnessLoc, 32.0f);

		// 平行光的属性设置
		SetDirectionLight(containerShader);

		// 点光设置
		SetPointLight(containerShader, pointLightPositions);

		// 聚光灯设置
		SetFlushLight(containerShader);
		
		// 物体转换矩阵设置
		glm::mat4 model;
		glm::mat4  views = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		Uint model_Location = glGetUniformLocation(containerShader.Program, "model");
		Uint views_Location = glGetUniformLocation(containerShader.Program, "views");
		Uint projection_Location = glGetUniformLocation(containerShader.Program, "projection");

		glUniformMatrix4fv(views_Location, 1, GL_FALSE, glm::value_ptr(views));
		glUniformMatrix4fv(projection_Location, 1, GL_FALSE, glm::value_ptr(projection));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularTexture);

		glBindVertexArray(containerVAO);

		for (int i = 0; i < 10; ++i)
		{
			model = glm::mat4();
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (GLfloat)glm::radians((i+5)*20.0f), glm::vec3(1.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(model_Location, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// 光源绘制
		lampShader.Use();

		// 光源转换矩阵设置
		Uint modelLoc = glGetUniformLocation(lampShader.Program, "model");
		Uint viewLoc = glGetUniformLocation(lampShader.Program, "view");
		Uint projectionLoc = glGetUniformLocation(lampShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(views));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(lampVAO);
		for (int i = 0; i < 4; ++i)
		{
			model = glm::mat4();
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &containerVAO);
	glfwTerminate();
	
	return 0;
}



