#include<cmath>
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<SOIL.h>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "shader.h"

typedef GLint Int;
typedef GLuint Uint;
typedef GLchar Char;
typedef GLfloat Float;

Uint WIDTH = 500, HEIGHT = 450;
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* InitWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "transform", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyboard);

	glewExperimental = GL_TRUE;
	glewInit();
	return window;
}


int main()
{
	GLFWwindow* window = InitWindow();

	const Char* vertexPath = "E:\\OpenGL\\OpenGL_test1\\Shader\\vertexShader.sh";
	const Char* fragmentPath = "E:\\OpenGL\\OpenGL_test1\\Shader\\fragmentShader.sh";

	Shader ourShader(vertexPath, fragmentPath);

	Float vertices[] = {
		-0.5f,-0.5f,0.0f,		0.0f,0.0f,
		-0.5f, 0.5f,0.0f,		0.0f,1.0f,
		 0.5f, 0.5f,0.0f,		1.0f,1.0f,
		 0.5f,-0.5f,0.0f,		1.0f,0.0f
	};

	Uint indices[] = {
		0,1,2,
		0,2,3
	};
	
	Uint VAO, VBO, EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	//************ TEXTURE **************//

	Uint texture1, texture2;

	// texture 1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width=0, height=0;
	const Char* imagePath = "E:\\OpenGL\\OpenGL_test1\\Images\\wall.jpg";
	unsigned char* image = SOIL_load_image(imagePath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// texture 2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	imagePath = "E:\\OpenGL\\OpenGL_test1\\Images\\awesomeface.png";
	image = SOIL_load_image(imagePath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		glm::mat4 trans;
		trans = glm::rotate(trans, (GLfloat)glm::radians(glfwGetTime())*50.f, glm::vec3(1.0f, 1.0f, 0.0f)); // 绕y=x轴旋转
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f)); // 沿x,y,z,轴缩放0.5倍

		Uint transLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transLoc,1,GL_FALSE,glm::value_ptr(trans));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"),0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"),1);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
