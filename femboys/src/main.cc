#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <print>
#include <filesystem>
#include <iostream>
#include <windows.h>
#include <regex>
#include <memory>

// helper function to get the fucking ass program executable path, where
// the font and image files are.
std::filesystem::path GetTheMotherFuckingPath(){
    // win32
    wchar_t path[2048];
    GetModuleFileNameW(NULL, path, 2048);
    std::filesystem::path ced = std::filesystem::path(path);
    // go to parent dir
    std::filesystem::path clean_ced = ced.parent_path();
    return clean_ced;
}

class startProgram {
    public:
        startProgram(){
            sf::RenderWindow thisFuckingWindow(sf::VideoMode({800, 600}), "femboy virus");
            // load image
            std::filesystem::path clean_img_path = GetTheMotherFuckingPath() += "\\img.jpg";
            sf::Texture thisFuckingTexture(clean_img_path);
            sf::Sprite thisFuckingSprite(thisFuckingTexture);

            // load font and text
            std::filesystem::path clean_font_path = GetTheMotherFuckingPath() += "\\font.ttf";
            const sf::Font assFont(clean_font_path);
            sf::Text thisFuckingText(assFont, "hello cuties", 67);
            thisFuckingText.setFillColor(sf::Color::Black); // black color

            while (thisFuckingWindow.isOpen()){
                // event
                _sleep(80); // even the cpu and gpu need a rest (80ms update)
                while (const std::optional event = thisFuckingWindow.pollEvent()){
                    if (event->is<sf::Event::Closed>()){
                        thisFuckingWindow.close();
                    }
                }

                // show the stuff in real time
                thisFuckingWindow.clear();
                thisFuckingWindow.draw(thisFuckingSprite);
                thisFuckingWindow.draw(thisFuckingText);
                thisFuckingWindow.display();
            }
        }
};

int main() {
    std::println("Running");
    startProgram::startProgram();
    std::println("Stopped");
    return 0;
}
