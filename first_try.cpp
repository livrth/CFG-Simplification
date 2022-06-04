#include <bits/stdc++.h>
using namespace std;

//无用符号 worst case O(N^2) N为文法行数
//空产生式 worst case O(N*T) T为所有文法产生式数量总和
//单产生式 worst case O(T)

/*
S - > a | bA | B | ccD
A - > abB|epsilon
B -> aA
C -> ddC
D -> ddd
-----
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

struct Node {
    string val;      //字符串值
    int number;      //点编号
    bool reachable;  //能否到达终结符
};

void solve() {
    int n;
    cout << "\n请输入产生式的数量: ";
    cin >> n;
    cout << "\n请输入所有产生式, 每个一行, 空字符使用 epsilon 替代: \n\n";
    getchar();

    set<char> N;  //起始符集合
    set<char> T;  //结束符集合
    map<char, vector<string> > all_production;
    vector<char> all_keys;
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        char key = s[0];
        all_keys.push_back(key);
        string temp = "";
        for (int i = 1; s[i]; i++) {
            char c = s[i];
            if (c == '-' || c == '>' || isspace(c)) continue;
            if (c == '|') {
                all_production[key].push_back(temp);
                temp = "";
                continue;
            }
            temp += c;
        }
        if (temp.size() != 0) all_production[key].push_back(temp);
    }
    auto out_dbg = [&]() {
        puts("-------------------------------------------");
        for (auto production : all_production) {
            cout << production.first << " -> ";
            auto all_gen = production.second;
            for (auto t : all_gen) cout << t << ' ';
            cout << endl;
        }
    };

    //先消去无用符号 注意 A->aA 这种递归式子也要消去
    for (auto temp_key : all_keys) {  //无法到达的符号消去
        bool flag = false;
        for (auto pro : all_production) {
            if (pro.first != temp_key) {  //除了当前产生式搜索其余产生式右端是否出现
                auto right_ = pro.second;
                string right_end = "";
                for (auto t : right_) right_end += t;
                if (right_end.find(temp_key) != std::string::npos) {
                    flag = true;
                    break;
                }
            }
        }
        if (!flag && temp_key != 'S') {
            // cout << temp_key << endl;
            auto it = all_production.find(temp_key);
            all_production.erase(it);
        }
    }
    // out_dbg();

    //消去不会产生结束符号的递归式子: A->aaaA, A->Aaaa
    //这样好像有点麻烦，考虑在图上直接dfs所有可达的点，可达就是路径能到全是终结符的字符串，或者 epsilon
    //这种dfs可以通用处理所有是否可达情况,产生式右边如果有一项可达那就是可达，否则不可达
    //但是图上点的权值是一个字符串...
    //考虑如何封装为 Node 然后 dfs 求出可达性
    

    // system("pause");
}

int main_() {
    solve();
    return 0;
}
