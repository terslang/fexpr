// SPDX-License-Identifier: GPL-3.0-only

#include "ast.hpp"
#include "visitor.hpp"

namespace fexpr {
namespace ast {

void Node::accept(Visitor &visitor) {
  if (auto n = dynamic_cast<TermNode *>(this)) {
    visitor.visit(n);
  } else if (auto o = dynamic_cast<OperatorNode *>(this)) {
    visitor.visit(o);
  }
}

TermNode::TermNode(std::string value) : value(value) {}

OperatorNode::OperatorNode(std::string op, std::unique_ptr<Node> left,
                           std::unique_ptr<Node> right)
    : op(op), left(std::move(left)), right(std::move(right)) {}

} // namespace ast
} // namespace fexpr
