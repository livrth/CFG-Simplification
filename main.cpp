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
int h[N], e[N], idx, ne[N];
bool vis[N];
bool reachable[N];
map<string, vector<string> > all_production;
map<string, int> start_symbol;
map<int, string> start_symbol_rev;
int number = 1;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void out_dbg(map<string, vector<string> > &all_production) {
    puts("-------------------------------------------");
    for (auto production : all_production) {
        cout << production.first << " -> ";
        auto all_gen = production.second;
        for (auto t : all_gen) cout << t << ' ';
        cout << endl;
    }
}

bool dfs(int u) {  //判断点 u 开始能否到达终结符
    if (reachable[u]) return true;
    //u右边有纯终结符组成的字符串返回 true
    auto vec = all_production[start_symbol_rev[u]];
    // puts("------------------------------");
    // cout << start_symbol_rev[u] << endl;
    // puts("------------------------------");
    for (auto t : vec) {
        bool flag = true;
        for (auto c : t) {
            if (c >= 'A' && c <= 'Z') {
                flag = false;
                break;
            }
        }
        if (flag) {
            reachable[u] = true;
            break;
        }
    }

    // u能到的起始符也是可达的返回 true
    // A -> B | C
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        // cout << start_symbol_rev[j] << ' ';
        // if (vis[j]) continue;
        // vis[j] = true;
        reachable[u]  |= dfs(j);
    }
    if (reachable[u]) return true;

    return false; //有环的情况 A->C, C->A => A->A 也是不可达的
}

void solve() {
    memset(h, -1, sizeof h);  //邻接表初始化
    cout << "\n请输入起始符号数量: ";
    int cnt;
    cin >> cnt;
    cout << "\n请输入所有起始符: ";
    for (int i = 0; i < cnt; i++) {
        string key;
        cin >> key;
        start_symbol.insert({key, number});
        start_symbol_rev.insert({number, key});
        number++;
    }
    int n;
    cout << "\n请输入产生式的数量: ";
    cin >> n;
    cout << "\n请输入所有产生式, 确保文法最初从起始符 S 开始, 每个一行, 空字符使用 epsilon 替代: \n\n";
    getchar();

    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        string key = s.substr(0, 1);
        // if (start_symbol.find(key) == start_symbol.end()) { //两个互相映射

        string temp = "";
        for (int i = 1; s[i]; i++) {
            char c = s[i];
            if (c == '-' || c == '>' || isspace(c)) continue;
            if (c == '|') {
                all_production[key].push_back(temp);
                for (auto s : temp) {
                    if (s >= 'A' && s <= 'Z' && string(1, s) != key) {
                        add(start_symbol[key], start_symbol[string(1, s)]);
                    }
                }
                temp = "";
                continue;
            }
            temp += c;
        }
        if (temp.size() != 0) {
            all_production[key].push_back(temp);
            for (auto s : temp) {
                if (s >= 'A' && s <= 'Z' && string(1, s) != key) {
                    add(start_symbol[key], start_symbol[string(1, s)]);
                }
            }
        }
    }
    // out_dbg(all_production);
    // for (auto t : start_symbol) cout << t.first << ' ' << t.second << endl;

    //消无用式子
    /*
    for (auto production : all_production) {
        auto start = production.first;
        auto to_state_vec = production.second;
        for (auto to_state : to_state_vec) {
            for (auto c : to_state) {
                if (c >= 'A' && c <= 'Z')
                    reachable[start_symbol[start]] |= dfs(start_symbol[string(1, c)]);
            }
        }
    }
    */
    // cout << start_symbol.size() << endl;
    // cout << start_symbol_rev.size() << endl;

    if (!dfs(start_symbol["S"])) {
        cout << "The final production has nothing!\n\n"; //化简后全为空，没有可达式子
    }
    else {
        for (int i = 1; i < number; i++)
            cout << start_symbol_rev[i] << ' ' << reachable[i] << endl;
        //删去 all_production 中的所有含有不可达起始符的式子

    }

}

int main() {
    solve();
    return 0;
}