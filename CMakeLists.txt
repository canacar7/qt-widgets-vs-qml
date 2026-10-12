cmake_minimum_required(VERSION 3.16)

project(compare VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(compare
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        topic1/mybutton.h topic1/mybutton.cpp
    )
endif()


target_link_libraries(compare PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(compare PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_include_directories(compare PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


include(GNUInstallDirs)

install(TARGETS compare
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(compare)
endif()


add_subdirectory(shapeplugin)
