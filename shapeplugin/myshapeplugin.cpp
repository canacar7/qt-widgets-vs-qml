#include "myshapeplugin.h"
#include "../topic1/mybutton.h"

MyShapePlugin::MyShapePlugin(QObject* obj) : QObject(obj)
{

}


QWidget *MyShapePlugin::createWidget(QWidget *parent)
{
    return new MyButton(parent);
}

//forma birakildiginda baslangic boyutu ve yazisi
QString MyShapePlugin::domXml() const
{
    return R"(
    <ui language="c++">
      <widget class="MyButton" name="myButton">
        <property name="geometry">
          <rect><x>0</x><y>0</y><width>130</width><height>130</height></rect>
        </property>
        <property name="text">
          <string>Button</string>
        </property>
      </widget>
    </ui>)";
}


//Widget sınıf adi ile birebir aynı olamlidir
QString MyShapePlugin::name() const
{
    return "MyButton";
}

//widget box daki kategori basligi
QString MyShapePlugin::group() const
{
    return "Customn";
}

//uic ui_mainwindow.h icine bu #include yazacak
QString MyShapePlugin::includeFile() const
{
    return "topic1/mybutton.h";
}


QIcon MyShapePlugin::icon() const
{
    return {};
}

bool MyShapePlugin::isContainer() const
{
    return false;
}

QString MyShapePlugin::toolTip() const
{
    return {};
}

QString MyShapePlugin::whatsThis() const
{
    return {};
}
