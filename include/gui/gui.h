#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "lexer/lexer.h"

namespace ypars {

class gui {
 public:
  static int start(SDL_Window *, SDL_Renderer *, ypars::lexer &);
};

}  // namespace ypars
