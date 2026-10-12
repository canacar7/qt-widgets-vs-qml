#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "topic1/mybutton.h"

#include <QEvent>
#include <QLabel>
#include <QPainter>
#include <QPaintEngine>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QDebug>

#include <sys/resource.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Koyu arka plan
    QPalette pal = ui->widget->palette();
    pal.setColor(QPalette::Window, QColor("#1E1F22"));
    ui->widget->setPalette(pal);
    ui->widget->setAutoFillBackground(true);

    // ui->widget her çizildiğinde eventFilter çağrılsın (FPS sayımı)
    ui->widget->installEventFilter(this);

    // Bilgi kutusu
    m_stats = new QLabel(ui->widget);
    m_stats->setStyleSheet("background: rgba(0,0,0,200); color: white; font: bold 14px monospace; padding: 8px;");
    m_stats->move(10, 10);

    // Her 2 saniyede 50 buton ekle
    connect(&m_spawnTimer, &QTimer::timeout, this, [this]() { addButtons(kButtonsPerSpawn); });
    m_spawnTimer.start(kSpawnIntervalMs);

    // Saniyede bir: FPS ve CPU
    connect(&m_statsTimer, &QTimer::timeout, this, &MainWindow::updateStats);
    m_statsTimer.start(1000);

    m_lastCpuSeconds = processCpuSeconds();
    m_statsClock.start();

    // Pencere açılıp boyutlar belli olduktan sonra ilk butonları ekle
    QTimer::singleShot(0, this, [this]() { addButtons(kButtonsPerSpawn); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addButtons(int count)
{
    QWidget *area = ui->widget;
    auto *rng = QRandomGenerator::global();
    auto randomPoint = [area, rng]() {
        return QPoint(rng->bounded(qMax(area->width() - 44, 1)), rng->bounded(qMax(area->height() - 48, 1)));
    };

    for (int i = 0; i < count; ++i) {
        auto *button = new MyButton(area);    // topic1'deki buton, yeniden tanımlamıyoruz
        button->setText(QString());
        button->setFixedSize(44, 48);         // MyButton'un 130x130 minimum boyutunu ez
        button->show();

        // A -> B -> A, sonsuz döngü
        const QPoint a = randomPoint();
        const QPoint b = randomPoint();
        auto *anim = new QPropertyAnimation(button, "pos", button);
        anim->setDuration(2000 + rng->bounded(2000));
        anim->setStartValue(a);
        anim->setKeyValueAt(0.5, b);
        anim->setEndValue(a);
        anim->setEasingCurve(QEasingCurve::InOutSine);
        anim->setLoopCount(-1);
        anim->start();
    }
    m_buttonCount += count;
    m_stats->raise();                         // bilgi kutusu butonların üstünde kalsın
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->widget && event->type() == QEvent::Paint) {
        ++m_frames;

        // Hangi çizim motoru? Çizim anında bir kez sor. Normal bir QWidget için: Raster (CPU)
        if (m_engineName.isEmpty()) {
            QPainter painter(ui->widget);
            m_engineName = painter.paintEngine()->type() == QPaintEngine::Raster ? "Raster (CPU)" : "Other";
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::updateStats()
{
    const double seconds = m_statsClock.restart() / 1000.0;
    const double cpu = processCpuSeconds();
    const double cpuPercent = (cpu - m_lastCpuSeconds) / seconds * 100.0;
    m_lastCpuSeconds = cpu;

    const double fps = m_frames / seconds;
    m_frames = 0;

    m_stats->setText(QString("Items  : %1\nFPS    : %2\nCPU    : %3 %\nEngine : %4")
                         .arg(m_buttonCount)
                         .arg(fps, 0, 'f', 0)
                         .arg(cpuPercent, 0, 'f', 0)
                         .arg(m_engineName));
    m_stats->adjustSize();

    qInfo().noquote() << QString("items=%1  fps=%2  cpu=%3%  engine=%4")
                             .arg(m_buttonCount)
                             .arg(fps, 0, 'f', 0)
                             .arg(cpuPercent, 0, 'f', 0)
                             .arg(m_engineName);
}

// Bu sürecin harcadığı toplam CPU süresi (user + system), saniye
double MainWindow::processCpuSeconds()
{
    rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    return ru.ru_utime.tv_sec + ru.ru_utime.tv_usec / 1e6 + ru.ru_stime.tv_sec + ru.ru_stime.tv_usec / 1e6;
}
