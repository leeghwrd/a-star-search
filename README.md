# A * Search

Simple project to find quickest route to end goal, using an implementation of the
A * Search algorithm. Written in C++

Compile:

```bash
% g++ -std=c++17 main.cpp -o main
% ./main
```

Expected output:

```bash
🚦   ⛰️   -1   -1   -1   -1   
🚗   ⛰️   -1   -1   -1   -1   
🚗   ⛰️   -1   -1   -1   -1   
🚗   ⛰️   -1   🚗   🚗   🚗   
🚗   🚗   🚗   🚗   ⛰️   🏁
```


Board files are text files located in boards/ directory. Currently only contains
one board.

```bash
% cat boards/1.board
0,1,0,0,0,0,
0,1,0,0,0,0,
0,1,0,0,0,0,
0,1,0,0,0,0,
0,0,0,0,1,0,
```