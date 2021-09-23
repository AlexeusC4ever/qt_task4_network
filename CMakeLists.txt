cmake_minimum_required(VERSION 3.5)

project(qt_task4_network VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED Widgets Network Xml)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

qt_wrap_cpp(MOC_WRAPPERS
    mainwindow.h
    )

qt_wrap_ui(UIC_WRAPPERS
    mainwindow.ui
    )

add_executable(qt_task4_network
    ${PROJECT_SOURCES}
    ${MOC_WRAPPERS}
    ${UIC_WRAPPERS})

target_link_libraries(qt_task4_network PRIVATE
    Qt6::Widgets
    Qt6::Network
    Qt6::Xml)

