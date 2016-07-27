#version 330 core
in vec2 TexCoord;

out vec4 color;

// Texture samplers
//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // 两个纹理的线性混合取色
	//color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
    color = vec4(lightColor * objectColor, 1.0f);
}
