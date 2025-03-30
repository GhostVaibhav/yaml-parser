#pragma once

#include <string>

namespace ypars {

enum component {
  comp_lexer,
  comp_parser,
};

enum reason {
  reason_invalid_arg,
  reason_bad_optional_access,
  reason_bad_key_format,
  reason_bad_value_format,
  reason_bad_statement_format,
  reason_bad_colon_position
};

class error {
  component c;
  reason r;
  std::optional<int> line;
  std::optional<int> col;

 public:
  error(component _c, reason _r) : c(_c), r(_r) {}
  error(component _c, reason _r, int _line) : c(_c), r(_r), line(_line) {}
  error(component _c, reason _r, int _line, int _col)
      : c(_c), r(_r), line(_line), col(_col) {}

  std::string toString();
};

}  // namespace ypars
