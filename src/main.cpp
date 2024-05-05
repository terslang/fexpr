// SPDX-License-Identifier: GPL-3.0-only

#include "eval_visitor.hpp"
#include "parse.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<std::string> args(argv + 1, argv + argc);

  // Parsing
  size_t index = 0;
  auto ast = fexpr::parse(args, index);

  // Evaluation
  fexpr::ast::EvalVisitor visitor;
  ast->accept(visitor);
  std::cout << visitor.result << '\n';

  // TODO --help, --version, return values 0, 1 and 2
  return 0;
}
