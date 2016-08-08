#version 330 core
in vec2 TexCoords;
uniform sampler2D Texture;
out vec4 color;

const float offset = 1.0 / 300;  
void main()
{
    // 反相效果
    // color = vec4(1.0f - texture(Texture, TexCoords), 1.0f);
    // 灰度效果
    // color = texture(Texture, TexCoords);
    // float average = (color.r+color.g+color.b) / 3.0f;
    // color = vec4(average, average, average, 1.0f);
    // Kernal效果
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right    
    );
 
    /*
       // Kernal特效
       float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
        );
    */
    /*
       // 模糊特效
        float kernel[9] = float[](
            1.0 / 16, 2.0 / 16, 1.0 / 16,
            2.0 / 16, 4.0 / 16, 2.0 / 16,
            1.0 / 16, 2.0 / 16, 1.0 / 16  
        ); 
    */
    float kernel[9]=float[](
            1,1,1,
            1,-8,1,
            1,1,1
            );
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(Texture, TexCoords.st + offsets[i]));
    }
    vec3 col;
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
    color = vec4(col, 1.0);
}
