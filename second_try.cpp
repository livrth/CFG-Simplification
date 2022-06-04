#include <bits/stdc++.h>
using namespace std;

//无用符号 worst case O(N^2) N为文法行数
//空产生式 worst case O(N*T) T为所有文法产生式数量总和
//单产生式 worst case O(T)

/*
S->a|bA|B|ccD
A->abB|epsilon
B->aA
C->ddC
D->ddd
-----
S->a|bA|aA|ccD|b
A->abB
B->aA|a
D->ddd
*/

const int N = 50;

struct Node {
    string val;              //字符串值
    int number;              //点编号
    bool reachable = false;  //能否到达终结符
} node[N];

void out_dbg(map<string, vector<string> > &all_production) {
    puts("-------------------------------------------");
    for (auto production : all_production) {
        cout << production.first << " -> ";
        auto all_gen = production.second;
        for (auto t : all_gen) cout << t << ' ';
        cout << endl;
    }
}

int h[N], e[N], idx, ne[N];
bool vis[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u) {  //有向图不用考虑反向边
    vis[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (vis[j]) continue;
        node[j].reachable = true;
        vis[j] = true;
        dfs(j);
    }
}

void solve() {
    memset(h, -1, sizeof h);  //邻接表初始化
    int n;
    cout << "\n请输入产生式的数量: ";
    cin >> n;
    cout << "\n请输入所有产生式, 每个一行, 空字符使用 epsilon 替代: \n\n";
    getchar();

    map<string, vector<string> > all_production;
    int number = 1;
    map<string, int> state_number;
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        string key = s.substr(0, 1);
        if (state_number.find(key) == state_number.end()) state_number[key] = number++;
        string temp = "";
        for (int i = 1; s[i]; i++) {
            char c = s[i];
            if (c == '-' || c == '>' || isspace(c)) continue;
            if (c == '|') {
                all_production[key].push_back(temp);
                if (state_number.find(temp) == state_number.end()) state_number[temp] = number++;
                add(state_number[temp], state_number[key]);
                temp = "";
                continue;
            }
            temp += c;
        }
        if (temp.size() != 0) {
            all_production[key].push_back(temp);
            if (state_number.find(temp) == state_number.end()) state_number[temp] = number++;
            add(state_number[temp], state_number[key]);
        }
    }
    // out_dbg(all_production);
    /*
    cout << "\n"
         << state_number.size() << "\n\n";
    for (auto str : state_number) {
        cout << str.first << ' ' << str.second << endl;
    }
    cout << "\n";
    */

    for (auto t : state_number) {  //存入 node[]
        node[t.second].val = t.first;
    }

    //初始判断key所代表的状态是否可达 然后 DFS
    //也就是判断是否到达状态有全为终结符的状态
    for (auto key : all_production) {
        auto to_state = key.second;
        for (auto t : to_state) {
            bool flag = true;
            for (auto c : t) {
                if (c >= 'A' && c <= 'Z') {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                node[state_number[t]].reachable = true;
                node[state_number[key.first]].reachable = true;
                // break;
            }
        }
    }

    for (int i = 1; i <= state_number.size(); i++) cout << node[i].val << ' ' << node[i].reachable << endl;

    //消去不会产生结束符号的递归式子: A->aaaA, A->Aaaa
    //这样好像有点麻烦，考虑在图上直接dfs所有可达的点，可达就是路径能到全是终结符的字符串，或者 epsilon
    //这种dfs可以通用处理所有是否可达情况,产生式右边如果有一项可达那就是可达，否则不可达
    //但是图上点的权值是一个字符串...考虑如何封装为 Node 然后 dfs 求出可达性

    //每个点代表的状态都 DFS 一次 O(T^2) 图不一定是联通的，有的点没有入边
    for (int i = 1; i <= state_number.size(); i++) {
        if (node[i].reachable == true) dfs(i);
    }

    puts("----------------");
    puts("可达性DFS结果如下:");
    for (int i = 1; i <= state_number.size(); i++) cout << node[i].val << ' ' << node[i].reachable << endl;

    // system("pause");
}

int main() {
    solve();
    return 0;
}