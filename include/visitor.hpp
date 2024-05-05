// SPDX-License-Identifier: GPL-3.0-only

#pragma once
#include "ast.hpp"

namespace fexpr {
namespace ast {

class Visitor {
public:
  virtual void visit(TermNode *node) = 0;
  virtual void visit(OperatorNode *node) = 0;
  virtual ~Visitor() {}
};

} // namespace ast
} // namespace fexpr
