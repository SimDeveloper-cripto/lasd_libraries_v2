### Work in Progress

This is a continuation and completion of lasd_libraries: <br />
What is left to do:

- [ ] Implement a Double Linked List
- [ ] Linked List
  - [ ] Add Reverse()
  - [ ] Add MapPreOrder()
  - [ ] Add FoldPreOrder()
- [ ] Graph
  - [ ] Add Move and Copy constructor, Move and Copy assignment, operator=, do not implement operator==
  - [ ] Add FoldPreOrder()
  - [ ] Implement transposed graph
  - [ ] Implement topological order 
  - [ ] Bfs: to make it complete should add dist[] and prev[]
  - [ ] Dfs: theoretically, via stack, we can implement PreOrderVisit() and PostOrderVisit()

What is left to be fixed:

- [ ] Resolve FIXME line 75, test.cpp

### Compile the project in Windows (PowerShell)

```bat
.\compile_clang++.bat
cd bin
.\main
```

```bat
.\compile_g++.bat
cd bin
.\main
```
