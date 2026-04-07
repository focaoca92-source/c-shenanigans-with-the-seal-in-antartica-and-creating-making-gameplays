#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <print>
#include <filesystem>
#include <iostream>
#include <windows.h>
#include <regex>

int main() {
    std::println("Running");

    // win32
    wchar_t path[2048];
    GetModuleFileNameW(NULL, path, 2048);
    std::filesystem::path ced = std::filesystem::path(path);
    // go to parent dir
    std::filesystem::path clean_ced1 = ced.parent_path();
    std::filesystem::path clean_ced2 = ced.parent_path(); 

    sf::RenderWindow thisFuckingWindow(sf::VideoMode({1280, 720}), "testing");

    // load image
    std::filesystem::path clean_img_path = clean_ced1 += "\\img.jpg";
    const sf::Texture thisFuckingTexture(clean_img_path);
    sf::Sprite thisFuckingSprite(thisFuckingTexture);

    // load font and text
    std::filesystem::path clean_font_path = clean_ced2 += "\\font.ttf";
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

    std::println("Stopped");
    return 0;
}
