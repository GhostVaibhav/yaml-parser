#include "errors/error.h"

namespace ypars {

// Function to return the error message and the error code
std::string error::toString() {
  std::string result = "";
  switch (c) {
    case comp_lexer:
      result += "[LEX] ";
      break;
    case comp_parser:
      result += "[PAR] ";
      break;
    default:
      break;
  }

  switch (r) {
    case reason_invalid_arg:
      result += "Invalid Argument";
      break;
    case reason_bad_optional_access:
      result += "Bad Optional Access";
      break;
    default:
      break;
  }

  if (line.has_value()) {
    result += " | Line: " + std::to_string(line.value());
  }

  if (col.has_value()) {
    result += ", Col: " + std::to_string(col.value());
  }

  return result;
}

}  // namespace ypars
