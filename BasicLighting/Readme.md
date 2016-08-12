
## Phong光照模型
Phong光照模型主要由ambient(环境光),diffus(漫反射),specular(镜面反射)组成.

环境光表示的是物体周围环境光对的影响,影响较小,且不考虑某一个方向,所以只需要设置一个ambient因子即可.

漫反射主要考虑了光源方向的光对物体的影响,具有显著效果.原理图如下:

![diffuse](https://img1.doubanio.com/view/photo/photo/public/p2373350349.jpg)

图右边有一个光源,它所发出的光线落在物体的一个fragment上.我们需要测量这个光线与它所接触的fragment的角度.如果光线垂直于物体表面,
这束光对物体的影响会最大化(更亮).为了测量光线和fragment的角度,我们可以使用法线向量,它是垂直于fragment表面的一种向量;
两个向量之间的角度就能够使用向量点乘简单的计算出来.
**从而把其点乘的结果乘于光的颜色就可以作为Phong光照模型的diffuse成分了..**

## 效果图

![phong.png](https://img3.doubanio.com/view/photo/photo/public/p2369638462.jpg)
