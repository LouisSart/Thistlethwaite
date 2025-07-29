#include "cube.hpp"
#include "extern/EpiCube/src/search.hpp"
#include "phase_one.hpp"
#include "phase_two.hpp"

int main(int argc, char *argv[]) {
  load_mtables();
  phase_one::load_ptable();
  phase_two::load_ptable();

  Cube cube;
  apply_alg("R' U' F D2 B' L' D R' F' B U' D2 R F2 L' B2 L2 B2 L' F2 L' D2 R' "
            "F2 R' U' F B U D' F U R U B",
            cube);

  auto root = make_root(cube);
  auto solutions =
      IDAstar(root, apply, phase_two::estimate, phase_two::is_solved);
  solutions.show();
  return 0;
}