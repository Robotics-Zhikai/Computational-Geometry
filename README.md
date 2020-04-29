# Computational-Geometry
学堂在线清华计算几何课程学习（邓俊辉）.Algorithm implementation code by Zhikai.

//Update record

20200405 OpenGL相关函数的使用 封装可视化函数

20200406 O(n^4)的凸包算法 to-left-test 极点的冒泡排序 Point的比较

20200407 O(n^3)的凸包算法 去除重复点算法

20200408 O(n)的ICPT算法 重复点的处理 更新冒泡排序算法 O(n)的CheckSorted算法

20200410 O(n^2)的IC凸包算法 有一些bug暂时没法解决

20200411 O(n)的LTL算法 部分JM算法

20200412 部分JM算法

20200413 未考虑共线的JM算法 280000个点10秒内完成 O(hn) output sensitive h为顶点个数

20200413 考虑共线的JM算法 考虑共线后存在数值计算的问题，tolefttest设置1e-10的阈值

20200414 部分Graham Scan算法

20200415 找到最低和最右的点O(n) 预冒泡排序 判断c是否在线段上 GrahamScan算法实现scan算法是O(n)复杂度，主要花费时间在预排序上 预排序最短能到O(nlogn)，虽然是线性复杂度，但是最终的速度还是取决于预排序的复杂度

20200428 前边提到的GrahamScan算法主要花费时间在预排序上，是因为预排序使用的冒泡排序O(n^2)，冒泡排序就非常费时间，因此现在把冒泡排序用归并排序（nlogn）代替，速度有显著提升！

预排序是冒泡排序展示：

![image](https://github.com/Robotics-Zhikai/Computational-Geometry/blob/master/image/3.png)

![image](https://github.com/Robotics-Zhikai/Computational-Geometry/blob/master/image/4.png)

预排序是归并排序展示：

![image](https://github.com/Robotics-Zhikai/Computational-Geometry/blob/master/image/1.png)

![image](https://github.com/Robotics-Zhikai/Computational-Geometry/blob/master/image/2.png)

可以看到，通过修改预排序算法，显著提升了算法的速度！

在上述OpenGL的实现中，可以看到有一串竖的和横的系列特殊点，可以看到算法对于这些特殊部分的处理鲁棒性还是比较强的。顶点用大的方块表示，点用小点来表示。

20200429 尝试用归并排序的思想对凸包问题进行解决。主要难点在如何将两个子凸包进行合并，只要保证合并的复杂度是线性的，就可以让整个问题以nlogn的复杂度进行解决。而要保证合并的复杂度是线性，则需要在线性时间内得到星形多边形，接着用线性的GrahamScan算法找到凸包点，进而即可合并。整个思路和归并排序是差不多的。

20200430 实现归并排序的思想对凸包问题进行解决遇到了超出想象的困难。尤其是归并，分为星星多边形的归并和1.5个多边形的归并，归并方法是不同的。同时，GS算法在对星星多边形进行处理时，需要注意下边的那个堆栈有可能弹的只剩一个元素，因为归并时并没有按照极角排序，是“坑坑洼洼”的，因此需要加上对此种情况的处理。