
## Phong光照模型
Phong光照模型主要由ambient(环境光),diffus(漫反射),specular(镜面反射)组成.

### Ambient
环境光表示的是物体周围环境光对的影响,影响较小,且不考虑某一个方向,所以只需要设置一个ambient因子即可.

### Diffuse
漫反射主要考虑了光源方向的光对物体的影响,具有显著效果.原理图如下:

![diffuse](https://img1.doubanio.com/view/photo/photo/public/p2373350349.jpg)

图右边有一个光源,它所发出的光线落在物体的一个fragment上.我们需要测量这个光线与它所接触的fragment的角度.如果光线垂直于物体表面,
这束光对物体的影响会最大化(更亮).为了测量光线和fragment的角度,我们可以使用法线向量,它是垂直于fragment表面的一种向量;
两个向量之间的角度就能够使用向量点乘简单的计算出来.

因为可以看出,$\theta$角越大,光源对fragment的影响就越小,点乘的结果也就越小,**从而把其点乘的结果乘于光的颜色就可以作为Phong光照模型的diffuse成分了..**

### Specular

镜面反射除了依据光线的方向向量和fragment的法向量,同样也考虑到了视线的方向向量,即观察者是从哪个方向看物体的.原理图如下:

![specular](https://img3.doubanio.com/view/photo/photo/public/p2373396964.jpg)

显然,这次我们希望计算光向在每个fragment的放射向量(可以通过GLSL内建的reflect()函数计算),然后计算放射向量和观察视线方向的夹角$\theta$,同样,$\theta$值越小,specular高光的影响越大,这也是点乘的结果.

然后用它的$n$次幂,当然要确保点乘的结果不为负数(当视线方向和光源方向在同一侧的时候点乘的结果就变成负数了);来表达specular成分,$n$表示高光值..


## 效果图

![phong.png](https://img3.doubanio.com/view/photo/photo/public/p2369638462.jpg)
