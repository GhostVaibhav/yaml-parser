#include "lexer/lexer.h"

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "errors/error.h"
#include "logger/log.h"

std::string ypars::tokenToString(ypars::TokenType type) {
  switch (type) {
    case ypars::TokenType::_KEY:
      return "KEY";
    case ypars::TokenType::_VALUE:
      return "VALUE";
    case ypars::TokenType::_OP_COLON:
      return "OP_COLON";
    default:
      return "";
  }
}

std::vector<ypars::Token> ypars::lexer::tokenize(std::string str) {
  std::istringstream string(str);
  std::string buffer, lineBuffer;
  std::vector<Token> tokens;
  int line = 0, col = 0;

  try {
    while (std::getline(string, lineBuffer)) {
      m_src = std::make_shared<std::string>(lineBuffer);
      ypars::logger->info("Line recv: " + *m_src);
      int curIndent = 0;
      col = 0;
      while (peek().has_value()) {
        if (std::isalnum(peek().value())) {
          buffer.push_back(consume());
          while (peek().has_value() && std::isalnum(peek().value())) {
            buffer.push_back(consume());
          }
          ypars::logger->info("Reading in buffer: " + buffer);

          if (!tokens.empty() && tokens.back().type == TokenType::_OP_COLON &&
              tokens.back().line == line) {
            tokens.push_back(
                {.type = TokenType::_VALUE, .value = buffer, .line = line});
          } else {
            tokens.push_back({.type = TokenType::_KEY,
                              .value = buffer,
                              .indent = curIndent,
                              .line = line});
            curIndent = 0;
          }
          col += buffer.size();
          buffer.clear();
        } else if (peek().value() == ':') {
          if (tokens.empty() || tokens.back().type == TokenType::_VALUE) {
            throw std::invalid_argument("");
          }
          consume();
          tokens.push_back({.type = TokenType::_OP_COLON, .line = line});
          ++col;
        } else if (std::isspace(peek().value())) {
          ++col;
          consume();
          if (tokens.empty() ||
              (tokens.back().type == TokenType::_OP_COLON &&
               tokens.back().line != line) ||
              (tokens.back().type == TokenType::_VALUE &&
               tokens.back().line != line)) {
            ++curIndent;
          }
        } else {
          throw std::invalid_argument("");
        }
      }
      ++line;
      lineBuffer.clear();
      m_index = 0;
    }
  } catch (std::bad_optional_access& e) {
    ypars::error err(ypars::component::comp_lexer,
                     ypars::reason::reason_bad_optional_access, line, col);
    throw std::runtime_error(err.toString());
  } catch (std::invalid_argument& e) {
    ypars::error err(ypars::component::comp_lexer,
                     ypars::reason::reason_invalid_arg, line, col);
    throw std::runtime_error(err.toString());
  }

  return tokens;
}
