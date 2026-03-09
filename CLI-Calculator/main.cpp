#include <cctype>
#include <cstddef>
#include <iostream>
#include <print>
#include <map>
#include <sys/types.h>
#include <typeinfo>
#include <variant>
#include <vector>
#include <string>
#include <charconv>

using string = std::string;

// declarations
double compute(string expression);
int priority(char op);

// main
int main() {
    string exprToSolve {"3 + 4 * (12 - 4 * 5) / 2 + 3"};

    // call the function:
    compute(exprToSolve);

    return 0;
}

int priority(char op){
    if (op == '+' || op == '-'){
        return 1;
    } else if (op == '*' || op == '/'){
        return 2;
    } else {
        return 0;
    }
}

double compute(string expression) {
    string current_number {};
    // std::map<double, char> token;

    std::vector<std::variant<string, char>> tokens;

    for (char character: expression){
        if (std::isdigit((character)) || character == '.'){
            current_number += character;
        } else {
            if (current_number != ""){
                tokens.push_back(current_number);
                current_number = "";
            }

            if (std::string("+-*/()").find(character) != std::string::npos){
                tokens.push_back(character);
            } else if (character == ' '){
                continue; // do nothing
            }
        }
    }
    if (current_number != ""){
        tokens.push_back(current_number);
    }

    std::println("Expression cleaned:");
    for (size_t i {0}; i < tokens.size(); i++){
        std::visit([](auto& argm) {
            //std::println("Numbers and expression: {}", argm);
        }, tokens[i]);
    }
    std::println();
    
    std::vector<std::variant<double, char>> output;
    std::vector<char> operators_stack;

    for (size_t token {0}; token < tokens.size(); token++){
        std::string temp_num {};
        std::string temp_op {};

        std::visit([&temp_num](auto& argm) { // store the value (by reference)
            temp_num = argm;
        }, tokens[token]);

        if (!(std::string("+-*/()").find(temp_num) != std::string::npos)){ // its a number
            double num = std::stod(temp_num); // convert to double
            output.push_back(num);
        } else if (std::string("+-*/").find(temp_num) != std::string::npos){ // its an operator
            while (operators_stack.size() > 0 && (std::string("+-*/").find(operators_stack[-1]) != std::string::npos) && priority(operators_stack[-1]) >= priority(std::get<char>(tokens[token]))) {
                std::println("Test {}", operators_stack[-1]);
                output.push_back(operators_stack[-1]); // ?
            }

            if (!(operators_stack.empty())){ // prevent seg fault
                char top = operators_stack.back();
                operators_stack.pop_back();
                output.push_back(top);
            }
            
        }
    }
    
    // debug
    for (size_t i {0}; i < output.size(); i++){
        std::visit([output](auto& argm) {
            std::println("Numbers on output: {}", argm);
        }, output[i]);
    }

    return 0;
}
