/* @file calculator.cpp
 * @brief the calculator source code :broken_heart:
 * @author Creitin Gameplays
 * @date 2026-03-16
*/
#include <cctype>
#include <cstddef>
#include <print>
#include <variant>
#include <vector>
#include <string>

using string = std::string;

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
    std::vector<std::variant<string, unsigned char>> tokens;

    for (char character: expression){
        if (std::isdigit((static_cast<unsigned char>(character))) || character == '.'){
            current_number += character;
        } else {
            if (current_number != ""){
                tokens.push_back(current_number);
                current_number = "";
            }

            if (string("+-*/()").find(character) != string::npos){
                tokens.push_back(static_cast<unsigned char>(character));
            } else if (character == ' '){
                // do nothing
            } 
        }
    }
    if (current_number != ""){
        tokens.push_back(current_number);
    }
    
    // setup
    std::vector<std::variant<double, unsigned char>> output;
    std::vector<unsigned char> operators_stack;

    for (size_t token {0}; token < tokens.size(); token++){
        std::string temp_num {};
        std::string temp_op {};

        std::visit([&temp_num](auto& argm) { // store the value (by reference)
            temp_num = argm;
        }, tokens[token]);

        if (!(string("+-*/()").find(temp_num) != string::npos)){ // its a number
            double num = std::stod(temp_num); // convert to double
            output.push_back(num);

        } else if (string("+-*/").find(temp_num) != string::npos){ // its an operator
            while (operators_stack.size() > 0 && (string("+-*/").find(operators_stack.back()) != string::npos) && priority(operators_stack.back()) >= priority(std::get<unsigned char>(tokens[token]))) {
                if (!(operators_stack.empty())){
                    char top = operators_stack.back();
                    operators_stack.pop_back();
                    output.push_back(static_cast<unsigned char>(top));
                }
            }

            operators_stack.push_back(std::get<unsigned char>(tokens[token])); // get the char from the tokens vector

        } else if (std::get<unsigned char>(tokens[token]) == '(') { // if opening parenthesis
            operators_stack.push_back(std::get<unsigned char>(tokens[token]));

        } else if (std::get<unsigned char>(tokens[token]) == ')') { // if closing parenthesis
            while (operators_stack.size() > 0 && operators_stack.back() != '('){
                if (!(operators_stack.empty())){
                    char top = operators_stack.back();
                    operators_stack.pop_back();
                    output.push_back(static_cast<unsigned char>(top));
                }
            }

            if (operators_stack.size() > 0 && operators_stack.back() == '(') {
                if (!(operators_stack.empty())){
                    operators_stack.pop_back();
                }
            }
        }
    }

    while (operators_stack.size() > 0){
        if (!(operators_stack.empty())){
            char top = operators_stack.back();
            operators_stack.pop_back();
            output.push_back(static_cast<unsigned char>(top));
        }
    }
    
    std::vector<double> values_stack; // this is where things gonna happen
    for (size_t token {}; token < output.size(); token++){
        double temp_num;
        std::visit([&temp_num](auto& argm) { // store the value (by reference)
            temp_num = argm;
        }, output[token]);

        if (std::holds_alternative<double>(output[token])){ // number
            values_stack.push_back(temp_num); 

        } else {
            // error handling
            if (values_stack.size() < 2){
                throw std::runtime_error("Awkward error.");
            }

            double b1 = values_stack.back();
            values_stack.pop_back();
            double b = b1;

            double a1 = values_stack.back();
            values_stack.pop_back();
            double a = a1;

            if (std::get<unsigned char>(output[token]) == '+'){
                values_stack.push_back(a + b);
            } else if (std::get<unsigned char>(output[token]) == '-'){
                values_stack.push_back(a - b);
            } else if (std::get<unsigned char>(output[token]) == '*'){
                values_stack.push_back(a * b);
            } else if (std::get<unsigned char>(output[token]) == '/'){
                values_stack.push_back(a / b);
            }
            // i could've used switch() here, but I like if-else more.
        }
    }

    if (!values_stack.empty() && values_stack[0]) {
        std::println("OUTPUT = {}", values_stack[0]);
        return values_stack[0]; // final result
    } else {
        throw std::runtime_error("Fatal error occurred");
    }
}
