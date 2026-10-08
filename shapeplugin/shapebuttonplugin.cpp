#include "shapebuttonplugin.h"
#include "shapebutton.h"

// Widget Box'ta görünen ad; uic'in üreteceği C++ sınıf adıyla aynı olmalı
QString ShapeButtonPlugin::name() const { return "ShapeButton"; }

// Widget Box'taki kategori başlığı
QString ShapeButtonPlugin::group() const { return "Compare Widgets"; }

QString ShapeButtonPlugin::toolTip() const { return "SVG path'li, dikdörtgen olmayan buton"; }
QString ShapeButtonPlugin::whatsThis() const { return toolTip(); }

// uic, ui_mainwindow.h içine bu include'u yazar
QString ShapeButtonPlugin::includeFile() const { return "shapebutton.h"; }

QIcon ShapeButtonPlugin::icon() const { return {}; }
bool ShapeButtonPlugin::isContainer() const { return false; }

// Designer canvas'ına sürüklendiğinde oluşturulan gerçek widget
QWidget *ShapeButtonPlugin::createWidget(QWidget *parent) { return new ShapeButton(parent); }

bool ShapeButtonPlugin::isInitialized() const { return m_initialized; }
void ShapeButtonPlugin::initialize(QDesignerFormEditorInterface *) { m_initialized = true; }

// Forma ilk bırakıldığındaki varsayılan .ui XML'i
QString ShapeButtonPlugin::domXml() const
{
    return R"(
<ui language="c++">
  <widget class="ShapeButton" name="shapeButton">
    <property name="geometry">
      <rect><x>0</x><y>0</y><width>120</width><height>130</height></rect>
    </property>
    <property name="text"><string>Button</string></property>
  </widget>
</ui>)";
}
