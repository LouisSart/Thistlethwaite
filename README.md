C++ Implementation of [Thistlethwaite's algorithm](https://www.jaapsch.net/puzzles/thistle.htm) for solving the 3x3x3 Rubik's Cube

Clone with `git clone --recursive https://github.com/LouisSart/Thistlethwaite.git` as submodule "EpiCube" is required for this to run.

I use `g++ -std=c++20 -O3 main.cpp -o thistlewaite` to compile
and then run with for example:

```
./thistlethwaite "R' U' F D R' F2 L2 D R2 D' F2 D2 L2 B2 D' L D R U' B' R U2 B' R' U' F"
D2 L2 U' F B D R U' R' B2 D' L F2 D' L2 F2 D' B2 U2 L2 U F2 B2 L2 B2 (25)
D2 L2 U' F B D R U' R' B2 D' L B2 U' R2 F2 U' B2 D2 R2 D F2 B2 R2 F2 (25)
```


Note that a few tables are written on the disk on the first run. They are computed very quickly and stored directly where you ran the exe

Phase 1 : solve EO, e.g. orient the edges with respect to the  FB axis so that the cube can be solved without any F or B quarter turns\
Phase 2 : Solve DR on white/yellow, e.g. reduce the cube to a state which can be solved without any R, L, F or B quarter turns\
Phase 3 : Solve HTR, e.g. reduce to a state that can be solved with only half turns\
Phase 4 : Solve the cube with only half turns\

It's a very naive implementation of the algorithm, with no particular optimization. Every step is solved optimally until one of the phases reaches the max_depth criterion. Then max_depth is incremented iteratively until solutions are found.