#ifndef SHAPEBUTTONPLUGIN_H
#define SHAPEBUTTONPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class ShapeButtonPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit ShapeButtonPlugin(QObject *parent = nullptr) : QObject(parent) {}

    QString name() const override;
    QString group() const override;
    QString toolTip() const override;
    QString whatsThis() const override;
    QString includeFile() const override;
    QIcon icon() const override;
    bool isContainer() const override;
    QWidget *createWidget(QWidget *parent) override;
    bool isInitialized() const override;
    void initialize(QDesignerFormEditorInterface *core) override;
    QString domXml() const override;

private:
    bool m_initialized = false;
};

#endif // SHAPEBUTTONPLUGIN_H
