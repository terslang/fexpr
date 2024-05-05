#include "parse.hpp"
#include "ast.hpp"
#include <unordered_map>

namespace fexpr {

int get_precedence(std::string op) {
  static const std::unordered_map<std::string, int> m{
      {"|", 1},  {"&", 2},  {"<", 3}, {"=", 3}, {">", 3}, {">=", 3}, {"<", 3},
      {"<=", 3}, {"!=", 3}, {"+", 4}, {"-", 4}, {"*", 5}, {"/", 5},  {":", 6},
  };
  auto it = m.find(op);
  return (it != m.end() ? it->second : 0);
}

std::unique_ptr<ast::Node> parse(std::vector<std::string> &tokens,
                                 size_t &index, int precedence) {
  auto left =
      (tokens[index] == "(" ? parse(tokens, ++index)
                            : std::make_unique<ast::TermNode>(tokens[index++]));

  while (index < tokens.size() && tokens[index] != ")" &&
         get_precedence(tokens[index]) >= precedence) {
    std::string op = tokens[index];
    int next_precedence = get_precedence(op) + 1;
    auto right = parse(tokens, ++index, next_precedence);
    left = std::make_unique<ast::OperatorNode>(op, std::move(left),
                                               std::move(right));
  }
  if (index < tokens.size() && tokens[index] == ")")
    index++;

  return left;
}

} // namespace fexpr
