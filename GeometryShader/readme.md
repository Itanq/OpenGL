
## 几何着色器
几何着色器是顶点着色器后面运行的阶段,是可选的.但是很强大的,可以很容易的实现很多效果.

几何着色器的生成和创建和顶点,像素着色器一样.只是在创建的时候,选择生成几何着色器类型即可.

几何着色器起源码的结构如下:

```
#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 2) out;
 
void main() {    
    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0); 
    EmitVertex();
 
    gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
}
```

每个几何着色器开始位置我们需要声明输入的基本图形类型,这个输入是我们从顶点着色器中接收到的.我们在in关键字前面声明一个layout标识符.这个输入layout修饰符可以从一个顶点着色器接收以下基本图形值:

|points                 |绘制GL_POINTS基本图形的时候(1).
|--------               |---------
|lines:                 |当绘制GL_LINES或GL_LINE_STRIP(2)时.
|lines_adjacency:       |GL_LINES_ADJACENCY或GL_LINE_STRIP_ADJACENCY(4).
|triangles:             |GL_TRIANGLES, GL_TRIANGLE_STRIP或GL_TRIANGLE_FAN(3).
|triangles_adjacency :  |GL_TRIANGLES_ADJACENCYGL_TRIANGLE_STRIP_ADJACENCY(6).

这是我们能够给渲染函数的几乎所有的基本图形.括号里的数字代表一个基本图形所能包含的最少的顶点数.

当我们需要指定一个几何着色器所输出的基本图形类型时,我们就在out关键字前面加一个layout修饰符.和输入layout标识符一样,output的layout标识符也可以接受以下基本图形值:
> points,line_strip,triangle_strip

使用这3个输出修饰符我们可以从输入的基本图形创建任何我们想要的形状.

几何着色器同时希望我们设置一个它能输出的顶点数量的最大值(如果你超出了这个数值,OpenGL就会忽略剩下的顶点),我们可以在out关键字的layout标识符上做这件事.

## 效果

虽然很简单,但是下面效果是采用`glDrawArrays(GL_POINTS,0,4)`渲染的..

![g](https://img3.doubanio.com/view/photo/photo/public/p2372710024.jpg)

