#pragma once
#include "cube.hpp"
#include "extern/EpiCube/src/pruning_table.hpp"

namespace phase_one {
bool is_solved(const Cube &cube) { return cube.eo == 0; }
unsigned index(const Cube &cube) { return cube.eo; }
Cube from_index(const unsigned &ceo) { auto ret = Cube(); ret.eo = ceo; return ret;}

constexpr unsigned PTABLE_SIZE = ipow(2, NE - 1);
PruningTable<PTABLE_SIZE> ptable;

void load_ptable() {
  if (!ptable.load("phase_one")) {
    ptable.generate(Cube(), apply, index, from_index);
    ptable.write("phase_one");
  }
}
unsigned estimate(const Cube &cube) { return ptable[cube.eo]; };
}; // namespace phase_one