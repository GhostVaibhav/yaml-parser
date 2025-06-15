#include "parser/parser.h"

#include <exception>
#include <optional>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

#include "errors/error.h"
#include "lexer/lexer.h"
#include "logger/log.h"

namespace ypars {

void parser::error_expected(const std::string& msg) const {
  const int line = peek(-1).value().line;
  ypars::logger->info("[" + std::to_string(line) + "]" + "[PARSER] Expected " +
                      msg);
  exit(EXIT_FAILURE);
}

std::optional<ypars::Token> parser::peek(const int offset = 0) const {
  if (m_index + offset >= m_tokens.size()) {
    return {};
  } else {
    return m_tokens.at(m_index + offset);
  }
}

ypars::Token parser::try_consume_err(const ypars::TokenType type) {
  if (peek().has_value() && peek().value().type == type) {
    return consume();
  } else {
    error_expected(tokenToString(type));
    return {};
  }
}

std::optional<ypars::Token> parser::try_consume(const ypars::TokenType type) {
  if (peek().has_value() && peek().value().type == type) {
    return consume();
  } else {
    return {};
  }
}

ypars::Token parser::consume() { return m_tokens.at(m_index++); }

std::optional<NodeKey*> parser::parse_key() {
  if (peek().has_value() && peek().value().type == TokenType::KEY) {
    auto key = m_allocator.alloc<NodeKey>();
    key->key = consume();
    return key;
  }
  throw std::runtime_error("KEY");
}

std::optional<NodeValue*> parser::parse_value() {
  if (peek(-1).has_value() && peek().has_value() &&
      peek(-1).value().indent < peek().value().indent &&
      peek(-1).value().line < peek().value().line) {
    auto value = m_allocator.alloc<NodeValue>();
    auto valueStmts = std::vector<NodeStmt*>();
    while (peek().has_value()) {
      if (auto stmt = parse_stmt()) {
        valueStmts.push_back(stmt.value());
      } else {
        throw std::runtime_error("VALUE");
      }
    }
    value->var = valueStmts;
    return value;
  } else if (peek().has_value() && peek().value().type == TokenType::VALUE) {
    auto value = m_allocator.alloc<NodeValue>();
    value->var = consume();
    return value;
  }
  throw std::runtime_error("VALUE");
}

std::optional<NodeStmt*> parser::parse_stmt() {
  if (peek().has_value() && peek().value().type == TokenType::KEY) {
    auto stmt = m_allocator.alloc<NodeStmt>();
    if (const auto keyStmt = parse_key()) {
      stmt->key = keyStmt.value();
    } else {
      throw std::runtime_error("KEY");
    }
    if (!try_consume(TokenType::OP_COLON).has_value()) {
      throw std::runtime_error("COLON");
    }
    if (const auto valStmt = parse_value()) {
      stmt->value = valStmt.value();
    } else {
      throw std::runtime_error("VALUE");
    }
    return stmt;
  }
  throw std::runtime_error("STATEMENT");
}

NodeProg* parser::parse_prog() {
  const auto prog = m_allocator.alloc<NodeProg>();
  try {
    while (peek().has_value()) {
      if (auto stmt = parse_stmt()) {
        prog->stmts.push_back(stmt.value());
      }
    }
  } catch (std::exception& e) {
    if (const std::string reason = e.what(); reason == "VALUE") {
      const ypars::error err(ypars::component::comp_parser,
                       ypars::reason::reason_bad_value_format);
      throw std::runtime_error(err.toString());
    } else if (reason == "KEY") {
      const ypars::error err(ypars::component::comp_parser,
                       ypars::reason::reason_bad_key_format);
      throw std::runtime_error(err.toString());
    } else if (reason == "STATEMENT") {
      const ypars::error err(ypars::component::comp_parser,
                       ypars::reason::reason_bad_statement_format);
      throw std::runtime_error(err.toString());
    } else if (reason == "COLON") {
      const ypars::error err(ypars::component::comp_parser,
                       ypars::reason::reason_bad_colon_position);
      throw std::runtime_error(err.toString());
    } else {
      ypars::logger->error(reason);
      const ypars::error err(ypars::component::comp_parser,
                       ypars::reason::reason_bad_optional_access);
      throw std::runtime_error(err.toString());
    }
  }
  return prog;
}

}  // namespace ypars
