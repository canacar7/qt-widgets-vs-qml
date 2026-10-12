#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include <QTimer>

class QLabel;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // ui->widget'ın çizimlerini saymak için (FPS)
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    // Topic 2: animasyon testi
    void addButtons(int count);
    void updateStats();
    static double processCpuSeconds();

    static constexpr int kButtonsPerSpawn = 200;
    static constexpr int kSpawnIntervalMs = 2000;

    Ui::MainWindow *ui;

    QLabel *m_stats = nullptr;
    int m_buttonCount = 0;

    QTimer m_spawnTimer;   // her 2 sn'de buton ekle
    QTimer m_statsTimer;   // saniyede bir FPS ve CPU
    QElapsedTimer m_statsClock;

    int m_frames = 0;      // saniyede çizilen kare = FPS
    double m_lastCpuSeconds = 0.0;
    QString m_engineName;
};
#endif // MAINWINDOW_H
