# Overview

This is a continuation and completion of lasd_libraries: <https://github.com/SimDeveloper-cripto/lasd_libraries> <br />
What I have focused my work on the most is the Oriented Graph data structure, which is implemented by adjacency lists. <br />
I used this library for the examination of algorithms and data structures. <br />
This is my first ever try in implementing something like this so any help is well accepted! <br />

Things I want to add in the future:

- Oriented Graph: PostOrder Map() and Fold() (both Bfs and Dfs)
- Double Linked List
- Non-Oriented Graph

## Tutorial: Code your personal test

By default, I provided for you a section dedicated to your personal test. <br />
In __mytest/test.hpp__ there is everything you'll need, including all the libraries and a personal namespace called "__usertest__". <br />
Your code has to be written inside the namespace at __mytest/test.cpp__ <br />
I don't forbid you from doing otherwise, but if you want to quickly test things you can do it this way. Have fun! <br />

### Compile and Execute the project in Windows with G++ or CLANG++ (PowerShell)

```bat
mkdir bin
.\compile_clang++.bat
cd bin
.\main
```

```bat
mkdir bin
.\compile_g++.bat
cd bin
.\main
```

### Compile and Execute the project in Linux

```bash
mkdir bin
chmod +x build.sh
./build.sh
cd bin
.\main
```

## LICENSE

[MIT](https://choosealicense.com/licenses/mit/)