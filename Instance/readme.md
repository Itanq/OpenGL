
## 实例化
当要渲染的多个物体具有同样的数据的时候,我们虽然可以使用坐标变换把它变换到不同的世界坐标然后使用循环来一个个的渲染,但当物体变得太多的时候显然不是很好的方法.

`glDrawArraysInstanced(),glDrawElementsInstanced()`配合`gl_InstanceID`可以很多好的解决这个问题.

另外,还可以使用实例数组的方式来一次渲染多个物体.


## 效果图
一次性渲染成千上万的小行星带

![instance](https://img1.doubanio.com/view/photo/photo/public/p2375193707.jpg)
