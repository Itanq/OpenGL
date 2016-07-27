#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

// Texture samplers
//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

// 各光照元素的属性
struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light lightColor;

// 物体材质属性
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

uniform vec3 objectColor;

uniform vec3 viewPos;
void main()
{
    // 两个纹理的线性混合取色
	//color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);

    // 模拟环境光照
    vec3 ambient = material.ambient * lightColor.ambient;

    // 模拟漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightColor.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = (diff * material.diffuse) * lightColor.diffuse;

    // 模拟镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = (material.specular * spec) * lightColor.specular;

    vec3 ans = (ambient + diffuse + specular) * objectColor;
    color = vec4(ans, 1.0f);
}
