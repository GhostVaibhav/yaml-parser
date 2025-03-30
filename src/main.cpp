#include <string>

#include "constants/constants.h"
#include "gui/gui.h"
#include "lexer/lexer.h"
#include "logger/log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace ypars {

std::shared_ptr<spdlog::logger> logger;
void initLogger() { logger = spdlog::stdout_color_mt("ypars"); }

}  // namespace ypars

int main(int argc, char *argv[]) {
  int returnCode = 0;
  ypars::initLogger();
  ypars::logger->info("Starting the program");
  SDL_SetMainReady();
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
      0) {
    ypars::logger->error("Error: %s\n", SDL_GetError());
    return -1;
  }

#ifdef SDL_HINT_IME_SHOW_UI
  SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

  // Create window with SDL_Renderer graphics context
  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Window *window =
      SDL_CreateWindow(ypars::constant::appName.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
  if (window == nullptr) {
    ypars::logger->error("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
    return -1;
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    ypars::logger->error("Error creating SDL_Renderer!");
    return 0;
  }
  ypars::logger->info("Window and renderer created successfully");

  ypars::gui g;
  ypars::lexer l(ypars::text);

  try {
    g.start(window, renderer, l);
  } catch (std::exception &e) {
    ypars::logger->error(e.what());
    returnCode = 1;
  }

  ypars::logger->info("Shutting down the program");
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return returnCode;
}
