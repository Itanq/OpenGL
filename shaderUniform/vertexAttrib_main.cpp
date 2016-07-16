#include<cmath>
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include"myshader.h"

typedef GLint Int;
typedef GLuint Uint;
typedef GLchar Char;
typedef GLfloat Float;

Uint WIDTH = 800, HEIGHT = 700;

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* InitWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Uniform Var", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyboard);
	glfwSetInputMode(window, GLFW_CURSOR_DISABLED, GL_TRUE);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glewExperimental = GL_TRUE;
	glewInit();

	return window;
}

int main()
{

	GLFWwindow* window = InitWindow();

	const Char* vertexPath = "E:\\CodeOpenGL\\shaderUniform\\vertexShader1.shader";
	const Char* fragmentPath = "E:\\CodeOpenGL\\shaderUniform\\fragmentShader1.shader";

	Shader ourShader(vertexPath, fragmentPath);

	// 十字架顶点属性数据
	Float vertices[] = {
		// 顶点位置值		 顶点颜色值
		 0.000f, 0.75f,0.0f, 1.0f,0.0f,0.0f,
		-0.125f, 0.50f,0.0f, 0.0f,1.0f,0.0f,
		 0.125f, 0.50f,0.0f, 0.0f,0.0f,1.0f,

		-0.50f, 0.400f,0.0f, 0.0f,1.0f,0.0f,
		-0.50f, 0.150f,0.0f, 1.0f,0.0f,0.0f,
		-0.75f, 0.275f,0.0f, 0.0f,0.0f,1.0f,
		 
		 0.50f, 0.400f,0.0f, 0.0f,0.0f,1.0f,
		 0.75f, 0.275f,0.0f, 0.0f,1.0f,0.0f,
		 0.50f, 0.150f,0.0f, 1.0f,0.0f,0.0f,

		-0.125f,-0.50f,0.0f, 0.0f,1.0f,0.0f,
		 0.000f,-0.75f,0.0f, 1.0f,0.0f,0.0f,
		 0.125f,-0.50f,0.0f, 0.0f,0.0f,1.0f
	};

	// 十字架顶点索引数据
	Uint indices[] = {
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		1,9,11,
		1,2,9,
		2,9,11,
		3,4,8,
		3,4,6,
		4,6,8
	};// 30 vertex

	Uint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// 顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 索引数据
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 顶点位置属性设置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// 顶点颜色属性设置
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;
}
