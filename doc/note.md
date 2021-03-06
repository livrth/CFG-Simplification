
每一个起始符号可达的起始字符字母都进行 DFS,任意一项可达就是可达的。

考虑有环型关系推导的情况:
```
A -> B | C | D | c
C -> A | E
B -> bB
D -> dD 
E -> eE
```
A 是不可达的无用式子,防止环出现就搜过的不再搜了, 而且遇到环的话返回是 false

举例: A -> C, C -> A | E, 此时 C -> A 发现 A 已被标记搜过，那么这一项 DFS(A) = false

然后去 DFS(E) 最后返回的结果就是 DFS(C) = DFS(A) || DFS(E)

A -> A | B | C 这种应该化简为 A -> B | C, A->A 是要去掉的

如果只有 A -> A, 那么A就无法到达结束符，A 也是无用式子

DFS 搜索可达性, 测试样例1:
```
9
S A P B C D E F G
9
S -> a | bA | B | ccD | Pc
A -> abB | epsilon | P
P -> ppP | A | C | E
B -> aA
C -> ddC | D
D -> ddd
E -> eE | F
F -> fF | G
G -> gG
```
DFS 之后的可达性结果:
```
S 1
A 1
P 1
B 1
C 1
D 1
E 0
F 0
G 0
```
测试样例 2:
```
6
S A B C D E
6
S -> A | B | C
A -> Bd | Cf | D | c
C -> A | E
B -> bB
D -> dD 
E -> eE
```
DFS 之后的可达性结果:
```
S 1
A 1
B 0
C 1
D 0
E 0
```