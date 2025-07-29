#include "cube.hpp"

int main(int argc, char *argv[]) {
  CubieCube cc;
  cc.apply("R U D2 F' B D L2 F'");

  unsigned c = eo_coord(cc);
  CubieCube check = cc_from_eo(c);

  cc.show();
  check.show();
  return 0;
}