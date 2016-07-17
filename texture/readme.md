
每一个纹理叫做一个纹理单元,一个纹理坐标可以处理多个纹理单元.
绑定纹理之前要先使用glActiveTexture()激活相应的纹理单元...
默认激活纹理单元0...GL_TEXTURE0 ~ GL_TEXTURE15
像素着色器可以通过采样器sampler来获取纹理对象,它以纹理类型做后缀,,比如:samper1D,sampler2D,sampler3D
然后再像素器里面可以通过texture(纹理采样器,纹理坐标)来采样纹理颜色...

可以使用glUniform1i()来确定纹理单元的位置....



纹理没有加载出来的错误:

一般是使用glGetUniformLocation()的时候,纹理的名字拼错了.
或者是加载纹理图片的时候,图片的路径名写错了.

