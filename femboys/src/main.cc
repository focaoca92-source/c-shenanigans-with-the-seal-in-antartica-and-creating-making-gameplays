#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <print>
#include <filesystem>
#include <iostream>
#include <windows.h>
#include <regex>
#include <memory>

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
        void start(){
            sf::RenderWindow thisFuckingWindow(sf::VideoMode({800, 600}), "femboy virus");

            // load image
            std::filesystem::path clean_img_path = GetTheMotherFuckingPath() += "\\img.jpg";
            const sf::Texture thisFuckingTexture(clean_img_path);
            sf::Sprite thisFuckingSprite(thisFuckingTexture);

            // load font and text
            std::filesystem::path clean_font_path = GetTheMotherFuckingPath() += "\\font.ttf";
            const sf::Font assFont(clean_font_path);
            sf::Text thisFuckingText(assFont, "hello cuties", 67);
            thisFuckingText.setFillColor(sf::Color::Black); // black color

            while (thisFuckingWindow.isOpen()){
                // event
                while (const std::optional event = thisFuckingWindow.pollEvent()){
                    if (event->is<sf::Event::Closed>()){
                        thisFuckingWindow.close();
                    }
                }

                thisFuckingWindow.clear();
                thisFuckingWindow.draw(thisFuckingSprite);
                thisFuckingWindow.draw(thisFuckingText);
                thisFuckingWindow.display();
            }
        }
};

int main() {
    std::println("Running");
    startProgram femboySpawn;
    femboySpawn.start();
    std::println("Stopped");
    return 0;
}
