#version 330 core
layout (points) in;
layout (triangle_strip,max_vertices=5)out;

in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;

// 通过叉乘获取垂直于两个向量的第三个向量
// 得到a,b向量所在平面的法向量
vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void build_house(vec4 position)
{
    fColor = gs_in[0].color;
    gl_Position = position + vec4(-0.2f, -0.2f, 0.0f, 0.0f);   
    EmitVertex();   
    gl_Position = position + vec4( 0.2f, -0.2f, 0.0f, 0.0f);
    EmitVertex();
    gl_Position = position + vec4(-0.2f,  0.2f, 0.0f, 0.0f);
    EmitVertex();
    gl_Position = position + vec4( 0.2f,  0.2f, 0.0f, 0.0f);
    EmitVertex();
    gl_Position = position + vec4( 0.0f,  0.4f, 0.0f, 0.0f);
    fColor = vec3(1.0f, 1.0f, 1.0f);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    build_house(gl_in[0].gl_Position);
}
