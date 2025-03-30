#pragma once

#include <string>
#include <vector>

#include "lexer/lexer.h"

#define DEBUG
#define iscs(key, val) inline static const std::string key = val

namespace ypars {

class constant {
 public:
  iscs(appName, "YAML Parser");
  iscs(authorName, "Vaibhav Sharma");
  iscs(majorVersion, "0");
  iscs(minorVersion, "1");
};

static std::string text;
static std::vector<ypars::Token> tokens;

}  // namespace ypars
