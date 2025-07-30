#pragma once
#include "cube.hpp"
#include "extern/EpiCube/src/node.hpp"
#include "extern/EpiCube/src/pruning_table.hpp"
#include "phase_two.hpp"
#include <deque>
#include <map>

namespace phase_three {
std::array<Move, 10> moves{U, U2, U3, D, D2, D3, R2, L2, F2, B2};

constexpr unsigned N_HTR_CP = factorial(4) * factorial(4) / 6; // = 96
std::map<unsigned, CubieCube> htr_corner_states;

void generate_htr_corner_states() {
  std::deque queue{CubieCube()};

  while (queue.size() > 0) {
    CubieCube cc = queue.back();
    unsigned index = cp_coord(cc);
    if (!htr_corner_states.contains(index)) {
      htr_corner_states[index] = cc;
      for (const Move m : {U2, D2, R2, L2, F2, B2}) {
        CubieCube child = cc;
        child.apply(m);
        queue.push_front(child);
      }
    }
    queue.pop_back();
  }
  assert(htr_corner_states.size() == N_HTR_CP);
}

constexpr unsigned N_CORNER_REP = CP_COORD_SIZE / N_HTR_CP; // 40320 / 96 = 420
std::array<unsigned, CP_COORD_SIZE> corner_representants;
void generate_corner_representants() {
  corner_representants.fill(CP_COORD_SIZE);
  std::deque queue{CubieCube()};

  unsigned index = 0;
  while (queue.size()) {
    CubieCube cc = queue.back();
    assert(cp_coord(cc) < CP_COORD_SIZE);
    if (corner_representants[cp_coord(cc)] == CP_COORD_SIZE) {
      for (const auto &[_, htr_cc] : htr_corner_states) {
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

unsigned corner_index(const Cube &cube) {
  return corner_representants[cube.cp];
}

unsigned edge_index(const Cube &cube) {
  return edge_representants[comb_mslice_index(cube)];
}

unsigned index(const Cube &cube) {
  return corner_index(cube) * N_EDGE_REP + edge_index(cube);
}

constexpr unsigned PTABLE_SIZE = N_CORNER_REP * N_EDGE_REP; // 96 * 70 = 6720
PruningTable<PTABLE_SIZE> ptable;
void load_ptable() {
  if (!ptable.load("phase_three")) {
    ptable.generate<true>(Cube(), apply, index, moves);
    ptable.write("phase_three");
  }
}

unsigned estimate(const Cube &cube) { return ptable[index(cube)]; };

bool is_solved(const Cube &cube) { return index(cube) == 0; }

std::vector<Move> directions(const Node<Cube>::sptr node) {
  if (node->parent == nullptr) {
    return {U, U2, U3, D, D2, D3, R2, L2, F2, B2};
  } else {
    switch (node->last_move) {
    case U ... U3:
      return {D, D2, D3, R2, L2, F2, B2};
    case D ... D3:
      return {R2, L2, F2, B2};
    case R2:
      return {U, U2, U3, D, D2, D3, L2, F2, B2};
    case L2:
      return {U, U2, U3, D, D2, D3, F2, B2};
    case F2:
      return {U, U2, U3, D, D2, D3, R2, L2, B2};
    case B2:
      return {U, U2, U3, D, D2, D3, R2, L2};
    default:
      return {U, U2, U3, D, D2, D3, R2, L2, F2, B2};
    }
  }
}
} // namespace phase_three