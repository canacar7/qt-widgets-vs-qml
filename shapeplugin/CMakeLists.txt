find_package(Qt6 REQUIRED COMPONENTS Widgets UiPlugin)

qt_add_plugin(mybuttonplugin)

target_sources(mybuttonplugin PRIVATE
    myshapeplugin.h
    myshapeplugin.cpp
    ../topic1/mybutton.h
    ../topic1/mybutton.cpp
)

target_include_directories(mybuttonplugin PRIVATE ../topic1)

target_link_libraries(mybuttonplugin PRIVATE Qt6::Widgets
                                             Qt6::UiPlugin)
