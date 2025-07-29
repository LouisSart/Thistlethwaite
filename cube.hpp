#pragma once
#include "extern/EpiCube/src/coordinate.hpp"
#include "extern/EpiCube/src/cubie_cube.hpp"
#include <algorithm>
#include <array>

unsigned E_coordinate(const CubieCube &cc) {
  static std::array<unsigned, 4> E_edges = {LF, RF, RB, LB};
  static std::array<unsigned, NE> combination = {0, 0, 0, 0, 0, 0,
                                                 0, 0, 0, 0, 0, 0};
  static std::array<unsigned, 4> permutation = {0, 1, 2, 3};

  unsigned k = 0;
  for (unsigned i = 0; i < NE; ++i) {
    auto it = std::find(E_edges.begin(), E_edges.end(), cc.ep[i]);
    if (it != E_edges.end()) {
      combination[i] = 1;
      permutation[k] = (unsigned)(it - E_edges.begin());
      ++k;
    } else {
      combination[i] = 0;
    }
  }
  assert(k == 4);

  unsigned perm_c = permutation_index(permutation);
  unsigned comb_c = layout_index(combination, 4);

  return comb_c * factorial(4) + perm_c;
}

unsigned M_coordinate(const CubieCube &cc) {
  static std::array<unsigned, 4> M_edges = {UF, UB, DF, DB};
  static std::array<unsigned, NE> combination = {0, 0, 0, 0, 0, 0,
                                                 0, 0, 0, 0, 0, 0};
  static std::array<unsigned, 4> permutation = {0, 1, 2, 3};

  unsigned k = 0;
  for (unsigned i = 0; i < NE; ++i) {
    auto it = std::find(M_edges.begin(), M_edges.end(), cc.ep[i]);
    if (it != M_edges.end()) {
      combination[i] = 1;
      permutation[k] = (unsigned)(it - M_edges.begin());
      ++k;
    } else {
      combination[i] = 0;
    }
  }
  assert(k == 4);

  unsigned perm_c = permutation_index(permutation);
  unsigned comb_c = layout_index(combination, 4);

  return comb_c * factorial(4) + perm_c;
}

unsigned S_coordinate(const CubieCube &cc) {
  static std::array<unsigned, 4> S_edges = {UR, UL, DR, DL};
  static std::array<unsigned, NE> combination = {0, 0, 0, 0, 0, 0,
                                                 0, 0, 0, 0, 0, 0};
  static std::array<unsigned, 4> permutation = {0, 1, 2, 3};

  unsigned k = 0;
  for (unsigned i = 0; i < NE; ++i) {
    auto it = std::find(S_edges.begin(), S_edges.end(), cc.ep[i]);
    if (it != S_edges.end()) {
      combination[i] = 1;
      permutation[k] = (unsigned)(it - S_edges.begin());
      ++k;
    } else {
      combination[i] = 0;
    }
  }
  assert(k == 4);

  unsigned perm_c = permutation_index(permutation);
  unsigned comb_c = layout_index(combination, 4);

  return comb_c * factorial(4) + perm_c;
}

struct Cube {
  // nissy-like cube state representation
  // cp : Corner permutation coordinate
  // ep : Edge permutation coordinate
  // eo : Edge orientation coordinate
  // esl: E-slice position coordinate
  // msl: M-slice position coordinate
  // ssl: S-slice position coordinate
  unsigned cp, co, eo, esl, msl, ssl;

  Cube() {
    CubieCube solved;
    cp = permutation_index(solved.cp);
    co = co_index<NC, true>(solved.co);
    eo = eo_index<NE, true>(solved.eo);
    esl = E_coordinate(solved);
    msl = M_coordinate(solved);
    ssl = S_coordinate(solved);
  }
  void show() const { print(cp, co, eo, esl, msl, ssl); }
};