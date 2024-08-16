// Specifying the header files
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

// Specifying the include files
#include "logger/log.h"
#include "constants/constants.h"
#include "lexer/lexer.h"
#include "errors/error.h"
#include "gui/gui.h"

std::shared_ptr<spdlog::logger> logger;

void initLogger() {
    logger = spdlog::stdout_color_mt("ypars");
}

int main(int argc, char *argv[])
{
    initLogger();
    logger->info("Starting the program");
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        logger->error("Error: %s\n", SDL_GetError());
        return -1;
    }

#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with SDL_Renderer graphics context
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window *window = SDL_CreateWindow("YAML Parser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    if (window == nullptr)
    {
        logger->error("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        logger->error("Error creating SDL_Renderer!");
        return 0;
    }
    logger->info("Window and renderer created successfully");

    start(window, renderer);

    logger->info("Shutting down the program");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    // ----------------------------------------------------------------------------------------
    // #ifdef DEBUG
    //     // Printing the number and value of args
    //     std::cout << "Number of args: " << argc << std::endl;
    //     for (int i = 0; i < argc; i++)
    //     {
    //         std::cout << "Arg " << i << ": " << argv[i] << std::endl;
    //     }
    // #endif

    //     // Checking for the number of args
    //     if (argc == 3)
    //     {
    //         // Storing the flag value in a string variable
    //         std::string flag = argv[1];

    //         if (flag == "-f" || flag == "--file")
    //         {
    //             // Convert relative path to absolute path
    //             std::filesystem::path path = std::filesystem::absolute(argv[2]);

    //             // Reading from a file
    //             std::ifstream file(path.string());

    //             // Initializing the main buffer for the program
    //             std::string buffer = "";

    //             // Checking if the file is open
    //             if (file.is_open())
    //             {
    //                 // Reading the file line by line
    //                 while (std::getline(file, buffer))
    //                 {
    //                     process(buffer);
    //                 }
    //                 file.close();
    //             }
    //             else
    //             {
    //                 // Printing the error message
    //                 vpars_error::print_error(1);

    //                 // Returning the error code
    //                 return 1;
    //             }
    //         }
    //     }
    return 0;
}
