#pragma once

#include <iostream>

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

}  // namespace ypars
