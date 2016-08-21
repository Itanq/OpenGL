#version 330 core
in vec2 TexCoords;

out vec4 fColor;

uniform sampler2D texture_diffuse;
void main()
{
    fColor = vec4(texture(texture_diffuse, TexCoords));
}
