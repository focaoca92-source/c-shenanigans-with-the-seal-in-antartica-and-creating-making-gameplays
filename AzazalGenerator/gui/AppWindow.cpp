// main window GUI file
#include <iostream>
#include "AppWindow.hpp"
#include "image_loader.hpp"
#include <algorithm>

// fall logic
void mainWindow() {
    // check GLFW initialization first
    if (!glfwInit()){
        std::cerr << "Could not intialize GLFW!\n";
    }

    // get classes
    Window azazalWindow;
    WindowCreator win;
    win.windows.resize(40);

    GLFWwindow* window = glfwCreateWindow(1024, 640, "azazazazazazazazazaaaa rain", NULL, NULL); // create the window
    azazalWindow.start(window); // and start it

    if (window == NULL){
        std::cerr << "Could not make window!\n";
    }

    // image file loading
    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    bool LoadTex = LoadTextureFromFile("az.jpg", &my_image_texture, &my_image_width, &my_image_height); // zazaza
    IM_ASSERT(LoadTex);

    GLuint my_image_texture_2 = 0;
    bool LoadTex2 = LoadTextureFromFile("ro.jpg", &my_image_texture_2, &my_image_width, &my_image_height); // roka
    IM_ASSERT(LoadTex2);

    // main loop
    std::srand(std::time(nullptr)); // start the seed here for always random windows positions
    while(!glfwWindowShouldClose(window)){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // create window
        win.createWindow("Azazal", 40, my_image_texture, my_image_texture_2, my_image_width, my_image_height);

        ImGui::Render(); // render it
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    azazalWindow.end(window); // clean-up
}
