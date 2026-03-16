# c-shenanigans-with-the-seal-in-antartica-and-creating-making-gameplays
exactly what the title says

C++ project for learning the language.


```cpp
/* @file README.md
 * @brief This is just a random snippet that uses try-catch. Nothing really crazy or some shit
 * note: this snippet code requires C++23
 * @author Creitin Gameplays
 * @date 2026-03-07
*/
import std;

int main(){
    int age {16};

    try {
        if (age < 18){
            throw std::runtime_error("u gotta be adult!");
        }
    } catch (const std::exception &e) {
        std::println("Error: {}", e.what());
    }

    return 0;
}
```

Debug:
```
gdb ./build/calculator
(gdb) run
(gdb) bt
```
