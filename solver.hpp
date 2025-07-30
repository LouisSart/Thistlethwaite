#pragma once
#include "extern/EpiCube/src/search.hpp"
#include "phase_four.hpp"
#include "phase_one.hpp"
#include "phase_three.hpp"
#include "phase_two.hpp"

auto solve_phase_four(Node<Cube>::sptr node, unsigned max_depth) {
  return IDAstar<false>(node, apply, phase_four::estimate,
                        phase_four::is_solved, phase_four::directions,
                        max_depth);
}
auto solve_phase_three(Node<Cube>::sptr node, unsigned max_depth) {
  return IDAstar<false>(node, apply, phase_three::estimate,
                        phase_three::is_solved, phase_three::directions,
                        max_depth);
}
auto solve_phase_two(Node<Cube>::sptr node, unsigned max_depth) {
  return IDAstar<false>(node, apply, phase_two::estimate, phase_two::is_solved,
                        phase_two::directions, max_depth);
}
auto solve_phase_one(Node<Cube>::sptr node, unsigned max_depth) {
  return IDAstar<false>(node, apply, phase_one::estimate, phase_one::is_solved,
                        max_depth);
}

auto thistlethwaite(Node<Cube>::sptr root) {
  // Zero optimization but this runs fine ^^
  using TTWSolutions = Solutions<Node<Cube>::sptr>;

  unsigned breadth = 5000, max_depth = phase_one::estimate(root->state);
  TTWSolutions solutions_p1;
  TTWSolutions solutions_p2;
  solutions_p2.reserve(breadth);
  TTWSolutions solutions_p3;
  solutions_p3.reserve(breadth);
  TTWSolutions solutions_p4;
  solutions_p4.reserve(breadth);

  while (solutions_p4.size() == 0) {
    print("Thistlethwaite : searching at depth", max_depth);
    solutions_p1 = solve_phase_one(root, max_depth);
    solutions_p1.sort_by_depth();

    solutions_p2.clear();
    for (auto node : solutions_p1) {
      auto sol = solve_phase_two(node, max_depth);
      solutions_p2.insert(solutions_p2.end(), sol.begin(), sol.end());
      if (solutions_p2.size() > breadth)
        break;
    }
    solutions_p2.sort_by_depth();

    solutions_p3.clear();
    for (auto node : solutions_p2) {
      auto sol = solve_phase_three(node, max_depth);
      solutions_p3.insert(solutions_p3.end(), sol.begin(), sol.end());
      if (solutions_p3.size() > breadth)
        break;
    }
    solutions_p3.sort_by_depth();

    solutions_p4.clear();
    for (auto node : solutions_p3) {
      auto sol = solve_phase_four(node, max_depth);
      solutions_p4.insert(solutions_p4.end(), sol.begin(), sol.end());
      if (solutions_p4.size() > breadth)
        break;
    }
    solutions_p4.sort_by_depth();
    ++max_depth;
  }

  return solutions_p4;
}