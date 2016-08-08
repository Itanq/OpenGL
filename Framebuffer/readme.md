
## 帧缓冲

帧缓冲就是前面学到的颜色缓冲,深度缓冲,模板缓冲的结合,**非常重要**,能够实现各种后处理特效..

前面都是在默认的帧缓冲中渲染的物体...在我们创建一个窗口的时候,glfw就自动为我们配置了默认的帧缓冲...

帧缓冲也是OpenGL中的一种对象.和前面学的所有的OpenGL对象一样,**都需要先生成,再绑定,然后配置,最后解绑,渲染的时候再绑定**这样的结构..

在配置阶段需要注意的是:

* 我们必须往里面加入至少一个附件(颜色、深度、模板缓冲).
* 其中至少有一个是颜色附件.
* 所有的附件都应该是已经完全做好的(已经存储在内存之中).
* 每个缓冲都应该有同样数目的样本.

当创建附件的时候,我们有两种方式: 纹理对象和渲染缓冲对象(也是一种OpenGL对象)


然后,我们把整个场景渲染到了一个单一的纹理上,就可以简单的通过纹理数据来创造各种后处理特效...

## 效果

反相效果
![faxiang](https://img3.doubanio.com/view/photo/photo/public/p2372345201.jpg)

灰度效果
![huidu](https://img3.doubanio.com/view/photo/photo/public/p2372345202.jpg)

锐化效果
![kernel](https://img1.doubanio.com/view/photo/photo/public/p2372345199.jpg)

模糊效果
![blur](https://img3.doubanio.com/view/photo/photo/public/p2372345203.jpg)

边缘效果
![bianyuan](https://img3.doubanio.com/view/photo/photo/public/p2372345204.jpg)


