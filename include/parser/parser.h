#pragma once

#include <optional>
#include <variant>
#include <vector>

#include "allocator/allocator.hpp"
#include "lexer/lexer.h"

namespace ypars {

struct NodeKey {
  Token key;
};

struct NodeValue;

struct NodeStmt {
  NodeKey* key;
  NodeValue* value;
};

struct NodeValue {
  std::variant<Token, std::vector<NodeStmt*>> var;
};

struct NodeProg {
  std::vector<NodeStmt*> stmts;
};

class parser {
 private:
  [[nodiscard]] std::optional<ypars::Token> peek(int) const;

  ypars::Token consume();

  void error_expected(const std::string& msg) const;

  ypars::Token try_consume_err(ypars::TokenType type);

  std::optional<ypars::Token> try_consume(ypars::TokenType type);

  const std::vector<ypars::Token> m_tokens;
  size_t m_index = 0;
  ArenaAllocator m_allocator;

 public:
  explicit parser(std::vector<Token> tokens)
      : m_tokens(std::move(tokens)), m_allocator(1024 * 1024 * 4) {}

  std::optional<NodeKey*> parse_key();

  std::optional<NodeValue*> parse_value();

  std::optional<NodeStmt*> parse_stmt();

  NodeProg* parse_prog();
};

}  // namespace ypars
