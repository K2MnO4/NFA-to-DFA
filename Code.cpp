#include<bits/stdc++.h>
#define debug(x) cout << "***" << x << endl
using namespace std;
const int N = 1000;
const int INF = 0x3f3f3f3f;

int m = 0; //边数
int cnt = 0; //状态集合个数
int st[N + 5][N + 5]; //用二进制表示每个状态集的状态
int ans[N][N]; //DFA转换表
map<string, int>vis; //判断状态是否存在
map<int, string>mp; //用哈希表存储每个状态集的状态
vector<pair<int, char>> g[N + 5];
set<char> sgSet; //状态转换字符集

void dfs(int u) //计算closure;
{
    if(st[cnt][u]) return; //剪枝
    st[cnt][u] = 1; //顶点u存在
    for(int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i].first;
        char sg = g[u][i].second;
        if('0' == sg) dfs(v);
    }
}

int checkState() //确认第cnt个状态集是否之前存在
{
    string s; //二进制序列表示该状态集
    for(int i = 0; i <= N; i++)
        s += (char)(st[cnt][i] + '0');
    if(s.find('1') == s.npos) return INF; //该状态集为空(找不到1)
    if(vis[s]) return vis[s]; //当前状态已经存在
    mp[cnt] = s; //存放第cnt个状态集的状态序列
    vis[s] = cnt; //标记状态序列s是第cnt个状态集
    cnt ++; //状态集数量增加
    return -1;
}

string Move(int pos, char sg) //Move(T, a)
{
    string s = mp[pos], res;
    for(int i = 0; i < s.size(); i++)
    {
        if('1' == s[i]) //该状态存在
        {
            int u = i; //状态集合T中的点
            for(int i = 0; i < g[u].size(); i++)
            {
                char v = (char)(g[u][i].first + '0');
                if(sg == g[u][i].second && res.find(v) == res.npos) //状态转移符号相等且没放入过res的顶点
                    res += v ; //存入该点
            }
        }
    }
    return res;
}

int main()
{
    int u, v; //顶点编号
    char sg; //状态转移符号(空边则用符号'0')
    cout << "请依次输入顶点编号1 顶点编号2 状态转移符号：\n结束符号：-1\n";
    while(cin >> u && u != -1)
    {
        m ++;
        cin >> v >> sg;
        g[u].push_back({v, sg});
        if(sg != '0')
            sgSet.insert(sg);
    }
    int pos = 0; //当前状态集编号(A = 0)
    dfs(0);
    int t = checkState(); //无用的t, 仅仅标记第一个状态集A
    while(pos < cnt)
    {
        set<char>::iterator ite; //迭代器
        int index = 0; //状态符号序号
        for(ite = sgSet.begin(); ite != sgSet.end(); ite++)
        {
            char sg = *ite;
            string s = Move(pos, sg); //Move(T, a)得到的集合s
            for(int i = 0; i < s.size(); i++)
            {
                int u = (int)(s[i] - '0'); //得到s中每一个顶点
                dfs(u);
            }
            int tPos = checkState(); //临时当前状态集编号
            if(tPos == -1) tPos = cnt - 1; //产生新状态
            else //状态集合为空或者重复
            {
                for(int i = 0; i <= N; i++) //clear: 回溯，st[cnt]状态清空
                    st[cnt][i] = 0;
            }
            ans[pos][index++] = tPos;
        }
        pos ++; //一个状态集结束
    }
    printf("\nDFA转换表：\nSet ");
    set<char>::iterator ite;
    for(ite = sgSet.begin(); ite != sgSet.end(); ite ++)
        cout << *ite << "  ";
    cout << "\n";
    for(int i = 0; i < cnt; i++)
    {
        cout << (char)(i + 'A') << "   ";
        set<char>::iterator ite;
        int index = 0;
        for(ite = sgSet.begin(); ite != sgSet.end(); ite ++)
        {
            if(ans[i][index] != INF) cout << (char)(ans[i][index] + 'A') << "  ";
            else cout << "#  "; //代表不存在该符号的状态的转移
            index ++;
        }
        cout << "\n";
    }
    return 0;
}

/*
0 1 0
1 1 a
1 1 b
1 2 0
-1
*/

/*
0 1 0
1 1 a
1 1 b
1 2 0
2 3 a
3 4 b
4 5 b
-1
*/

/*
0 1 0
0 7 0
1 4 0
1 2 0
4 5 b
2 3 a
5 6 0
3 6 0
6 1 0
6 7 0
7 8 a
8 9 b
9 10 b
-1
*/

/*
0 1 0
1 1 a
1 1 b
1 2 0
2 3 a
3 4 b
4 5 b
5 6 0
6 6 a
6 6 b
6 7 0
-1
*/

/*
0 1 0
0 7 0
1 2 0
1 4 0
2 3 a
4 5 b
3 6 0
5 6 0
6 1 0
6 7 0
7 8 a
8 9 b
9 10 b
10 11 0
10 17 0
11 12 0
11 14 0
12 13 a
14 15 b
13 16 0
15 16 0
16 11 0
16 17 0
-1

*/

/*
0 1 0
0 8 0
1 6 0
6 7 c
7 5 0
1 2 0
2 3 a
3 4 b
4 5 0
5 1 0
5 8 0
-1
*/

