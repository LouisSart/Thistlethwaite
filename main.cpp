#include "cube.hpp"
#include "extern/EpiCube/src/search.hpp"
#include "phase_one.hpp"
#include "phase_three.hpp"
#include "phase_two.hpp"

int main(int argc, char *argv[]) {
  load_mtables();
  phase_one::load_ptable();
  phase_two::load_ptable();
  phase_three::generate_representants();
  phase_three::load_ptable();

  Cube cube;
  apply_alg("D F2 D L2 D' F2 U2 F2 U L2 B2", cube);

  auto root = make_root(cube);
  auto solutions = IDAstar(root, apply, phase_three::estimate,
                           phase_three::is_solved, phase_three::directions);
  solutions.show();
  return 0;
}