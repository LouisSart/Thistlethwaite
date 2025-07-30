#pragma once
#include "cube.hpp"
#include "extern/EpiCube/src/pruning_table.hpp"
#include "phase_three.hpp"
#include <deque>
#include <map>

namespace phase_four {
std::array<Move, 6> moves{U2, D2, R2, L2, F2, B2};

std::map<unsigned, unsigned> corner_representants;
void generate_corner_representants() {
  unsigned k = 0;
  for (const auto &[cp, _] : phase_three::htr_corner_states) {
    corner_representants[cp] = k;
    ++k;
  }
  assert(k == phase_three::N_HTR_CP);
  assert(corner_representants.size() == phase_three::N_HTR_CP);
}

constexpr unsigned N_SLICE_PERM = factorial(4);
constexpr unsigned N_HTR_EP = ipow(N_SLICE_PERM, 3) / 2;
unsigned raw_edge_index(const Cube &cube) {
  // edge coordinate for phase 4 ignoring parity constraints.
  // Only half of the raw values can be reached with only half turns
  unsigned eslp = cube.esl % N_SLICE_PERM;
  unsigned mslp = cube.msl % N_SLICE_PERM;
  unsigned sslp = cube.ssl % N_SLICE_PERM;
  return (eslp * N_SLICE_PERM + mslp) * N_SLICE_PERM + sslp;
}

std::map<unsigned, unsigned> edge_representants;
void generate_edge_representants() {
  std::deque<Cube> queue{Cube()};
  unsigned rep_index = 0;
  while (queue.size()) {
    Cube cube = queue.back();
    if (!edge_representants.contains(raw_edge_index(cube))) {
      edge_representants[raw_edge_index(cube)] = rep_index;
      for (const Move m : moves) {
        Cube child = cube;
        apply(m, child);
        queue.push_front(child);
      }
      ++rep_index;
    }
    queue.pop_back();
  }
  assert(edge_representants.size() == N_HTR_EP);
}

void generate_representants() {
  generate_corner_representants();
  generate_edge_representants();
}
unsigned edge_index(const Cube &cube) {
  unsigned raw_index = raw_edge_index(cube);
  assert(edge_representants.contains(raw_index));
  return edge_representants[raw_index];
}
unsigned corner_index(const Cube &cube) {
  assert(corner_representants.contains(cube.cp));
  return corner_representants[cube.cp];
}
unsigned index(const Cube &cube) {
  return corner_index(cube) * N_HTR_EP + edge_index(cube);
}
constexpr unsigned PTABLE_SIZE = N_HTR_EP * phase_three::N_HTR_CP;
PruningTable<PTABLE_SIZE> ptable;
void load_ptable() {
  if (!ptable.load("phase_four")) {
    ptable.generate<true>(Cube(), apply, index, moves);
    ptable.write("phase_four");
  }
}

} // namespace phase_four