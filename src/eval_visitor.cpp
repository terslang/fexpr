// SPDX-License-Identifier: GPL-3.0-only

#include "eval_visitor.hpp"
#include "ast.hpp"
#include <format>
#include <functional>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <unordered_map>

inline bool is_zero_or_empty(std::string s) {
  // TODO: can be bettered
  return s.size() == 0 || std::format("{}", s) == "0";
}

namespace fexpr {
namespace ast {
void EvalVisitor::visit(TermNode *node) { result = node->value; }

void EvalVisitor::visit(OperatorNode *node) {
  EvalVisitor left_visitor, right_visitor;
  node->left->accept(left_visitor);
  node->right->accept(right_visitor);

  long double left_operand, right_operand;
  std::regex right_regex;
  if (node->op == ":") {
    try {
      right_regex = std::regex(right_visitor.result);
    } catch (const std::regex_error &e) {
      std::cout << "Invalid Regex: " << e.what() << '\n';
      return;
    }
  } else {
    try {
      left_operand = std::stold(left_visitor.result);
      right_operand = std::stold(right_visitor.result);
    } catch (const std::invalid_argument &e) {
      std::cerr << "Invalid argument(s) provided\n";
      return;
    }
  }

  const std::unordered_map<std::string, std::function<void()>> m{
      {"|",
       [&]() {
         result =
             (is_zero_or_empty(left_visitor.result) ? left_visitor.result
                                                    : right_visitor.result);
       }},
      {"&",
       [&]() {
         result = (is_zero_or_empty(left_visitor.result) &&
                           is_zero_or_empty(right_visitor.result)
                       ? left_visitor.result
                       : std::to_string(0));
       }},
      // TODO: string comparison
      {"<", [&]() { result = std::to_string(left_operand < right_operand); }},
      {"=", [&]() { result = std::to_string(left_operand == right_operand); }},
      {">", [&]() { result = std::to_string(left_operand > right_operand); }},
      {"<=", [&]() { result = std::to_string(left_operand <= right_operand); }},
      {">=", [&]() { result = std::to_string(left_operand >= right_operand); }},
      {"+",
       [&]() { result = std::format("{}", left_operand + right_operand); }},
      {"-",
       [&]() { result = std::format("{}", left_operand - right_operand); }},
      {"*",
       [&]() { result = std::format("{}", left_operand * right_operand); }},
      {"/",
       [&]() { result = std::format("{}", left_operand / right_operand); }},
      // TODO: capture groups, fix regex logic to match expr's
      {":",
       [&]() {
         std::smatch match;
         std::regex_search(left_visitor.result, match, right_regex);
         result = std::to_string(match.length(0));
       }},
  };

  auto it = m.find(node->op);
  if (it != m.end()) {
    it->second();
  } else {
    std::cerr << "Invalid Operation: " << node->op << '\n';
  }
}

} // namespace ast
} // namespace fexpr
