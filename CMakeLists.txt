cmake_minimum_required(VERSION 4.1)
project(Bugs_Life_Project_2026)

set(CMAKE_CXX_STANDARD 20)

# After downloading SFML, put it in C:\SFML.
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(Bugs_Life_Project_2026 main.cpp
        Bug.cpp
        Bug.h
        Crawler.cpp
        Crawler.h
        Hopper.cpp
        Hopper.h
        Board.cpp
        Board.h
        DiagonalBug.cpp
        DiagonalBug.h
        sfml_display.cpp
        sfml_display.h)

target_link_libraries(Bugs_Life_Project_2026
        sfml-graphics
        sfml-window
        sfml-system)

# Copy the SFML .dll files beside the .exe after building.
file(GLOB SFML_DLL_FILES "C:/SFML/bin/*.dll")

add_custom_command(TARGET Bugs_Life_Project_2026 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SFML_DLL_FILES}
        $<TARGET_FILE_DIR:Bugs_Life_Project_2026>)
