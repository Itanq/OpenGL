#version 330 core
in vec2 TexCoords;
uniform sampler2D Texture;
out vec4 color;
void main()
{
    vec4 texColor = texture(Texture, TexCoords);
//    if(texColor.a<0.f)
//        discard;
    color = texture(Texture, TexCoords);
}
