
## About Include
> 用于存放自定义的一些头文件..

## About CreatWindow
> 用glfw和glew创建一个空的OpenGL窗口


## About tirangle
> 用OpenGL创建一个三角形,学习了OpenGL的顶点缓冲对象VBO,顶点数组对象VAO.

  学习了采用OpenGL3.0绘制图形的一些基础知识以及计算机图形学的一些基础知识.

  认识图形渲染的各个阶段,认识着色器


## About ManyTriangle
> 用OpenGL创建多个三角形,主要是对索引缓冲对象EBO的学习..

## About shaderUniform
> 学习了着色器中的uniform变量的知识.进一步认识了OpenGL中各种缓冲对象的作用.
  掌握了顶点数组对象中对顶点数据的多属性处理..


## About texture
> 学习了OpenGL中对纹理的处理方法.并且掌握了多纹理单元的处理方法.感受到了纹理

  处理方式和顶点缓冲对象处理方式的相同之处...都是通过ID引用来对数据进行操作,

  只需在每次需要用的时候绑定相应的ID,用完之后解绑相应的ID,就不会影响后面的操作..


## About transform
> 学习了变换矩阵在OpenGL的"动画"中的作用.了解了矩阵对OpenGL变换的意义..


## About SpaceCoord
> 在顶点最终到达屏幕的过程中,必须经历五个空间:**本地空间**,**世界空间**,**观察空间**,**裁切空间**,**屏幕空间**

  各个空间的示例图如下
  ![spacecoord](https://img3.doubanio.com/view/photo/photo/public/p2368187954.jpg)

  由上可知,当我们想要渲染多个不同的物体的时候,不需要重新创建顶点属性,只需要建立几个不同的模型矩阵,

  然后,通过模型矩阵的变换,就可以把它放置在世界空间中不同位置,

  比如SpaceCoord/main.cpp中渲染的十个立方体其实就是通过创建十个模型矩阵来生成的...


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


## About Color
  学习OpenGL中光源是如何影响物体的颜色的.我们所看到的物体的颜色其实是物体所反射的颜色,并不是物体本身的颜色.
  我看所看到的物体的颜色就是物体本身的颜色乘于光源的颜色,也就是它所反射的颜色..
