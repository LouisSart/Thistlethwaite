#include "cube.hpp"
#include "extern/EpiCube/src/search.hpp"
#include "solver.hpp"

int main(int argc, char *argv[]) {
  load_mtables();
  phase_one::load_ptable();
  phase_two::load_ptable();
  phase_three::generate_representants();
  phase_three::load_ptable();
  phase_four::generate_representants();
  phase_four::load_ptable();

  Cube cube(
      "R' U' F L' R' U2 F2 R' U2 F2 L' U L B' F' R' D F' U2 F L' D2 R' U' F");

  auto root = make_root(cube);
  auto solutions = thistlethwaite(root);
  solutions.show();
  return 0;
}