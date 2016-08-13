#version 330 core

in VS_OUT{
    in vec2 TexCoords;
    in vec3 FragCoord;
    in vec3 Normal;
}fs_in;

uniform sampler2D planeTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool blinn;

out vec4 color;
void main()
{

    vec3 objectColor = vec3(texture(planeTexture, fs_in.TexCoords));
    // ambient
    vec3 ambient = 0.05f * objectColor;
    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragCoord);
    float diff = max(dot(lightDir, fs_in.Normal), 0.0f);
    vec3 diffuse = diff * objectColor;
    // specular
    vec3 ref = reflect(-lightDir, fs_in.Normal);
    vec3 viewDir = normalize(viewPos - fs_in.FragCoord);

    float spec=0.0f;
    if(blinn)
    {
        vec3 halfvector = normalize(ref + viewDir);
        spec = pow(max(dot(halfvector, fs_in.Normal),0.0f),32.0f);
    }
    else
    {
        spec = pow(max(dot(viewDir, ref),0.0f),8.0f);
    }
    vec3 specular = vec3(0.3) * spec * objectColor;

    color = vec4(ambient+diffuse+specular, 1.0f);
}

