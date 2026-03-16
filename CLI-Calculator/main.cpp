/* @file main.cpp
 * @brief this is a simple but functional calculator that uses Shunting-yard algorithm to make calculations
 * Was a pain in the ass to make this work ngl
 * Important: no AI touched this code.
 * @author Creitin Gameplays
 * @date 2026-03-09
*/
#include <print>
#include <iostream>
#include <regex>
#include "calculator.hpp"

using string = std::string;

// main
int main() {
    string expression {}; // THIS IS THE EXPRESSION TO EVALUATE

    try {
        std::print("Write the expression: ");
        std::getline(std::cin, expression);

        // check if the expression is valid first
        std::regex exp_pattern(R"([0-9()+\-*/.])");
        std::regex letters_pattern(R"([a-zA-Z])");
        std::smatch Lmatch;
        std::smatch match;
        if (!std::regex_search(expression, match, exp_pattern)){
            throw std::runtime_error("Invalid expression!");
        }
        if (std::regex_search(expression, Lmatch, letters_pattern)) {
            throw std::runtime_error("Unsupported expression!");
        }

        // call the function:
        double result = compute(expression);
        std::println("Final result: {}", result);
    } catch (const std::exception &e) {
        std::cerr << "FATAL ERROR: " << e.what() << "\n";
    }

    return 0;
}

