#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "image_loader.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#pragma once

// class to start and destroy the window
class Window {
public:
    void start(GLFWwindow* window){
        glfwMakeContextCurrent(window);
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
        glClearColor(0.20f, 0.0f, 0.45f, 1.00f); // this changes the main window background color
    }

    void end(GLFWwindow* window){
        //Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

struct WindowState {
    float x;
    float y;
    float vel;
};

class WindowCreator {
public:
    std::vector<WindowState> windows;
    float scaleSize{0.1f}; // make images larger or smaller
    void createWindow(std::string winName, int count, GLuint texture, GLuint texture2, int width, int height){
        ImVec2 imgSize((float)width * scaleSize, (float)height * scaleSize);
        ImVec2 imgSizeWin((float)width * scaleSize + 25, (float)height * scaleSize + 25);

        // window setup
        ImGuiWindowFlags win_flags = ImGuiWindowFlags_NoResize |  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse; // disable resizing.
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 0.0f, 0.0f, 0.0f)); // windows background (transparent)
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.0f, 0.0f, 0.0f)); // line border background (transparent)

        int half {count / 2};
        // fall animation
        for(int i{0}; i < count; i++) {
            windows[i].vel = 0.4f;
            windows[i].y += windows[i].vel;

            if (windows[i].y > 600.0f) {
                windows[i].y = -(std::rand() % 512);
                windows[i].vel = 0.4f;
                windows[i].x = std::rand() % 2048;
            }
        }

        // first window
        for(int i{0}; i < count; i++) {
            std::string titlename {winName + "!!!!!##" + std::to_string(i)}; 
            ImGui::SetNextWindowPos(ImVec2(windows[i].x, windows[i].y), ImGuiCond_Always);
            ImGui::SetNextWindowSize(imgSizeWin, ImGuiCond_Always); // windows size for images, where we can click

            if (ImGui::Begin(titlename.c_str(), nullptr, win_flags)) { // make unique windows
                if (i < half){
                    ImGui::Image((ImTextureID)(intptr_t)texture, imgSize); // load image
                }
                if (i > half) {
                    ImGui::Image((ImTextureID)(intptr_t)texture2, imgSize); // load another image
                }
            }

            ImGui::End();
        }

        // apply colors for windows background and borders
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
    }
};

void mainWindow();

