#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

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
    // texture(material.diffuse, TexCoords) 通过采样来获取物体的diffuse光照
    // texture(material.specular,TexCoords) 通过采样来获取物体的specular光照
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

uniform vec3 viewPos;

void main()
{



    // 模拟环境光照
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * lightColor.ambient;

    // 模拟漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightColor.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = lightColor.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // 模拟镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = vec3(texture(material.specular, TexCoords)) * spec * lightColor.specular;

    vec3 ans = (ambient + diffuse + specular);
    color = vec4(ans, 1.0f);
}
