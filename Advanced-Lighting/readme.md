
## Blinn-Phong光照模型
Phong光照模型一般情况下都能产生很好的效果,且性能高效,但是当视线方向向量和法线方向向量之间的夹角大于$90^.$的时候,则会产生specular边缘区域迅速减弱的问题.

Blinn-Phong光照模型就可以防止那种情况发生,事实上,Blinn-Phong光照模型基本上和Phong光照模型是一样的,只是在specular模型上做了一点修正.它使用一个**半程向量**来防止上面大于$90^.$的问题.
原理图如下:

![blinn](https://img3.doubanio.com/view/photo/photo/public/p2373468114.jpg)

$H$向量就是其中的半程向量,它是视线向量和光源向量的**和向量**,是**单位向量**.半程向量和fragment的法向量月接近,则specular成分越大.

其他*aimbent*和*diffuse*部分则与Phong光照一样的计算方式...


## 效果

Phong光照模型

![Phong](https://img3.doubanio.com/view/photo/photo/public/p2373464730.jpg)

Blinn-Phong光照模型

![blinnPhong](https://img1.doubanio.com/view/photo/photo/public/p2373464729.jpg)

