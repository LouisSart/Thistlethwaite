#pragma once
#include "cube.hpp"
#include "extern/EpiCube/src/pruning_table.hpp"
#include "phase_two.hpp"
#include <deque>
#include <map>
#include <set>

namespace phase_three {
std::array<Move, 10> moves{U, U2, U3, D, D2, D3, R2, L2, F2, B2};

constexpr unsigned N_HTR_CP = factorial(4) * factorial(4) / 6; // = 96
std::vector<CubieCube> htr_corner_states;

void generate_htr_corner_states() {
  std::set<unsigned> htr_cp_indices;
  std::deque queue{CubieCube()};

  while (queue.size() > 0) {
    CubieCube cc = queue.back();
    unsigned index = cp_coord(cc);
    if (!htr_cp_indices.contains(index)) {
      htr_cp_indices.insert(index);
      htr_corner_states.push_back(cc);
      for (const Move m : {U2, D2, R2, L2, F2, B2}) {
        CubieCube child = cc;
        child.apply(m);
        queue.push_front(child);
      }
    }
    queue.pop_back();
  }
  assert(htr_cp_indices.size() == N_HTR_CP);
  assert(htr_corner_states.size() == N_HTR_CP);
}

constexpr unsigned N_CORNER_REP = CP_COORD_SIZE / N_HTR_CP; // 40320/96 = 420
std::array<unsigned, CP_COORD_SIZE> corner_representants;
void generate_corner_representants() {
  corner_representants.fill(CP_COORD_SIZE);
  std::deque queue{CubieCube()};

  unsigned index = 0;
  while (queue.size()) {
    CubieCube cc = queue.back();
    assert(cp_coord(cc) < CP_COORD_SIZE);
    if (corner_representants[cp_coord(cc)] == CP_COORD_SIZE) {
      for (CubieCube htr_cc : htr_corner_states) {
        CubieCube rep = htr_cc;
        rep.apply(cc);
        corner_representants[cp_coord(rep)] = index;
      }
      ++index;
      assert(index <= N_CORNER_REP);
      for (const Move m : moves) {
        CubieCube child = cc;
        child.apply(m);
        queue.push_front(child);
      }
    }
    queue.pop_back();
  }

  for (unsigned k : corner_representants) {
    assert(k < N_CORNER_REP);
  }
}

// constexpr unsigned COMB_SLICE_COORD_SIZE =
//     SLICE_COORD_SIZE / factorial(4);            // 495
constexpr unsigned N_EDGE_REP = binomial(8, 4); // 70
std::map<unsigned, unsigned> edge_representants;
unsigned comb_mslice_index(const Cube &cube) { return cube.msl / factorial(4); }

void generate_edge_representants() {
  std::deque<Cube> queue{Cube()};
  unsigned rep_index = 0;

  while (queue.size()) {
    Cube cube = queue.back();
    if (!edge_representants.contains(comb_mslice_index(cube))) {
      edge_representants[comb_mslice_index(cube)] = rep_index;
      ++rep_index;
      for (const Move m : moves) {
        Cube child = cube;
        apply(m, child);
        queue.push_front(child);
      }
    }
    queue.pop_back();
  }
  assert(edge_representants.size() == N_EDGE_REP);
  assert(edge_representants.size() == rep_index);
}

void generate_representants() {
  generate_htr_corner_states();
  generate_corner_representants();
  generate_edge_representants();
}
} // namespace phase_three