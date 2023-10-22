# Overview

This is a continuation and completion of lasd_libraries: <https://github.com/SimDeveloper-cripto/lasd_libraries> <br />
What I have focused my work on the most is the Graph data structure, which is implemented by adjacency lists. <br />
This is my first even try in implementing something like this so any help is well accepted! <br />
Keep in mind this is still a work in progess, there are some things I need to finish. <br />

- Graph
  - [ ] Add the calculation of SCC
  - [ ] To complete Bfs algorithm I should add dist[] and prev[] so that the user can calculate Minimum paths

Coming soon:

- Double Linked List
- Graph: PostOrder Map() and Fold()

## Tutorial: Code your personal test

By default, I provided for you an section dedicated to your personal test. <br />
In mytest/test.hpp there is everything you'll need, including all the libraries and a personal namespace called "usertest". <br />
Your code has to be written inside the namespace at mytest/test.cpp <br />
I don't forbid you from doing otherwise, but if you want to quickly test things you can do it this way. Have fun! <br />

### Compile and Execute the project in Windows (PowerShell)

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