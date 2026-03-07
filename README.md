# c-shenanigans-with-the-seal-in-antartica-and-creating-making-gameplays
exactly what the title says

C++ project for learning the language.


```cpp
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
}
```