#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "misc/cpp/imgui_stdlib.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>

int start(SDL_Window*, SDL_Renderer*);
