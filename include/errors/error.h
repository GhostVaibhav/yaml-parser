#pragma once

#include <iostream>
#include <tuple>
#include <string>

namespace vpars_error {
    // Function to return the error message and the error code
    std::tuple<std::string, int> get_error_info(int);

    // Function to pretty print the error message
    void print_error(int);

    // Function to pretty print the error message with additional information
    void print_error(int, std::string info);
}
