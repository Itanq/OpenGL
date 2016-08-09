
## About Include
> 用于存放自定义的一些头文件..

## About CreatWindow
> 用glfw和glew创建一个空的OpenGL窗口


## About tirangle
> 用OpenGL创建一个三角形,学习了OpenGL的顶点缓冲对象VBO,顶点数组对象VAO.

  学习了采用OpenGL3.0绘制图形的一些基础知识以及计算机图形学的一些基础知识.

  认识图形渲染的各个阶段,认识着色器

  [详情](https://github.com/Itanq/OpenGL/tree/master/triangle)

## About ManyTriangle
> 用OpenGL创建多个三角形,主要是对索引缓冲对象EBO的学习..

  [详情](https://github.com/Itanq/OpenGL/tree/master/manyTriangle)

## About shaderUniform
> 学习了着色器中的uniform变量的知识.进一步认识了OpenGL中各种缓冲对象的作用.
  掌握了顶点数组对象中对顶点数据的多属性处理..

  [详情](https://github.com/Itanq/OpenGL/tree/master/shaderUniform)

## About texture
> 学习了OpenGL中对纹理的处理方法.并且掌握了多纹理单元的处理方法.感受到了纹理

  处理方式和顶点缓冲对象处理方式的相同之处...都是通过ID引用来对数据进行操作,

  只需在每次需要用的时候绑定相应的ID,用完之后解绑相应的ID,就不会影响后面的操作..

  [详情](https://github.com/Itanq/OpenGL/tree/master/texture)

## About transform
> 学习了变换矩阵在OpenGL的"动画"中的作用.了解了矩阵对OpenGL变换的意义..

  [详情](https://github.com/Itanq/OpenGL/tree/master/transform)

## About SpaceCoord
> 在顶点最终到达屏幕的过程中,必须经历五个空间:**本地空间**,**世界空间**,**观察空间**,**裁切空间**,**屏幕空间**

  各个空间的示例图如下
  ![spacecoord](https://img3.doubanio.com/view/photo/photo/public/p2368187954.jpg)

  由上可知,当我们想要渲染多个不同的物体的时候,不需要重新创建顶点属性,只需要建立几个不同的模型矩阵,

  然后,通过模型矩阵的变换,就可以把它放置在世界空间中不同位置,

  比如SpaceCoord/main.cpp中渲染的十个立方体其实就是通过创建十个模型矩阵来生成的...

  [详情](https://github.com/Itanq/OpenGL/tree/master/SpaceCoord)

## About Camera
> 物体在各个空间的变换必须经过各个矩阵来实现.如果,我们想让物体绕某个点转动的时候,只有动态的改变视图矩阵的值即可

  比如,对于SpaceCoord/main.cpp的代码我们把其中的视图矩阵写成如下即可实现立方体自传的同时绕圆点以y轴旋转
  ```
  // 在xz平面构建一个半径是10的圆
  Float radius = 10.f;
  Float camX = sin(glfwGetTime())*radius;
  Float camZ = cos(glfwGetTime())*radius;
  views = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
  ```

  当物体需要从世界空间变换到观察者空间中时,主要是通过视图矩阵来变换的,我们可以创建一个摄像机类来简化创建视图矩阵的过程..

  3D空间中物体的所有的旋转都可以通过三个**欧拉角**来实现

  [详情](https://github.com/Itanq/OpenGL/tree/master/Camera)

## About Color
  学习OpenGL中光源是如何影响物体的颜色的.我们所看到的物体的颜色其实是物体所反射的颜色,并不是物体本身的颜色.

  我看所看到的物体的颜色就是物体本身的颜色乘于光源的颜色,也就是它所反射的颜色..

  [详情](https://github.com/Itanq/OpenGL/tree/master/Color)

## About BasicLighting
  学习OpenGL的基本光照模型.Phong光照模型包括三部分: **环境光**,**漫反射**,**镜面反射**.环境光只要把光源乘以一个因子就可以了.

  漫反射表示光源与fragment距离对光照效果的影响.所以,离光源越近的点,光的效果越明显.所以,计算漫反射需要计算法线向量,光线方向两个向量.

  镜面反射不仅需要依据光线的方向和物体的法线方向,同样还要考虑观察的方向.主要模拟有光泽物体光照下产生的亮点..

  [详情](https://github.com/Itanq/OpenGL/tree/master/BasicLighting)

## About Material
  学习不同的材质对光照的不同影响

  [详情](https://github.com/Itanq/OpenGL/tree/master/Material)

## Abount LightMaps
  每个物体的不同部位都拥有不同的材质属性,光照时产生不同程度的效果,为了精确控制一个物体不同部位对diffuse和specular光的反应程度,

  可以用diffuse贴图和specular贴图来解决,其实就是给物体加一个纹理,然后通过纹理采样来给每个fragment索引独立颜色值即可..

  [详情](https://github.com/Itanq/OpenGL/tree/master/LightMaps)

## About LightCastes
  学习OpenGL中不同光源的光照效果,**平行光**,**点光**,**聚光灯**...

  其中平行光相对简单一点的,只需要考虑光的方向即可.

  点光和LightMaps实现的光差不多,但是要考虑到光随着距离的增加的衰减

  聚光灯主要是有一个光照射的方向向量和聚光灯的照射半径,所以,每个fragment与光源的方向的方向向量和聚光灯的方向向量就类似前面的点光了,
  只是fragment和光源反了一下位置而已...

  [详情](https://github.com/Itanq/OpenGL/tree/master/LightCastes)


## About MultiLight
  在一个场景中同时设置多个光源,为了方便,我们可以给每个不同的光源设置独立的uniform结构体,独立的计算照明函数即可..

  [详情](https://github.com/Itanq/OpenGL/tree/master/MultiLight)


## About DepthTest
  深度测试的学习,大多数情况下,深度测试都是不能缺少的有用的技术.

  [详情](https://github.com/Itanq/OpenGL/tree/master/DepthTest)
  

## About Stencil
  模板测试学习,可以实现一个特别有用的功能,绘制物体的轮廓.

  [详情](https://github.com/Itanq/OpenGL/tree/master/Stencil)


## Abount Blending
  混合技术,也叫物体透明技术.在渲染半透明或透明物体的时候非常有用.可以实现现实中玻璃的效果.
  混合需要注意的是渲染的**顺序很重要**

  [详情](https://github.com/Itanq/OpenGL/tree/master/Blending)


## About Framebuffer
  帧缓冲就是前面学习的颜色缓冲,深度缓冲,模板缓冲的结合,非常重要,可以实现各种后处理特效.

  [详情](https://github.com/Itanq/OpenGL/tree/master/Framebuffer)


## About CubeMap
  立体贴图可以实现3D场景的效果,可以创建更加真实的场景效果..

  [详情](https://github.com/Itanq/OpenGL/tree/master/CubeMap)
