#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

// Texture samplers
//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // 两个纹理的线性混合取色
	//color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);

    // 模拟环境光照
    float ambientStrength = 0.1f; // ambient因子
    vec3 ambient = ambientStrength * lightColor;

    // 模拟漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    // 模拟镜面反射
    float specularStrength = 0.3;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 ans = (ambient + diffuse + specular) * objectColor;
    color = vec4(ans, 1.0f);
}
