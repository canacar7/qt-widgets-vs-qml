find_package(Qt6 REQUIRED COMPONENTS Widgets UiPlugin)

qt_add_plugin(shapebuttonplugin)

target_sources(shapebuttonplugin PRIVATE
    shapebuttonplugin.h
    shapebuttonplugin.cpp
    ../shapebutton.h
    ../shapebutton.cpp
)

target_include_directories(shapebuttonplugin PRIVATE ..)
target_link_libraries(shapebuttonplugin PRIVATE Qt6::Widgets Qt6::UiPlugin)

# Plugin'i Qt Creator'ın designer klasörüne kopyalar.
# Elle çalıştırılır (Creator açıkken yüklü .so'nun üzerine yazmamak için):
#   cmake --build <build-dir> --target deploy_designer_plugin
# Sonra Creator yeniden başlatılmalı.
set(DESIGNER_PLUGIN_DIR "/home/can/Qt/Tools/QtCreator/lib/Qt/plugins/designer"
    CACHE PATH "Qt Creator designer plugin klasörü")
add_custom_target(deploy_designer_plugin
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:shapebuttonplugin> ${DESIGNER_PLUGIN_DIR}
    DEPENDS shapebuttonplugin
    COMMENT "ShapeButton plugin'i ${DESIGNER_PLUGIN_DIR} klasörüne kopyalanıyor"
)
