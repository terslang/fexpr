// SPDX-License-Identifier: GPL-3.0-only

#include "parse.hpp"
#include "visitor.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<std::string> args(argv + 1, argv + argc);

  size_t index = 0;
  auto ast = fexpr::parse(args, index);

  return 0;
}
