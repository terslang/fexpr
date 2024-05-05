// SPDX-License-Identifier: GPL-3.0-only

#pragma once
#include <memory>
#include <string>

namespace fexpr {
namespace ast {

class Visitor;

class Node {
public:
  void accept(Visitor &visitor);
  virtual ~Node() {}
};

class TermNode : public Node {
public:
  TermNode(std::string value);
  std::string value;
};

class OperatorNode : public Node {
public:
  OperatorNode(std::string op, std::unique_ptr<Node> left,
               std::unique_ptr<Node> right);
  std::string op;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;
};

} // namespace ast
} // namespace fexpr
