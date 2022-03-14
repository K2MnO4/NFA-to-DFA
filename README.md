**解决过程**

1. 声明：
   - 用$m$表示边数；
   - $cnt$表示当前已有状态集合的个数；
   - $st_{i, j}$表示第$i$个状态集合的顶点情况，第$0$个的编号为$A$，并且用二进制表示，例如$A = {0, 1 ,3}$，则二进制表示为1101（0表示不存在，1表示存在），表示位数规定为N = 1000位，那么$st_{0, 0} = 1, st_{0, 1} = 1, st_{0, 2} = 0, st_{0, 3} = 1, st_{0, x_{x= 4}^N } = 0$；
   - 哈希表$vis$判断一个顶点状态（01串）是否存在，即一个状态集合是否已经存在，哈希表$mp$存储第$i$个状态集的顶点状态；
   - 邻接表$g$存储NFA有向图；
   - $sgSet$存在状态转移符号集合；
   - $ans_{i, j}$存储第$i$个状态集合$S_1$经过第$j$个状态转移符号得到的状态集合$S_2$，若$S_2$不存在，则用"#"表示；
   - 函数$string ~ Move(int ~ pos, char ~ sg);$实现$Move(T, sg)$的过程，即状态集$T$经过符号$sg$转移后得到的状态集$T'$；
   - 函数$void ~dfs(int ~ u); $用来寻找$\epsilon-closure(u)\{u \in T'\}$，即从顶点编号为$u$出发经过多次(1、2、3...次)$\epsilon$转换得到的状态集合$T''$；
   - 函数$int ~ checkState();​$判断当前需要判断的状态集$T''​$是否已经存在 。
2. 首先读入一张NFA的有向图，并把所有的状态转移符号(除空转移$\epsilon$)放入$sgSet$中，直到读入到顶点编号为-1时结束读入；
3. 接着寻找初始状态集合$A$即编号0的集合($\epsilon-closure(0)$)，并标记该状态集；
4. 枚举所有状态符号，进行每个符号的$Move(T, sg)$操作得到状态集$T'$，再进行$\epsilon-closure(u)\{u \in T'\}$操作得到状态集$T''$，最后需要进行判断$T''$是否为新状态集；ps：特别要注意的是，若$T''$为空或者重复，因为该状态并非新状态，所以需要把之前$dfs$操作中$st_{cnt}$清空，以便下一个状态集使用$st_{cnt}$来存在其顶点状态；
5. 最后输出DFA的转换表即可。
6. 时间复杂度为：$O(N^3)$。