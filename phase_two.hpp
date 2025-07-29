#pragma once
#include "cube.hpp"
#include "extern/EpiCube/src/pruning_table.hpp"
#include "phase_one.hpp"

namespace phase_two {

unsigned comb_slice_index(const Cube &cube) { return cube.esl / factorial(4); }

bool is_eslice_solved(const Cube &cube) {
  return comb_slice_index(cube) == comb_slice_index(solved);
}

bool is_solved(const Cube &cube) {
  //   assert(phase_one::is_solved(cube));
  return phase_one::is_solved(cube) && cube.co == 0 && is_eslice_solved(cube);
}

constexpr unsigned COMB_SLICE_COORD_SIZE = SLICE_COORD_SIZE / factorial(4);
unsigned index(const Cube &cube) {
  return cube.co * COMB_SLICE_COORD_SIZE + comb_slice_index(cube);
}

constexpr unsigned PTABLE_SIZE = CO_COORD_SIZE * COMB_SLICE_COORD_SIZE;
PruningTable<PTABLE_SIZE> ptable;

void load_ptable() {
  if (!ptable.load("phase_two")) {
    ptable.generate<true>(Cube(), apply, phase_two::index,
                          {U, U2, U3, D, D2, D3, R, R2, R3, L, L2, L3, F2, B2});
    ptable.write("phase_two");
  }
}
unsigned estimate(const Cube &cube) { return ptable[index(cube)]; };
}; // namespace phase_two