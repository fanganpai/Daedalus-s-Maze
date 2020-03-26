# Daedalus's Maze

# 代达罗斯的迷宫

![图示](Readme.assets/image-20200326123223663.png)

使用Qt5编写的简单小游戏，地图的连通性由自己实现的数据结构（并查集）来完成（思路参考了[这篇文章](https://www.cnblogs.com/bigsai/p/11571715.html)）

已知的问题：棋盘较大时容易在远离起点和终点处产生过多的空白；且必定生成连通度为1的图