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

void startProgram(){
    sf::RenderWindow thisFuckingWindow(sf::VideoMode({800, 600}), "femboy virus");
    std::filesystem::path clean_base_path = GetTheMotherFuckingPath(); // base path

    // load image
    std::filesystem::path clean_img_path = clean_base_path / "img.jpg";
    sf::Texture thisFuckingTexture;

    if (!thisFuckingTexture.loadFromFile(clean_img_path)){
        std::println(stderr, "Couldn't load image\n");
    };

    sf::Sprite thisFuckingSprite(thisFuckingTexture);

    // load font and text
    std::filesystem::path clean_font_path = clean_base_path / "font.ttf";
    sf::Font assFont;

    if (!assFont.openFromFile(clean_font_path)){
        std::println(stderr, "Couldn't load font file\n");
    }

    sf::Text thisFuckingText(assFont, "hello cuties", 67);
    thisFuckingText.setFillColor(sf::Color::Black); // black color

    while (thisFuckingWindow.isOpen()){
        // even the cpu and gpu need a rest (80ms update).
        // yes clang++ i know this is deprecated and Windows-only, but it's working so
        // won't bother with that for now
        // Linus once said: "don't fix what's not broken" (he probably never said that though)
        _sleep(80);

        // events
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

int main() {
    std::println("Running");
    startProgram();
    std::println("Stopped");
    return 0;
}

// issues according to "hey claude":
// 1. lazy
