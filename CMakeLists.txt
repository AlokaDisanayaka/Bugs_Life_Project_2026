cmake_minimum_required(VERSION 4.1)
project(Bugs_Life_Project_2026)

set(CMAKE_CXX_STANDARD 20)

# If SFML is installed manually, this is the expected folder:
# C:\SFML\lib\cmake\SFML
set(SFML_DIR "C:/SFML/lib/cmake/SFML" CACHE PATH "Path to SFMLConfig.cmake" FORCE)

find_package(SFML 2.6 COMPONENTS graphics window system QUIET)

add_executable(Bugs_Life_Project_2026
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
        main.cpp
        sfml_view.cpp
        sfml_view.h)

if(SFML_FOUND)
        target_compile_definitions(Bugs_Life_Project_2026 PRIVATE HAVE_SFML)

        target_link_libraries(Bugs_Life_Project_2026
                sfml-graphics
                sfml-window
                sfml-system)

        file(GLOB SFML_DLL_FILES "C:/SFML/bin/*.dll")

        add_custom_command(TARGET Bugs_Life_Project_2026 POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SFML_DLL_FILES}
                $<TARGET_FILE_DIR:Bugs_Life_Project_2026>)
else()
        message(WARNING "SFML was not found. The console project will still build, but the SFML visualizer needs SFML installed.")
endif()
