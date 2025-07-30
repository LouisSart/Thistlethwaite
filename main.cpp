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

  auto scramble = Algorithm(argv[argc - 1]);
  Cube cube(scramble);

  auto root = make_root(cube);
  auto solutions = thistlethwaite(root);
  solutions.show();
  return 0;
}