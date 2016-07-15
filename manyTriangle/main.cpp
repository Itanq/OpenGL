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
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT,"Triangle",nullptr,nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyboard);

	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	return window;
}

int main()
{
	GLFWwindow* window = InitWindow();
	
	const Char* vertexPath = "E:\\CodeOpenGL\\triangle\\vertexShader.shader";
	const Char* fragmentPath = "E:\\CodeOpenGL\\triangle\\fragmentShader.shader";


	// 三角形的顶点数据
	Float vertices[] = {
		-0.5f/2.0, 1.0f/2.0,0.0f,
		-0.5f/2.0, 0.5f/2.0,0.0f,
		 1.0f/2.0, 0.5f/2.0,0.0f,
		 0.5f/2.0, 0.5f/2.0,0.0f,
		 0.5f/2.0,-1.0f/2.0,0.0f,
		 0.5f/2.0,-0.5f/2.0,0.0f,
		-1.0f/2.0,-0.5f/2.0,0.0f,
		-0.5f/2.0,-0.5f/2.0,0.0f
	};

	// 各个三角形的索引数据
	Uint indices[] = {
		0,1,2,
		2,3,4,
		4,5,6,
		6,7,0,
		1,3,7,
		1,7,5,
		1,3,5
	};

	// 加载三角形的顶点着色器和像素着色器
	Shader ourShader(vertexPath, fragmentPath);

	Uint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// 把顶点数据复制到顶点缓冲区中
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 把索引数据复制到索引缓冲区中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(Float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 线框模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(1.0f, 0.5f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 21, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
