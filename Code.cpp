#include<bits/stdc++.h>
#define debug(x) cout << "***" << x << endl
using namespace std;
const int N = 1000;
const int INF = 0x3f3f3f3f;

int m = 0; //����
int cnt = 0; //״̬���ϸ���
int st[N + 5][N + 5]; //�ö����Ʊ�ʾÿ��״̬����״̬
int ans[N][N]; //DFAת����
map<string, int>vis; //�ж�״̬�Ƿ����
map<int, string>mp; //�ù�ϣ��洢ÿ��״̬����״̬
vector<pair<int, char>> g[N + 5];
set<char> sgSet; //״̬ת���ַ���

void dfs(int u) //����closure;
{
    if(st[cnt][u]) return; //��֦
    st[cnt][u] = 1; //����u����
    for(int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i].first;
        char sg = g[u][i].second;
        if('0' == sg) dfs(v);
    }
}

int checkState() //ȷ�ϵ�cnt��״̬���Ƿ�֮ǰ����
{
    string s; //���������б�ʾ��״̬��
    for(int i = 0; i <= N; i++)
        s += (char)(st[cnt][i] + '0');
    if(s.find('1') == s.npos) return INF; //��״̬��Ϊ��(�Ҳ���1)
    if(vis[s]) return vis[s]; //��ǰ״̬�Ѿ�����
    mp[cnt] = s; //��ŵ�cnt��״̬����״̬����
    vis[s] = cnt; //���״̬����s�ǵ�cnt��״̬��
    cnt ++; //״̬����������
    return -1;
}

string Move(int pos, char sg) //Move(T, a)
{
    string s = mp[pos], res;
    for(int i = 0; i < s.size(); i++)
    {
        if('1' == s[i]) //��״̬����
        {
            int u = i; //״̬����T�еĵ�
            for(int i = 0; i < g[u].size(); i++)
            {
                char v = (char)(g[u][i].first + '0');
                if(sg == g[u][i].second && res.find(v) == res.npos) //״̬ת�Ʒ��������û�����res�Ķ���
                    res += v ; //����õ�
            }
        }
    }
    return res;
}

int main()
{
    int u, v; //������
    char sg; //״̬ת�Ʒ���(�ձ����÷���'0')
    cout << "���������붥����1 ������2 ״̬ת�Ʒ��ţ�\n�������ţ�-1\n";
    while(cin >> u && u != -1)
    {
        m ++;
        cin >> v >> sg;
        g[u].push_back({v, sg});
        if(sg != '0')
            sgSet.insert(sg);
    }
    int pos = 0; //��ǰ״̬�����(A = 0)
    dfs(0);
    int t = checkState(); //���õ�t, ������ǵ�һ��״̬��A
    while(pos < cnt)
    {
        set<char>::iterator ite; //������
        int index = 0; //״̬�������
        for(ite = sgSet.begin(); ite != sgSet.end(); ite++)
        {
            char sg = *ite;
            string s = Move(pos, sg); //Move(T, a)�õ��ļ���s
            for(int i = 0; i < s.size(); i++)
            {
                int u = (int)(s[i] - '0'); //�õ�s��ÿһ������
                dfs(u);
            }
            int tPos = checkState(); //��ʱ��ǰ״̬�����
            if(tPos == -1) tPos = cnt - 1; //������״̬
            else //״̬����Ϊ�ջ����ظ�
            {
                for(int i = 0; i <= N; i++) //clear: ���ݣ�st[cnt]״̬���
                    st[cnt][i] = 0;
            }
            ans[pos][index++] = tPos;
        }
        pos ++; //һ��״̬������
    }
    printf("\nDFAת����\nSet ");
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
            else cout << "#  "; //�������ڸ÷��ŵ�״̬��ת��
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

