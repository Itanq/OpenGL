#version 330 core
in vec2 TexCoords;
uniform sampler2D Texture;
out vec4 color;
void main()
{
    color = vec4(texture(Texture, TexCoords));
}