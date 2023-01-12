cmake_minimum_required(VERSION 3.5)

project(TesseractLauncher VERSION 0.1 LANGUAGES CXX)

set(UI_QT_VERSION 6 CACHE STRING "xyz")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt${UI_QT_VERSION} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/window_main.cpp
        src/window_main.h
        ui/window_main.ui
)

add_executable(TesseractLauncher ${PROJECT_SOURCES})

target_link_libraries(TesseractLauncher PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(TesseractLauncher PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS TesseractLauncher
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
