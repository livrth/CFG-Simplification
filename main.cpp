#include <bits/stdc++.h>
using namespace std;

//无用符号 worst case O(N^2) N为文法行数
//空产生式 worst case O(N*T) T为所有文法产生式数量总和
//单产生式 worst case O(T)


/*
S→a|bA|B|ccD
A→abB|ε
B→aA
C→ddC
D→ddd
-----
S→a|b|a|ccD
A→abB
B→a
D→ddd
*/

int main() {
    cout << "test" << endl;
    system("pause");
    return 0;
}