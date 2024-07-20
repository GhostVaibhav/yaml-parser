// Specifying the header files
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

// Specifying the include files
#include "constants.h"

using namespace std;

// Function to process the input
void process(string buffer) {
    // Printing the buffer
    cout << buffer << endl;
}

int main(int argc, char *argv[]) {
#ifdef DEBUG
    // Printing the number and value of args
    cout << "Number of args: " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "Arg " << i << ": " << argv[i] << endl;
    }
#endif

    // Checking for the number of args
    if (argc == 3) {
        // Storing the flag value in a string variable
        string flag = argv[1];

        if(flag == "-f" || flag == "--file") {
            // Convert relative path to absolute path
            std::filesystem::path path = std::filesystem::absolute(argv[2]);

            // Reading from a file
            ifstream file(path.string());

            // Initializing the main buffer for the program
            string buffer = "";

            // Checking if the file is open
            if (file.is_open()) {
                // Reading the file line by line
                while (getline(file, buffer)) {
                    process(buffer);
                }
                file.close();
            } else {
                cout << "Error: Unable to open the file" << endl;
            }
        }
    }
    return 0;
}
