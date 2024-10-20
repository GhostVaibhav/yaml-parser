#pragma once

#include <iostream>
#include <optional>
#include <vector>

namespace ypars {

enum TokenType { _KEY, _VALUE, _OP_COLON };

struct Token {
  TokenType type;
  std::optional<std::string> value;
};

class lexer {
 private:
  std::optional<char> peek(int offset = 0) const {
    if (m_index + offset >= (*m_src).size()) {
      return {};
    } else {
      return (*m_src).at(m_index + offset);
    }
  }

  char consume() { return (*m_src).at(m_index++); }

  std::shared_ptr<std::string> m_src;
  size_t m_index = 0;

 public:
  lexer(std::string source) : m_src(std::make_shared<std::string>(source)) {}

  std::vector<Token> tokenize(std::shared_ptr<std::string> str);
};

}  // namespace ypars
