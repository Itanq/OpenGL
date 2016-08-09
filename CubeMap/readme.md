
## CubeMap

立体贴图可以实现3D效果的场景,因为一个立体有六个面,所以,一个立体贴图由6个2D纹理组成,所以在创建立体贴图和其他贴图时的不同在于,我们需要调用`过来TexImage2D()`六次,每次把纹理目标参数设置为立体贴图特定的面..

立体贴图的六个纹理目标:

| 纹理目标（Texture target）	    |方位
| -----------------------           |---
| GL_TEXTURE_CUBE_MAP_POSITIVE_X	|右
|-------------------------          |---
| GL_TEXTURE_CUBE_MAP_NEGATIVE_X	|左
|-------                            |---
| GL_TEXTURE_CUBE_MAP_POSITIVE_Y	|上
|---------                          |---
| GL_TEXTURE_CUBE_MAP_NEGATIVE_Y	|下
|----------                         |---
| GL_TEXTURE_CUBE_MAP_POSITIVE_Z	|后
|----------                         |
| GL_TEXTURE_CUBE_MAP_NEGATIVE_Z	|前

因为它们是依次递增的整形,所以,可以从`GL_TEXTURE_CUBE_MAP_POSITIVE_X`开始依次加一来递增设置各个纹理目标.

立体贴图用以给3D立方体贴上纹理,可以用立方体的纹理坐标进行采样,当一个立方体的中心位于原点,**它的每一个位置向量也就是以原点为起点的方向向量就是我们要得到的某个位置的纹理值,所以,我们只需提供位置向量,而无需纹理坐标**

在像素着色器设置采样器的时候为`samplerCube`

在绘制的时候,为了把它作为背景,需要用`glDepthMask(GL_FALSE)`来**关闭深度写入**...


立体贴图做背景的时候是一个巨大的立方体,所以还可以实现反射和折射的效果...

原理如下图所示;

反射原理图:

![reflect](https://img3.doubanio.com/view/photo/photo/public/p2372530513.jpg)

不难看出,我们基于观察向量$I$和法向量$N$计算出反射向量$R$,然后使用反射向量$R$从立体贴图中进行采样,从而实现反射的效果.
```
#version 330 core
in vec3 Normal;
in vec3 Position;
out vec4 color;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    color = texture(skybox, R);
}
```

折射原理图:

![refract](https://img1.doubanio.com/view/photo/photo/public/p2372530687.jpg)

折射和反射类似,计算的时候,采用`refract(观察向量,法向量,折射率)`来计算折射向量即可..


## 效果

3D贴图效果

![1](https://img3.doubanio.com/view/photo/thumb/public/p2372531380.jpg)

反射效果

![2](https://img1.doubanio.com/view/photo/thumb/public/p2372530509.jpg)

折射效果

![3](https://img3.doubanio.com/view/photo/thumb/public/p2372530511.jpg)
