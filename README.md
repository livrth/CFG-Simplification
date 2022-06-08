#### BUPT 2022 Spring Formal Languages and Automata Course Lab2


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
