// SPDX-License-Identifier: GPL-3.0-only

#pragma once
#include "visitor.hpp"
#include <string>

namespace fexpr {
namespace ast {
class EvalVisitor : public Visitor {
public:
  std::string result;
  void visit(TermNode *node) override;
  void visit(OperatorNode *node) override;
};
} // namespace ast
} // namespace fexpr
