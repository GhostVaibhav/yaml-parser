#include "lexer/lexer.h"

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "errors/error.h"
#include "logger/log.h"

std::string ypars::tokenToString(const ypars::TokenType type) {
  switch (type) {
    case ypars::TokenType::KEY:
      return "KEY";
    case ypars::TokenType::VALUE:
      return "VALUE";
    case ypars::TokenType::OP_COLON:
      return "OP_COLON";
    default:
      return "";
  }
}

std::vector<ypars::Token> ypars::lexer::tokenize(const std::string& str) {
  std::istringstream string(str);
  std::vector<Token> tokens;
  int line = 0, col = 0;

  try {
    int lastIndent = 0;
    std::string lineBuffer;
    std::string buffer;
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

          if (!tokens.empty() && tokens.back().type == TokenType::OP_COLON &&
              tokens.back().line == line) {
            tokens.push_back(
                {.type = TokenType::VALUE, .value = buffer, .line = line});
          } else {
            // Key is inserted here
            if (!tokens.empty()) {
              bool keyInserted = false;
              // If the current indent is more
              if (curIndent >= lastIndent) {
                tokens.push_back({.type = TokenType::KEY,
                                  .value = buffer,
                                  .indent = curIndent,
                                  .line = line});
                keyInserted = true;
                // If the current indent is less
              } else {
                int prevIndent = lastIndent;
                for (size_t i = tokens.size() - 1; i > 0; --i) {
                  if (tokens[i].type == TokenType::KEY &&
                      tokens[i].indent < prevIndent) {
                    prevIndent = tokens[i].indent;
                    if (prevIndent == curIndent) {
                      tokens.push_back({.type = TokenType::KEY,
                                        .value = buffer,
                                        .indent = curIndent,
                                        .line = line});
                      keyInserted = true;
                      break;
                    }
                  }
                }
              }
              if (!keyInserted) {
                throw std::runtime_error("INDENT");
              }
            } else {
              tokens.push_back({.type = TokenType::KEY,
                                .value = buffer,
                                .indent = curIndent,
                                .line = line});
            }
          }
          lastIndent = curIndent;
          curIndent = 0;
          col += static_cast<int>(buffer.size());
          buffer.clear();
        } else if (peek().value() == ':') {
          // Check if we can have a colon here
          if (tokens.empty() || tokens.back().type == TokenType::VALUE) {
            throw std::invalid_argument("Invalid colon placement");
          }
          consume();
          tokens.push_back({.type = TokenType::OP_COLON, .line = line});
          ++col;
          
          // After colon, we can have either a value or end of line
          // Skip any remaining whitespace on this line
          while (peek().has_value() && std::isspace(peek().value())) {
            consume();
            ++col;
          }
          
          // If there's no value after colon, that's fine - the key can exist without a value
          // The next token will be processed on the next iteration or next line
        } else if (std::isspace(peek().value())) {
          ++col;
          consume();
          if (tokens.empty() ||
              (tokens.back().type == TokenType::OP_COLON &&
               tokens.back().line != line) ||
              (tokens.back().type == TokenType::VALUE &&
               tokens.back().line != line)) {
            ++curIndent;
          }
        } else {
          throw std::invalid_argument("Unexpected character");
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
