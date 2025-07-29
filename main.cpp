#include "cube.hpp"
#include "extern/EpiCube/src/search.hpp"
#include "phase_one.hpp"

int main(int argc, char *argv[]) {
  load_mtables();
  phase_one::load_ptable();

  Cube cube(
      "R' U' F D2 L' B' R2 D L' B R L2 B2 D R2 B2 U D B2 U F2 L2 D2 R' U' F");
  auto root = make_root(cube);
  auto solutions =
      IDAstar(root, apply, phase_one::estimate, phase_one::is_solved);
  solutions.show();
  return 0;
}