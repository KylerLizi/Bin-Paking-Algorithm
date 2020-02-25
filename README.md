# Bin-Paking-Algorithm 2019.12.01-2020.1.31
# 二维装箱算法
基于`二叉树`与`叶子链表`算法思维对输入的矩形数据进行动态排版，缩进式树状打印与Opengl绘制显示排版结果。<br>
实现了将全部的矩形紧凑封装在一个近似正方形的空间中，提高了空间利用率，减少了内存资源的浪费。<br>

### 配置：<br>
简单的使用了Glut库进行Opengl绘制窗体与矩形，首次编译需要[配置glut环境](https://blog.csdn.net/qq_31788759/article/details/104342559)，这也是我博客的博文，求关注嘿嘿<br>
配置结束后，记得将解决方案配置设置为`Debug x86`，否则glut.h文件会找不到<br>

### 内含：<br>
* 7个数据集，数据需为整数，5和7数据集复杂度高，新增了叶子链表查询后才跑的通<br>

### 功能：<br>
* 按照近似正方形的规则，添加矩形时会`自适应的不断扩充`外接矩形的大小<br>
* 按照`宽度/高度/面积/最大边`排序算法对矩形数据集排序<br>
* 调用`windows文件浏览窗口`，选择本地txt数据集作为输入(矩形格式为 宽 高 数量)<br>
* 使用`Opengl显示列表`在窗口中绘制`空间利用率`<br>
* `一次性绘制`或`左键点击逐个绘制`矩形排版结果(在glDraw.cpp中通过define设置)<br>

### 运行结果
数据集5<br>
`2 2 256`<br>
`4 4 128`<br>
`8 8 64`<br>
`16 16 32`<br>
`32 32 16`<br>
`64 64 8`<br>
`128 128 4`<br>
`256 256 2`<br>
![5powersOf2](https://github.com/ColorGalaxy/Bin-Paking-Algorithm/raw/master/Screenshot/5powersOf2.png)<br>
数据集7<br>
`100 100 3`<br>
`60 60 3`<br>
`50 20 20`<br>
`20 50 20`<br>
`250 250 1`<br>
`250 100 1`<br>
`100 250 1`<br>
`400 80 1`<br>
`80 400 1`<br>
`10 10 100`<br>
`5 5 500`<br>
![7complex](https://github.com/ColorGalaxy/Bin-Paking-Algorithm/raw/master/Screenshot/7complex.png)<br>
