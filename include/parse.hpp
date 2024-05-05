// SPDX-License-Identifier: GPL-3.0-only

#pragma once
#include "ast.hpp"
#include <string>
#include <vector>

namespace fexpr {
std::unique_ptr<ast::Node> parse(std::vector<std::string> &tokens,
                                 size_t &index, int precedence = 0);
}
