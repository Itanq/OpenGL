#version 330 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT{
    out vec2 TexCoords;
    out vec3 FragCoord;
    out vec3 Normal;
}fs_out;

void main()
{
    gl_Position = projection * view * model * vec4(position,1.0f);
    fs_out.TexCoords = texCoords;
    fs_out.Normal = normalize(normal);
    fs_out.FragCoord = vec3(model * vec4(position,1.0f));
}
