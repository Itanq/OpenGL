#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

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

// 平行光
struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

// 计算平行光输出的光照颜色
vec3 CalcuDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // 漫反射强度
    float diff = max(dot(normal, lightDir), 0.0);

    // 镜面反射强度
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    return (ambient+diffuse+specular);
}

// 点光
struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // 点光.... 实现光随着距离变大而衰减的变量
    float constant;
    float linear;
    float quadratic;
};
uniform PointLight pointLight[5];

vec3 CalcuPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // 计算漫反射强度
    float diff = max(dot(normal, lightDir), 0.0);

    // 计算镜面反射强度
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient*vec3(texture(material.diffuse,TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular*spec*vec3(texture(material.specular,TexCoords));

    // 计算衰减量
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f/(light.constant + light.linear*distance + light.quadratic*(distance*distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient+diffuse+specular);
}

struct FlushLight
{

    // 聚光灯
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform FlushLight flushLight;
vec3 CalcuFlushLight(FlushLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // 漫反射
    float diff = max(dot(normal, lightDir), 0.0f);

    // 镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // 计算衰减量
    float distance = length(light.position = fragPos);
    float atten = 1.0f/(light.constant+light.linear*distance+light.quadratic*(distance*distance));
    
    // 计算聚光灯的范围
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta-light.outerCutOff)/epsilon,0.0,1.0f);

    vec3 ambient = light.ambient*vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse,TexCoords));
    vec3 specular = light.specular*spec*vec3(texture(material.specular,TexCoords));

    ambient *= atten * intensity;
    diffuse *= atten * intensity;
    specular *= atten * intensity;
    return (ambient+diffuse+specular);
}

out vec4 color;

void main()
{
    vec3 normal = normalize(-Normal);
    vec3 viewDir = normalize(viewPos-FragPos);

    // 计算平行光
    vec3 ans = CalcuDirLight(dirLight, normal, viewDir);

    // 计算点光
    for(int i=0; i<4; ++i)
        ans += CalcuPointLight(pointLight[i], normal, FragPos, viewDir);

    // 计算聚光灯
    ans += CalcuFlushLight(flushLight, normal, FragPos, viewDir);
    color = vec4(ans, 1.0f);
}

