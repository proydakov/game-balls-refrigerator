#include <ctime>

#include <QLabel>
#include <QPainter>
#include <QGridLayout>
#include <QPaintEvent>

#include <QDebug>

#include "main_window.h"
#include "grip_widget.h"
#include "lock_widget.h"
#include "game_controller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_background = QBrush(QColor(192, 192, 192));

    srand(time(NULL));

    setWindowTitle(tr("Game balls refrigerator"));
    setFixedSize(600, 750);

    QWidget *central = new QWidget(this);

    QGridLayout *layout = new QGridLayout(central);

    const size_t size = 4;
    m_controller.reset(new GameController(size));
    for(size_t x = 0; x < size; x++) {
        LockWidget *lock = new LockWidget(x, central);
        layout->addWidget(lock, 0, x);
        m_controller->addLock(lock);

        for(size_t y = 0; y < size; y++) {
            const int value = rand() % 2;
            const QPoint position(x, y);
            GripWidget *native = new GripWidget(position, central);
            native->setState(value);
            layout->addWidget(native, y + 1, x);
            m_controller->addGrip(native);
        }
    }

    m_controller->connect(m_controller.get(), SIGNAL(solve()), this, SLOT(solve()));
    m_controller->validate();

    central->setLayout(layout);

    setCentralWidget(central);
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), m_background);
}

void MainWindow::solve()
{
    qDebug() << "solve";

    QWidget *central = new QWidget(this);

    QGridLayout *layout = new QGridLayout(central);
    QLabel* text = new QLabel(tr("Solve!"), central);
    text->setAlignment(Qt::AlignCenter);

    QFont font = text->font();
    font.setPointSize(72);
    font.setBold(true);
    text->setFont(font);

    layout->addWidget(text, 0, 0);
    central->setLayout(layout);

    m_controller.reset();

    setCentralWidget(central);
}
