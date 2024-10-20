#include "lexer/lexer.h"

#include <exception>
#include <iostream>
#include <vector>

#include "errors/error.h"
#include "logger/log.h"

std::vector<ypars::Token> ypars::lexer::tokenize(
    std::shared_ptr<std::string> str) {
  m_src = str;
  std::string buffer;
  std::vector<Token> tokens;

  try {
    while (peek().has_value()) {
      ypars::logger->info("Index: " + std::to_string(m_index));
      if (std::isalnum(peek().value())) {
        buffer.push_back(consume());
        while (peek().has_value() && std::isalnum(peek().value())) {
          buffer.push_back(consume());
        }

        if (!tokens.empty() && tokens.back().type == TokenType::_OP_COLON) {
          tokens.push_back({.type = TokenType::_VALUE, .value = buffer});
        } else {
          tokens.push_back({.type = TokenType::_KEY, .value = buffer});
        }
        buffer.clear();
      } else if (peek().value() == ':') {
        consume();
        tokens.push_back({.type = TokenType::_OP_COLON});
      } else if (std::isspace(peek().value())) {
        consume();
      } else {
        throw std::invalid_argument("");
      }
    }
  } catch (std::bad_optional_access& e) {
    ypars::error err(ypars::component::comp_lexer,
                     ypars::reason::reason_bad_optional_access);
    throw std::runtime_error(err.toString());
  } catch (std::invalid_argument& e) {
    ypars::error err(ypars::component::comp_lexer,
                     ypars::reason::reason_invalid_arg);
    throw std::runtime_error(err.toString());
  }

  m_index = 0;
  return tokens;
}
