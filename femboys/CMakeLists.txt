cmake_minimum_required(VERSION 3.10)
project(Femboys)

# C++23 default fuck
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 3.0.2 COMPONENTS Graphics Window System REQUIRED)

add_executable(Femboys src/main.cc)
target_link_libraries(Femboys PRIVATE SFML::Graphics SFML::Window SFML::System)

# copy runtime DLLs and font from project bin/ into the target output dir
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")

if (EXISTS "${BIN_DIR}")
  file(GLOB RUNTIME_DLLS "${BIN_DIR}/*")

  foreach(_dll IN LISTS RUNTIME_DLLS)
    add_custom_command(TARGET Femboys POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_dll}" "$<TARGET_FILE_DIR:Femboys>"
      COMMENT "Copying ${_dll} -> $<TARGET_FILE_DIR:Femboys>"
    )
  endforeach()

  add_custom_command(TARGET Femboys POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${BIN_DIR}/font.ttf" "$<TARGET_FILE_DIR:Femboys>"
    COMMENT "Copying font.ttf -> $<TARGET_FILE_DIR:Femboys>"
  )
endif()

# if msvc is being a dick
if(MSVC)
    target_compile_options(Femboys PRIVATE /std:c++latest)
endif()