#### BUPT 2022 Spring Formal Languages and Automata Course Lab2

Team Member:
- [@livrth](https://github.com/livrth)
- [@likely-dog](https://github.com/likely-dog)
- [@R-oink](https://github.com/R-oink)
- [@tempure](https://github.com/tempure)

6/3 TODO:
- [x] Review the CFG Simplification
- [ ] Try to remove useless symbol

--- 

__Some ideas and problems encountered__

Example Input:
```
9
S->a|bA|B|ccD|Pc
A->abB|epsilon|P
P->ppP|A
B->aA
C->ddC
D->ddd
E->eE|F
F->fF|G
G->gG
```

先从 S 开始 DFS, 考虑 S 右边的所有项中的大写字母, 比如 ccD 只考虑 D
- DFS 右边这些大写字母, 去掉所有DFS完这些大写字母都不可达的大写字符集 E F G
- 只需要判断是大写字符是否可达, 某个大写字符不可达, 就要删除所有含有这个大写字符的产生式
- 枚举每个产生式然后判断是否在其他产生式右边出现过思路是错的, E F G 这三项就可以证明

考虑图中有环的特殊情况, 上述样例中 A P 的关系:
- 假设先搜索到 A, 然后标记 A 为搜索过,然后 A 出发搜索邻接点 P, 标记 P 为搜索过, 从 P 出发遇到 A 发现已经搜过就不再搜 A, 然后考虑 P->ppP 这个递归式，这个式子是不可达的，要特殊判断递归式的格式，包括左递归和右递归。搜索完 P 的所有项了递归返回结果是 P 为不可达状态。如果不标记A是否搜过，再去搜 A 就会陷入死循环。

- 直接将 A 代入 P 产生式得到 P->ppP|abB|epsilon|P, 那么此时P->epsilon 是可达的, 但是如何处理 P->P, 以及如何用代码实现“代入” ?

到底 A 和 P 的推导关系该如何处理才能得到正确结果, 同时保证 DFS 不会无限递归陷入死循环?

--- 


__6.6 Update__
```
A -> B | C | D
B -> bB | E | F
E -> eE | c
F -> eF | G
G -> gG | b
```
每一项大写字母都DFS 任意一项可达就是可达的

有环情况:
```
A -> B | C | D
C -> A | E
B -> bB
D -> dD 
E -> eE
```
A 是不可达的 无用式子
防止环出现就搜过的不再搜了, 而且遇到环的话返回是 false
举例: A -> C, C -> A | E

此时 C -> A 发现 A 已被标记搜过，那么这一项 DFS(A)  = false

然后去 DFS(E) 最后返回的结果就是 DFA(A) || DFS(E)

A -> A | B | C 这种应该化简为 A -> B | C, A->A 是要去掉的

如果只有 A -> A, 那么A就无法到达结束符，A 也是无用式子

---

__Reference__

- [Tutorial in English 1](https://www.javatpoint.com/automata-simplification-of-cfg)

- [Tutorial in English 2](https://www.tutorialspoint.com/automata_theory/cfg_simplification.htm)

- [Simplification of context-free grammar through Petri net](https://www.academia.edu/5233442/Simplification_of_context_free_grammar_through_Petri_net)
