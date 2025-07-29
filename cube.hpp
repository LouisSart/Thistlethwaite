#pragma once
#include "extern/EpiCube/src/cubie_cube.hpp"

struct Cube {
  // nissy-like cube state representation
  // cp : Corner permutation coordinate
  // ep : Edge permutation coordinate
  // eo : Edge orientation coordinate
  // esl: E-slice position coordinate
  // msl: M-slice position coordinate
  // ssl: S-slice position coordinate
  unsigned cp, co, eo, esl, msl, ssl;
};

unsigned E_coordinate(const CubieCube &cc) {
  static unsigned E_edges[4] = {LF, RF, RB, LB};
}