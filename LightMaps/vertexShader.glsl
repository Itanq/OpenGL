#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;


out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 views;
uniform mat4 projection;

void main()
{
	gl_Position = projection*views*model*vec4(position, 1.0f);
    // 在世界空间中计算fragment位置
    FragPos = vec3(model*vec4(position,1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoords = texCoord;
}
