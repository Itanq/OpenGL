#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

// 各光照元素的属性
struct Light
{
    /*
    vec3 position;
    vec3 direction; // 定向光即平行光,故不需要光的位置,只需要光的方向即可
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // 点光.... 实现光随着距离变大而衰减的变量
    float constant;
    float linear;
    float quadratic;
    */

    // 聚光灯
    vec3 position;
    vec3 direction;
    float cutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

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

    vec3 lightDir = normalize(light.position - FragPos);
    
    float theta = dot(lightDir, normalize(-light.direction));

    if(theta > light.cutOff)
    {
        // 模拟环境光照
        vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

        // 模拟漫反射
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(-light.direction);
        //vec3 lightDir = normalize(light.position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

        // 模拟镜面反射
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
        vec3 specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;

        // 点光衰减公式
        float distance = length(light.position-FragPos);
        float attenuation = 1.0f/(light.constant + light.linear*distance+light.quadratic*(distance*distance));

        //ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        vec3 ans = (ambient + diffuse + specular);
        color = vec4(ans, 1.0f);
    }
    else
    {
        color = vec4(light.ambient*vec3(texture(material.diffuse, TexCoords)), 1.0f);
    }
}
