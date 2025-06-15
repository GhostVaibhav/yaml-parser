#pragma once

#include <optional>
#include <string>
#include <vector>

namespace ypars {

enum TokenType { KEY, VALUE, OP_COLON };

struct Token {
  TokenType type;
  std::optional<std::string> value;
  int indent = -1;
  int line;
};

std::string tokenToString(ypars::TokenType type);

class lexer {
 private:
  [[nodiscard]] std::optional<char> peek(const int offset = 0) const {
    if (m_index + offset >= m_src->size()) {
      return {};
    } else {
      return m_src->at(m_index + offset);
    }
  }

  char consume() { return m_src->at(m_index++); }

  std::shared_ptr<std::string> m_src;
  size_t m_index = 0;

 public:
  explicit lexer(const std::string& source) : m_src(std::make_shared<std::string>(source)) {}

  std::vector<Token> tokenize(const std::string &str);
};

}  // namespace ypars
