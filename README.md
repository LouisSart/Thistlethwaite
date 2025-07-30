C++ Implementation of [Thistlethwaite's algorithm](https://www.jaapsch.net/puzzles/thistle.htm) for solving the 3x3x3 Rubik's Cube

I use `g++ -std=c++20 -O3 main.cpp -o thistlewaite` to compile
and then for example:

```./thistlewaite "R' U' F D R' F2 L2 D R2 D' F2 D2 L2 B2 D' L D R U' B' R U2 B' R' U' F"
Thistlethwaite : searching at depth 5
Thistlethwaite : searching at depth 6
Thistlethwaite : searching at depth 7
Thistlethwaite : searching at depth 8
Thistlethwaite : searching at depth 9
Thistlethwaite : searching at depth 10
Thistlethwaite : searching at depth 11
Thistlethwaite : searching at depth 12
Thistlethwaite : searching at depth 13
Thistlethwaite : searching at depth 14
Thistlethwaite : searching at depth 15
Thistlethwaite : searching at depth 16
Thistlethwaite : searching at depth 17
Thistlethwaite : searching at depth 18
Thistlethwaite : searching at depth 19
Thistlethwaite : searching at depth 20
Thistlethwaite : searching at depth 21
Thistlethwaite : searching at depth 22
Thistlethwaite : searching at depth 23
Thistlethwaite : searching at depth 24
Thistlethwaite : searching at depth 25
D2 L2 U' F B D R U' R' B2 D' L F2 D' L2 F2 D' B2 U2 L2 U F2 B2 L2 B2 (25)
D2 L2 U' F B D R U' R' B2 D' L B2 U' R2 F2 U' B2 D2 R2 D F2 B2 R2 F2 (25)```