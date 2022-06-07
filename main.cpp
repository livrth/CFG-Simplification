#include <bits/stdc++.h>
using namespace std;

//无用符号 worst case O(N^2) N为文法行数
//空产生式 worst case O(2^C) 需要指数枚举
//单产生式 worst case O(T)

const int N = 50;
int h[N], e[N], idx, ne[N];
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

    if (all_production.find(start_symbol_rev[u]) == all_production.end()) return false;

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
        reachable[u]  |= dfs(j);
    }
    if (reachable[u]) return true;

    return false; //有环的情况 A->C, C->A => A->A 也是不可达的
}

//消无用符号
void remove_useless() {
    if (!dfs(start_symbol["S"])) {
        cout << "\nThe final production has nothing!\n\n"; //化简后全为空，没有可达式子
        system("pause");
        return;
    }
    // for (int i = 1; i < number; i++)
    // cout << start_symbol_rev[i] << ' ' << reachable[i] << endl;

    set<string> all_unreachable;
    for (int i = 1; i < number; i++) {
        if (!reachable[i]) all_unreachable.insert(start_symbol_rev[i]);
    }

    //删掉所有不可达开始的左边式子，然后再删右边含有不可达符号的项
    for (auto un : all_unreachable) {
        auto t = all_production.find(un);
        all_production.erase(t);
    }
    for (auto &pro : all_production) {
        set<string> delete_;
        vector<string> new_right;
        auto &to_state = pro.second;
        for (auto it = to_state.begin(); it != to_state.end(); ++it) {
            string now = *it;
            for (auto c : now) {
                if (all_unreachable.count(string(1, c))) {
                    delete_.insert(now);
                    break;
                }
            }
        }
        //copy and change
        for (auto t : to_state) {
            if (!delete_.count(t)) new_right.push_back(t);
        }
        pro.second = new_right;
    }
}

//消空产生式
void remove_epsilon() {
    //消空产生式 指数枚举含有 epsilon 的项中被消去的所有情况
    //如果 X -> epsilon 则要注意删除后X推导为空，同时删除此产生式
    set<string> all_ep; //所有能推导出 epsilon 的产生式

    for (auto pro : all_production) {
        auto to_state = pro.second;
        auto key = pro.first;
        for (auto t : to_state) {
            if (t == "epsilon") {
                all_ep.insert(key);
                break;
            }
        }
    }

    //先删除能直接推导出 epsilon 的项 A -> x | epsislon, 删除 epsilon
    for (auto &pro : all_production) {
        vector<string> new_right;
        auto &to_state = pro.second;
        for (auto it = to_state.begin(); it != to_state.end(); ++it) {
            string now = *it;
            if (now != "epsilon") {
                new_right.push_back(now);
            }
        }
        if (new_right.size() != 0) {
            pro.second = new_right;
        }
        else { // C -> _ 没有生成式了，只有一个 epsilon 消完了，直接删除这个生成式
            auto it = all_production.find(pro.first);
            all_production.erase(it);
        }
    }

    //指数枚举替换 epsilon
    /*
    S -> XYX | A | B
    A -> bBX | aCbC
    B -> bbb | BX
    X -> aX | epsilon
    Y -> bY | epsilon
    C -> epsilon
    */
    for (auto &pro : all_production) {
        auto &to_state = pro.second;
        vector<string> new_right;
        vector<string> to_temp;
        if (to_state.empty()) continue; // C -> _
        for (auto str : to_state) { //str : XYX
            vector<int> pos; //所有空项的下标
            for (int i = 0; str[i]; i++) {
                if (all_ep.count(string(1, str[i]))) {
                    pos.push_back(i);
                }
            }
            if (!pos.empty()) {
                for (int i = 1; i < (1 << pos.size()); i++) {
                    string temp = str;
                    for (int k = 0; k < pos.size(); k++) {
                        if ((i >> k) & 1) {
                            temp[pos[k]] = '#';
                        }
                    }
                    to_temp.push_back(temp);
                }
            }
        }
        for (auto t : to_temp) to_state.push_back(t);
    }

    //最后处理去掉字符串的 '#'
    for (auto & pro : all_production) {
        auto & to_state = pro.second;
        for (auto &str : to_state) {
            string temp = "";
            for (auto c : str) {
                if (c != '#') temp += string(1, c);
            }
            str = temp;
        }
    }
    //去重, XYX 去空会产生两个 X
    for (auto & pro : all_production) {
        auto & to_state = pro.second;
        set<string> right;
        for (auto str : to_state) {
            if (str != "") right.insert(str);
        }
        vector<string> new_right;
        for (auto t : right) new_right.push_back(t);
        pro.second = new_right;
    }
}

void rebuild_graph() {
    memset(h, -1, sizeof h);
    memset(ne, 0, sizeof ne);
    memset(e, 0, sizeof e);
    idx = 0;
    memset(reachable, 0, sizeof reachable);
    number = (int)all_production.size();
    int cnt = 1;
    start_symbol.clear();
    start_symbol_rev.clear();

    for (auto pro : all_production) {
        auto key = pro.first;
        start_symbol[key] = cnt;
        start_symbol_rev[cnt] = key;
        cnt++;
    }

    for (auto pro : all_production) {
        auto to_state = pro.second;
        auto key = pro.first;
        for (auto str : to_state) {
            for (auto c : str) {
                if (c >= 'A' && c <= 'Z' && string(1, c) != key) //不要加自环的边
                    add(start_symbol[key], start_symbol[string(1, c)]);
            }
        }
    }
}


//消除单产生式
void remove_unit() {

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

        string temp = "";
        for (int i = 1; s[i]; i++) {
            char c = s[i];
            if (c == '-' || c == '>' || isspace(c)) continue;
            if (c == '|') {
                all_production[key].push_back(temp);
                for (auto s : temp) {
                    if (s >= 'A' && s <= 'Z' && string(1, s) != key) { //不要加自环
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

    //消无用
    remove_useless();
    out_dbg(all_production);

    //消空 
    remove_epsilon();

    rebuild_graph(); //重新建图 消去 epsilon 之后
    remove_useless(); //再消一次无用符号
    /*
    再消去一次无用符号:
    S -> XYX | A | B   //输入样例
    A -> bBX | aCbC
    B -> bbb | BX | D
    D -> C
    X -> aX | epsilon
    Y -> bY | epsilon
    C -> epsilon
    ------------------------------------------- //消去无用以及空符号 C->epsilon 已经被删了, D->C 落单
    A -> aCb aCbC ab abC bB bBX
    B -> B BX D bbb
    D -> C
    S -> A B X XX XY XYX Y YX
    X -> a aX
    Y -> b bY
    ------------------------------------------- //D落单之后为无用符号, 所以要再删一次
    A -> aCb aCbC ab abC bB bBX
    B -> B BX bbb
    S -> A B X XX XY XYX Y YX
    X -> a aX
    Y -> b bY
    */

    out_dbg(all_production);
    //消去单产生式:


}

int main() {
    solve();
    // system("pause");
    return 0;
}