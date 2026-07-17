C++ Implementation of [Thistlethwaite's algorithm](https://www.jaapsch.net/puzzles/thistle.htm) for solving the 3x3x3 Rubik's Cube

Clone with `git clone --recursive https://github.com/LouisSart/Thistlethwaite.git` as submodule "EpiCube" is required for this to run.

I use `g++ -std=c++20 -O3 main.cpp -o thistlethwaite` to compile
and then run with for example:

```
./thistlethwaite "R' U' F D R' F2 L2 D R2 D' F2 D2 L2 B2 D' L D R U' B' R U2 B' R' U' F"
D2 L2 U' F B D R U' R' B2 D' L F2 D' L2 F2 D' B2 U2 L2 U F2 B2 L2 B2 (25)
D2 L2 U' F B D R U' R' B2 D' L B2 U' R2 F2 U' B2 D2 R2 D F2 B2 R2 F2 (25)
```


Note that a few tables are written on the disk on the first run. They are computed very quickly and stored directly where you ran the exe

Pruning table not found at:  "pruning_tables/phase_one"
Pruning table not found at:  "pruning_tables/phase_two"
0 1
1 2
2 17
switch to forwards scan
3 134
4 1065
5 8190
6 54694
switch to backwards
7 267576
8 560568
9 187204
10 3114
Pruning table not found at:  "pruning_tables/phase_three"
0 3 0.0102041 %
1 12 0.0408163 %
2 48 0.163265 %
3 172 0.585034 %
4 702 2.38776 %
5 2508 8.53061 %
6 6240 21.2245 %
7 11398 38.7687 %
8 18468 62.8163 %
9 25686 87.3673 %
10 28888 98.2585 %
11 29376 99.9184 %
12 29400 100 %
Pruning table not found at:  "pruning_tables/phase_four"
0 7 0.00105493 %
1 34 0.00512394 %
2 154 0.0232084 %
3 673 0.101424 %
4 2605 0.392584 %
5 9089 1.36975 %
6 29399 4.43055 %
7 84433 12.7244 %
8 198325 29.8884 %
9 376820 56.7883 %
10 556016 83.7939 %
11 645744 97.3163 %
12 661920 99.7541 %
13 663408 99.9783 %
14 663552 100 %


Phase 1 : solve EO, e.g. orient the edges with respect to the  FB axis so that the cube can be solved without any F or B quarter turns\
Phase 2 : Solve DR on white/yellow, e.g. reduce the cube to a state which can be solved without any R, L, F or B quarter turns\
Phase 3 : Solve HTR, e.g. reduce to a state that can be solved with only half turns\
Phase 4 : Solve the cube with only half turns\

It's a very naive implementation of the algorithm, with no particular optimization. Every step is solved optimally until one of the phases reaches the max_depth criterion. Then max_depth is incremented iteratively until solutions are found.