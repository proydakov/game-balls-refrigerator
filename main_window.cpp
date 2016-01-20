#include <ctime>

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>

#include <QPainter>
#include <QPaintEvent>

#include <QDebug>

#include "main_window.h"
#include "grip_widget.h"
#include "lock_widget.h"
#include "start_widget.h"
#include "record_widget.h"
#include "game_controller.h"
#include "animation_controller.h"
#include "record_manager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_records.reset(new RecordManager);
    m_background = QBrush(QColor(192, 192, 192));

    m_buttonFont.setPointSize(60);
    m_buttonFont.setBold(true);

    setWindowTitle(tr("Game balls refrigerator"));
    setFixedSize(600, 750);

    const QPixmap pixmap( ":/res/images/icon.jpg" );
    setWindowIcon(QIcon(pixmap));

    create();
}

MainWindow::~MainWindow()
{
}

void MainWindow::start(size_t size)
{
    qDebug() << "start: " << size;

    srand(time(NULL));

    QWidget *central = new QWidget(this);
    QGridLayout *layout = new QGridLayout(central);

    const QPixmap pixmap( ":/res/images/grip.png" );

    GameController* gameController = new GameController(size, central);
    AnimationController* animationController = new AnimationController(central);

    for(size_t x = 0; x < size; x++) {
        LockWidget *lock = new LockWidget(x, central);
        layout->addWidget(lock, 0, x);
        gameController->addLock(lock);

        for(size_t y = 0; y < size; y++) {
            const int value = rand() % 2;
            const QPoint position(x, y);
            GripWidget *grip = new GripWidget(value, position, pixmap, central);
            layout->addWidget(grip, y + 1, x);
            gameController->addGrip(grip);
            animationController->addAnimatedWidget(grip);
            central->connect(grip, SIGNAL(stateChange(QPoint)), animationController, SLOT(stateChange()));
            central->connect(grip, SIGNAL(requireAnimate(QPoint)), animationController, SLOT(requireAnimate()));
            central->connect(grip, SIGNAL(finishAnimate()), animationController, SLOT(finishAnimate()));
        }
    }
    central->setLayout(layout);
    setCentralWidget(central);

    central->connect(animationController, SIGNAL(allAnimationsComplete()), gameController, SLOT(validate()));

    central->connect(gameController, SIGNAL(solve(qint64)), this, SLOT(solve(qint64)));
    gameController->start();
    gameController->validate();
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
    setCentralWidget(central);

    QVBoxLayout *centralLayout = new QVBoxLayout(central);
    central->setLayout(centralLayout);

    QWidget *control = new QWidget(central);

    QGridLayout *layout = new QGridLayout(control);

    const size_t min_size = 4;
    const size_t max_size = 10;
    const size_t size = max_size - min_size + 1;
    Q_ASSERT(size > 0);
    std::vector<QWidget*> items(size, nullptr);
    for(size_t i = 0; i < size; i++) {
        items[i] = new StartWidget(i + min_size, control);
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
    control->setLayout(layout);

    centralLayout->addWidget(control);

    QPushButton* button = new QPushButton(tr("Records"), central);
    button->setMinimumHeight(100);
    button->connect(button, SIGNAL(clicked(bool)), this, SLOT(records()));

    button->setFont(m_buttonFont);

    centralLayout->addWidget(button);
}

void MainWindow::records()
{
    qDebug() << "records";

    RecordWidget *widget = new RecordWidget(m_records.get(), m_buttonFont, this);
    setCentralWidget(widget);
    widget->connect(widget, SIGNAL(back()), this, SLOT(create()));
}

void MainWindow::solve(qint64 time)
{
    qDebug() << "solve time: " << time << " ms";

    m_records->trySetRecord(time);

    QWidget *central = new QWidget(this);

    QGridLayout *layout = new QGridLayout(central);
    QLabel* text = new QLabel(tr("Solve!\nTime: %1 sec").arg(time / 1000), central);
    text->setAlignment(Qt::AlignCenter);
    text->setFont(m_buttonFont);

    QPushButton *button = new QPushButton(tr("Сontinue"), central);
    button->setFont(m_buttonFont);
    button->connect(button, SIGNAL(clicked(bool)), this, SLOT(create()));

    layout->addWidget(text, 0, 0);
    layout->addWidget(button, 1, 0);

    central->setLayout(layout);

    setCentralWidget(central);
}
