# Computational-Geometry
  学堂在线清华计算几何课程学习（邓俊辉）.Algorithm implementation code by Zhikai.

更新历史

## 20200405 
  OpenGL相关函数的使用 封装可视化函数
调用OpenGL非常简单，遵循下述流程即可。
```
OpenGLplot();
```
```
//下边的两个函数可重复调用，但必须保证在OpenGLplot和CloseGLplot之间调用
AddBufferPoints(vector<Point> Points, float sizepoint);//用于显示某一大小的点
AddBufferLines(vector<Point> Points, float LineWidth);//用于显示某一宽度的直线，首尾相接
```
```
CloseGLplot();
```

## 20200406 
  O(n^4)的凸包算法 to-left-test 极点的冒泡排序 Point的比较

## 20200407 
  O(n^3)的凸包算法 去除重复点算法

## 20200408 
  O(n)的ICPT算法 重复点的处理 更新冒泡排序算法 O(n)的CheckSorted算法

## 20200410 
  O(n^2)的IC凸包算法 有一些bug暂时没法解决

## 20200411 
  O(n)的LTL算法 部分JM算法

## 20200412 
  部分JM算法

## 20200413 
  未考虑共线的JM算法 280000个点10秒内完成 O(hn) output sensitive h为顶点个数

## 20200413 
  考虑共线的JM算法 考虑共线后存在数值计算的问题，tolefttest设置1e-10的阈值

## 20200414 
  部分Graham Scan算法

## 20200415 
  找到最低和最右的点O(n) 预冒泡排序 判断c是否在线段上 GrahamScan算法实现scan算法是O(n)复杂度，主要花费时间在预排序上 预排序最短能到O(nlogn)，虽然是线性复杂度，但是最终的速度还是取决于预排序的复杂度

## 20200428 
  前边提到的GrahamScan算法主要花费时间在预排序上，是因为预排序使用的冒泡排序O(n^2)，冒泡排序就非常费时间，因此现在把冒泡排序用归并排序（nlogn）代替，速度有显著提升！

  预排序是冒泡排序展示：

![image](https://github.com/Robotics-Zhikai/Computational-Geometry/blob/master/image/3.png)

![image](https://github.com/Robotics-Zhikai/Computational-Geometry/blob/master/image/4.png)

  预排序是归并排序展示：

![image](https://github.com/Robotics-Zhikai/Computational-Geometry/blob/master/image/1.png)

![image](https://github.com/Robotics-Zhikai/Computational-Geometry/blob/master/image/2.png)

  可以看到，通过修改预排序算法，显著提升了算法的速度！

  在上述OpenGL的实现中，可以看到有一串竖的和横的系列特殊点，可以看到算法对于这些特殊部分的处理鲁棒性还是比较强的。顶点用大的方块表示，点用小点来表示。

## 20200429 
  尝试用归并排序的思想对凸包问题进行解决。主要难点在如何将两个子凸包进行合并，只要保证合并的复杂度是线性的，就可以让整个问题以nlogn的复杂度进行解决。而要保证合并的复杂度是线性，则需要在线性时间内得到星形多边形，接着用线性的GrahamScan算法找到凸包点，进而即可合并。整个思路和归并排序是差不多的。

## 20200430 
  实现归并排序的思想对凸包问题进行解决遇到了超出想象的困难。尤其是归并，分为星星多边形的归并和1.5个多边形的归并，归并方法是不同的。同时，GS算法在对星星多边形进行处理时，需要注意下边的那个堆栈有可能弹的只剩一个元素，因为归并时并没有按照极角排序，是“坑坑洼洼”的，因此需要加上对此种情况的处理。

  经过一整天的思考修改，任然没有完成递归法的求解，主要还是卡在了类似于IC算法的bug上，切点需要考虑共线。1.5个多边形归并需要修改序号，使得一遍扫描能够全部规整，否则会出现漏点的情况。现在的问题集中在切点不只有两个，有四个，而且四个都不是共线的，进一步的，CH2慢慢就不是凸包了，我认为还是主要在1636-1830行的程序有问题，即判断切点，不排序的GS算法也可能有问题。目前的编程水平还是不能够完成这个任务，以后有机会再思考这个问题吧！

  也有收获，debug能力得到提升，get到了二分法加断点定位递归程序bug的技能。也体会到大事化小、小事化了的递归解决问题思想。

  总之，凸包问题用GS算法求解是最好的。25秒可以求解55W个点的凸包。

## 20200501 
  对昨天的问题还是不甘心就此罢了，为了整个算法的完整性，我将归并CH1 CH2的步骤用GS算法代替，完成分治、融合的递归算法，这样的算法比较慢，完成求解50W个点，需要用时78秒。O(n*(logn)^2),多出来的操作是每次不得不进行排序，排序就需要很大的复杂度，但是二路归并却不需要排序那么大的复杂度。之后有机会再弄吧！

## 20200511 
  新建GeometryIntersection文件夹，并添加相关代码。解决的是线段、凸包的碰撞检测、交点枚举等问题。在MotionPlaning中，比如在ompl运动规划库中，没有碰撞检测的代码模块，需要自己编写，这时候就可以用GometryIntersection的算法。今天先封装了segment类，包括一些基本操作。也用到了convexhull中的相关基本操作函数。

## 20200812
  开始进行线段求交和凸包求交算法的编写。抽象出一些基础的轮子：求凸包、优先级队列、OpenGL可视化。
  对于OpenGL可视化新添加了线段显示函数

## 20200813
  完成优先级队列的数据结构的建立工作 开始着手BBST的状态线扫描的BBST数据结构工作，需要学习一下邓俊辉的数据结构BBST部分以及C++的模板部分

## 20200817 0818
  在MATLAB实现时，发现convexhull.cpp to left test 的bug 和presortting的bug 进行了修复 大体上都是因为阈值的问题 对于数值求解时极端的一些情况会出错
