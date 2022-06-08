#### BUPT 2022 Spring Formal Languages and Automata Course Lab2

The simplification of context-free grammars is not a simple problem, and there are many corner cases to consider, such as various circular derivation relationships. I write about 500 lines of this program, considering the vast majority of cases, and it works correctly under the [test cases I constructed myself](https://github.com/livrth/CFG-Simplification/blob/master/doc/test_case.txt).

At first I thought about using [Floyd–Warshall algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm) to implement transitive closures, but found that it was not feasible. If you think more about it, the whole process is completely recursive, in fact, the only algorithm that needs to be used is to hash the string represented by the grammar as a vertex on the graph, and then use a depth-first search. Yes, only depth-first search is needed for this lab, no other complex algorithms are needed.

Compile & Run:
```bash
g++ main.cpp -std=c++14 -fexec-charset=GBK -o test

./test
```

TODO:
- [x] Review the CFG Simplification
- [x] Think how to use graph theory to solve it
- [x] Try to remove useless symbol
- [x] DFS epsilon function can't return
- [x] Remove unit production



__Reference__

- [Tutorial in English 1](https://www.javatpoint.com/automata-simplification-of-cfg)

- [Tutorial in English 2](https://www.tutorialspoint.com/automata_theory/cfg_simplification.htm)

- [LLVM  Simplify and canonicalize the CFG](https://llvm.org/doxygen/SimplifyCFG_8h_source.html)

- [Simplification of context-free grammar through Petri net](https://www.academia.edu/5233442/Simplification_of_context_free_grammar_through_Petri_net)
