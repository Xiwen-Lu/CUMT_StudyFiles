`11.5` 更新，加入了四次课内实验的代码。词法分析、递归下降分析、LR语法分析、中间代码生成。

---
上课第二周左右，谢红侠老师布置了第一次加平时分作业，期间积极性并不高，虽然一直挂念着，最后还是拖到了9月底才完成。不过全部算法和内容皆是自己思考所得，还是感觉非常兴奋的！

It is about the first assignment of principles of compilation which the teacher gave us at the  second week of this semester. She stressed/laid  emphasis that whoever can complete this homework would get some extra credits as rewards. Although I was striving for it, my initiative was not as high as l had expected and eventually, I put it off till the end of September. Nonetheless, it is worth mentioning that all of the codes were original , except for a little bit of reference of the usage of STL from the web. The sense of achievement is rather fabulous and fantastic!

【NFA的确定化】
思路：
1.	存储NFA图结构使用状态邻接表，矩阵行列均为状态，对应元素为转移字符；
2.	计算每个节点的e-closure时，使用一个队列维护，进行广度优先搜索（优先遍历相邻状态）
3.	使用set容器存储状态集合、e闭包（方便插入去重）
4.	迭代时，使用可变长数组vector。随着计算，不断扩充，直至指针指向末尾（无新集合加入），跳出循环

【运行结果】

![NFA的确定化](https://github.com/LuXiwen1999/CUMT_StudyFiles/blob/master/%E7%BC%96%E8%AF%91%E5%8E%9F%E7%90%86/NFA%E7%9A%84%E7%A1%AE%E5%AE%9A%E5%8C%96_%E8%BF%90%E8%A1%8C%E5%9B%BE.jpg)


【DFA的最小化】
思路：
1. （关键）找到需要更新子集号的行，从该行往下的所有子集号加一，即可完成一次更新
2.  使用数组v存储一遍搜寻时，是否有行需要更新子集（find(1)不返回末尾指针）
3.  初始存储矩阵时需要存储初始子集状态
注：最小化中1处思路关键，代码中以注释形式保留了编写时对于程序运行的cout输出观察，删去61行注释符号，即可看到。

【运行结果】

![DFA的最小化](https://github.com/LuXiwen1999/CUMT_StudyFiles/blob/master/%E7%BC%96%E8%AF%91%E5%8E%9F%E7%90%86/DFA%E7%9A%84%E6%9C%80%E5%B0%8F%E5%8C%96_%E8%BF%90%E8%A1%8C%E5%9B%BE.jpg)
