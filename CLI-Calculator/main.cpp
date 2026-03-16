/* @file main.cpp
 * @brief this is a simple but functional calculator that uses Shunting-yard algorithm to make calculations
 * Was a pain in the ass to make this work ngl
 * Important: no AI touched this code.
 * @author Creitin Gameplays
 * @date 2026-03-09
*/
#include <cctype>
#include <cstddef>
#include <print>
#include <variant>
#include <vector>
#include <string>

using string = std::string; // lazy to type std:: every line

// main
int main() {
    string exprToSolve {"3 + 4 * (12 - 4 * 5) / 2 + 3"}; // THIS IS THE EXPRESSION TO EVALUATE
    // so not a really CLI calculator, I would need to use cin to get user input and shit
    // i'll do this another time, for now keep this hardcoded 

    // call the function:
    double result = compute(exprToSolve);
    std::println("Final result: {}", result);
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
    std::vector<std::variant<string, char>> tokens;

    for (char character: expression){
        if (std::isdigit((static_cast<unsigned char>(character))) || character == '.'){
            current_number += character;
        } else {
            if (current_number != ""){
                tokens.push_back(current_number);
                current_number = "";
            }

            if (std::string("+-*/()").find(character) != std::string::npos){
                tokens.push_back(character);
            } else if (character == ' '){
                // do nothing
            }
        }
    }
    if (current_number != ""){
        tokens.push_back(current_number);
    }
    
    // setup
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
            while (operators_stack.size() > 0 && (std::string("+-*/").find(operators_stack.back()) != std::string::npos) && priority(operators_stack.back()) >= priority(std::get<char>(tokens[token]))) {
                if (!(operators_stack.empty())){
                    char top = operators_stack.back();
                    operators_stack.pop_back();
                    output.push_back(top);
                }
            }

            operators_stack.push_back(std::get<char>(tokens[token])); // get the char from the tokens vector

        } else if (std::get<char>(tokens[token]) == '(') { // if opening parenthesis
            operators_stack.push_back(std::get<char>(tokens[token]));

        } else if (std::get<char>(tokens[token]) == ')') { // if closing parenthesis
            while (operators_stack.size() > 0 && operators_stack.back() != '('){
                if (!(operators_stack.empty())){
                    char top = operators_stack.back();
                    operators_stack.pop_back();
                    output.push_back(top);
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
            output.push_back(top);
        }
    }
    
    std::vector<double> values_stack; // this is where things gonna happen

    for (size_t token {}; token < output.size(); token++){
        double temp_num;
        std::visit([&temp_num](auto& argm) { // store the value (by reference)
            temp_num = argm;
        }, output[token]);

        if (!(std::string("+-*/()").find(temp_num) != std::string::npos)){ // number
            values_stack.push_back(temp_num);

        } else {
            double b1 = values_stack.back();
            values_stack.pop_back();
            double b = b1;

            double a1 = values_stack.back();
            values_stack.pop_back();
            double a = a1;

            if (std::get<char>(output[token]) == '+'){
                values_stack.push_back(a + b);
            } else if (std::get<char>(output[token]) == '-'){
                values_stack.push_back(a - b);
            } else if (std::get<char>(output[token]) == '*'){
                values_stack.push_back(a * b);
            } else if (std::get<char>(output[token]) == '/'){
                values_stack.push_back(a / b);
            }
            // i could've used switch() here, but I like if-else more.
        }
    }

    std::println("****** Output {}", values_stack[0]);
    return values_stack[0]; // final result
}
