#include "cube.hpp"
#include "extern/EpiCube/src/search.hpp"
#include "phase_four.hpp"
#include "phase_one.hpp"
#include "phase_three.hpp"
#include "phase_two.hpp"

int main(int argc, char *argv[]) {
  load_mtables();
  phase_one::load_ptable();
  phase_two::load_ptable();
  phase_three::generate_representants();
  phase_three::load_ptable();
  phase_four::generate_representants();
  phase_four::load_ptable();

  Cube cube;
  apply_alg("L2 R2 U2 F2 U2 B2 R2 L2 D2 F2 U2 R2 B2 L2 R2", cube);

  auto root = make_root(cube);
  auto solutions = IDAstar(root, apply, phase_four::estimate,
                           phase_four::is_solved, phase_four::directions);
  solutions.show();
  return 0;
}