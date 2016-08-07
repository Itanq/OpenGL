#version 330 core
in vec2 TexCoords;
uniform sampler2D Texture;
out vec4 color;

float LinearizeDepth(float depth)
{
    float near=0.1f;
    float far = 100.0f;
    float z = depth*2.0f-1.0f;
    return(2.0*near)/(far+near-z*(far-near));
}

void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z);
    color = vec4(vec3(depth),1.0f);
//    color = vec4(texture(Texture, TexCoords));
}
