
## 混合

混合可以用来实现透明物体和半透明物体的的渲染,所以也物体透明技术

**透明**是指物体呈现出一种来自不同浓度的自身颜色和它后面物体的颜色的混合色.

首先,我们应该要以GL_RGBA的格式来加载透明纹理.然后可以在GLSL中使用discard语句来丢弃alpha值小于某个值的fragment
这种方式只能渲染完全透明物体的纹理,所以,为了渲染不同透明级别的纹理,我们可以开启混合.

openGL以下面的方程混合:
$C_result=C_source*F_source+C_destination*F_destination$
. $C_source$: 源颜色向量,来自纹理本来的颜色
. $C_destination$: 目标颜色向量,存储在颜色缓冲中的颜色向量
. $F_source,F_destination$: 源因子和目标因子,设置了源和目标颜色对结果颜色的alpha值的影响.

源颜色和目标颜色不能改变,但我们可以通过'glBlendFunc(sFactor,dFactor)'来设置源和目标颜色的因子.

要让混合在多物体上有效果,我们必须要渲染远处的物体,后渲染近处的物体.

当无透明度物体和透明物体一起绘制的时候,通常要遵循以下原则:

1. 先绘制所有不透明物体.
2. 为所有透明物体排序.
3. 按顺序绘制透明物体.

一种排序透明物体的方式是,获取一个物体到观察者透视图的距离.

## 效果
草是全透明的,可以直接用discard命令丢弃相应的fragment就可以,不需要开启混合
![blending1](https://img3.doubanio.com/view/photo/photo/public/p2372248532.jpg)
玻璃是半透明,需要开启混合,且是多物体混合,所以需要注意顺序.
![blending2](https://img3.doubanio.com/view/photo/photo/public/p2372248533.jpg)
