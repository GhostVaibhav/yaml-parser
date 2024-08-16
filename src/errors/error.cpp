#include "errors/error.h"

namespace vpars_error {
    // Function to return the error message and the error code
    std::tuple<std::string, int> get_error_info(int error_code) {
        switch(error_code) {
            case 1:
                return {"Unable to open the file", error_code};
            default:
                return {"Unknown error", error_code};
        }
    }

    // Function to pretty print the error message
    void print_error(int error_code) {
        auto [msg, code] = get_error_info(error_code);
        std::cout << "Code: " << code << " | " << msg << std::endl;
    }

    // Function to pretty print the error message with additional information
    void print_error(int error_code, std::string info) {
        auto [msg, code] = get_error_info(error_code);
        std::cout << "Code: " << code << " | " << msg << ": " << info << std::endl;
    }
}
