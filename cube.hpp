#pragma once
#include "extern/EpiCube/src/coordinate.hpp"
#include "extern/EpiCube/src/cubie_cube.hpp"
#include "extern/EpiCube/src/move_table.hpp"
#include <algorithm>
#include <array>
#include <numeric>

static std::array<unsigned, 4> E_edges = {LF, RF, RB, LB};
static std::array<unsigned, 4> M_edges = {UF, UB, DF, DB};
static std::array<unsigned, 4> S_edges = {UR, UL, DR, DL};

// buffer arrays for computations
static std::array<unsigned, NE> combination = {0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0};
static std::array<unsigned, 4> permutation = {0, 1, 2, 3};

unsigned slice_coordinate(const CubieCube &cc,
                          const std::array<unsigned, 4> &slice) {

  unsigned k = 0;
  for (unsigned i = 0; i < NE; ++i) {
    auto it = std::find(slice.begin(), slice.end(), cc.ep[i]);
    if (it != slice.end()) {
      combination[i] = 1;
      permutation[k] = (unsigned)(it - slice.begin());
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

unsigned E_coord(const CubieCube &cc) { return slice_coordinate(cc, E_edges); }
unsigned M_coord(const CubieCube &cc) { return slice_coordinate(cc, M_edges); }
unsigned S_coord(const CubieCube &cc) { return slice_coordinate(cc, S_edges); }
unsigned cp_coord(const CubieCube &cc) { return permutation_index(cc.cp); }
unsigned co_coord(const CubieCube &cc) { return co_index<NC, true>(cc.co); }
unsigned eo_coord(const CubieCube &cc) { return eo_index<NE, true>(cc.eo); }

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
    cp = cp_coord(solved);
    co = co_coord(solved);
    eo = eo_coord(solved);
    esl = E_coord(solved);
    msl = M_coord(solved);
    ssl = S_coord(solved);
  }
  void show() const { print(cp, co, eo, esl, msl, ssl); }
};

CubieCube cc_from_slice_coord(const unsigned &esl,
                              const std::array<unsigned, 4> slice) {
  CubieCube ret;

  unsigned comb_c = esl / factorial(4);
  unsigned perm_c = esl % factorial(4);
  layout_from_index(comb_c, combination, 4);
  permutation_from_index(perm_c, permutation);

  unsigned k = 0;
  for (unsigned i = 0; i < NE; ++i) {
    if (combination[i] == 1) {
      ret.ep[i] = slice[permutation[k]];
      ++k;
    } else {
      ret.ep[i] = NE;
    }
  }

  return ret;
}

CubieCube cc_from_E(const unsigned &esl) {
  return cc_from_slice_coord(esl, E_edges);
}
CubieCube cc_from_M(const unsigned &msl) {
  return cc_from_slice_coord(msl, M_edges);
}
CubieCube cc_from_S(const unsigned &ssl) {
  return cc_from_slice_coord(ssl, S_edges);
}
CubieCube cc_from_cp(const unsigned &cp) {
  CubieCube ret;
  permutation_from_index(cp, ret.cp);
  return ret;
}
CubieCube cc_from_co(const unsigned &co) {
  CubieCube ret;
  co_from_index<NC, true>(co, ret.co);
  unsigned mod3 = std::accumulate(ret.co.begin(), ret.co.end(), 0) % 3;
  ret.co.back() = (3 - mod3) % 3;
  return ret;
}
CubieCube cc_from_eo(const unsigned &eo) {
  CubieCube ret;
  eo_from_index<NE, true>(eo, ret.eo);
  unsigned mod2 = std::accumulate(ret.eo.begin(), ret.eo.end(), 0) % 2;
  ret.eo.back() = (2 - mod2) % 2;
  return ret;
}

constexpr unsigned SLICE_COORD_SIZE = binomial(12, 4) * factorial(4);
constexpr unsigned CP_COORD_SIZE = factorial(8);
constexpr unsigned CO_COORD_SIZE = ipow(3, NC - 1);
constexpr unsigned EO_COORD_SIZE = ipow(2, NE - 1);
MoveTable<CP_COORD_SIZE> cp_mtable;
MoveTable<CO_COORD_SIZE> co_mtable;
MoveTable<EO_COORD_SIZE> eo_mtable;
MoveTable<SLICE_COORD_SIZE> e_mtable;
MoveTable<SLICE_COORD_SIZE> m_mtable;
MoveTable<SLICE_COORD_SIZE> s_mtable;

auto make_apply() {
  if (!cp_mtable.load("cp")) {
    cp_mtable.compute(cp_coord, cc_from_cp);
    cp_mtable.write("cp");
  }
  if (!co_mtable.load("co")) {
    co_mtable.compute(co_coord, cc_from_co);
    co_mtable.write("co");
  }
  if (!eo_mtable.load("eo")) {
    eo_mtable.compute(eo_coord, cc_from_eo);
    eo_mtable.write("eo");
  }
  if (!e_mtable.load("eslice")) {
    e_mtable.compute(E_coord, cc_from_E);
    e_mtable.write("eslice");
  }
  if (!m_mtable.load("mslice")) {
    m_mtable.compute(M_coord, cc_from_M);
    m_mtable.write("mslice");
  }
  if (!s_mtable.load("sslice")) {
    s_mtable.compute(S_coord, cc_from_S);
    s_mtable.write("sslice");
  }

  return [](Cube &cube, const Move &m) {
    cp_mtable.apply(cube.cp, m);
    co_mtable.apply(cube.co, m);
    eo_mtable.apply(cube.eo, m);
    e_mtable.apply(cube.esl, m);
    m_mtable.apply(cube.msl, m);
    s_mtable.apply(cube.ssl, m);
  };
}