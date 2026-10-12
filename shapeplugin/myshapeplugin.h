#ifndef MYSHAPEPLUGIN_H
#define MYSHAPEPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>

//Designer a mybutton sınıfını tanıtacak sınıf.
class MyShapePlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    //qt nin plugin sistemi bu sinifi bu kimlikte bulacak
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
    //Bu sinifin hangi arayuzu uyguladigini Qt ye bildirir.
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit  MyShapePlugin(QObject* parent = nullptr);

    // QDesignerCustomWidgetInterface interface
public:
    QString name() const override;
    QString group() const override;
    QString toolTip() const override;
    QString whatsThis() const override;
    QString includeFile() const override;
    QIcon icon() const override;
    bool isContainer() const override;
    QWidget *createWidget(QWidget *parent) override;
    QString domXml() const override;
};
#endif // MYSHAPEPLUGIN_H
