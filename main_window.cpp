#include <ctime>

#include <QLabel>
#include <QPushButton>

#include <QPainter>
#include <QGridLayout>
#include <QPaintEvent>

#include <QDebug>

#include "main_window.h"
#include "grip_widget.h"
#include "lock_widget.h"
#include "start_widget.h"
#include "game_controller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_background = QBrush(QColor(192, 192, 192));

    srand(time(NULL));

    setWindowTitle(tr("Game balls refrigerator"));
    setFixedSize(600, 750);

    create();
}

MainWindow::~MainWindow()
{
}

void MainWindow::start(size_t size)
{
    qDebug() << "start: " << size;

    QWidget *central = new QWidget(this);
    QGridLayout *layout = new QGridLayout(central);

    GameController* controller = new GameController(size, central);
    for(size_t x = 0; x < size; x++) {
        LockWidget *lock = new LockWidget(x, central);
        layout->addWidget(lock, 0, x);
        controller->addLock(lock);

        for(size_t y = 0; y < size; y++) {
            const int value = rand() % 2;
            const QPoint position(x, y);
            GripWidget *native = new GripWidget(position, central);
            native->setState(value);
            layout->addWidget(native, y + 1, x);
            controller->addGrip(native);
        }
    }

    controller->connect(controller, SIGNAL(solve()), this, SLOT(solve()));
    controller->validate();

    central->setLayout(layout);

    setCentralWidget(central);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), m_background);
}

void MainWindow::create()
{
    qDebug() << "create";

    QWidget *central = new QWidget(this);

    QGridLayout *layout = new QGridLayout(central);

    const size_t max_size = 10;
    const size_t min_size = 2;
    const size_t size = max_size - min_size + 1;
    Q_ASSERT(size > 0);
    std::vector<QWidget*> items(size, nullptr);
    for(size_t i = 0; i < size; i++) {
        items[i] = new StartWidget(i + min_size, central);
        items[i]->connect(items[i], SIGNAL(select(size_t)), this, SLOT(start(size_t)));
    }

    const size_t max_x = 3;
    const size_t max_y = size / max_x + 1;
    layout->addWidget(items[0], 0, 0);
    for(size_t x = 0; x < max_x; x++) {
        for(size_t y = 0; y < max_y; y++) {
            const size_t index = x + y * max_x;
            if(index >= items.size()) {
                break;
            }
            layout->addWidget(items[index], y, x);
        }
    }
    central->setLayout(layout);

    setCentralWidget(central);
}

void MainWindow::solve()
{
    qDebug() << "solve";

    QFont font;
    font.setPointSize(72);
    font.setBold(true);

    QWidget *central = new QWidget(this);

    QGridLayout *layout = new QGridLayout(central);
    QLabel* text = new QLabel(tr("Solve!"), central);
    text->setAlignment(Qt::AlignCenter);
    text->setFont(font);

    QPushButton *button = new QPushButton(tr("Restart"), central);
    button->setFont(font);
    button->connect(button, SIGNAL(clicked(bool)), this, SLOT(create()));

    layout->addWidget(text, 0, 0);
    layout->addWidget(button, 1, 0);

    central->setLayout(layout);

    setCentralWidget(central);
}
