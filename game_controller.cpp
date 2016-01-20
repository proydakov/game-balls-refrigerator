#include "grip_widget.h"
#include "lock_widget.h"
#include "game_controller.h"

#include <QDebug>

GameController::GameController(size_t size, QObject* parent) :
    QObject(parent),
    m_size(size)
{
    m_grips.resize(m_size * m_size, nullptr);
    m_locks.resize(m_size);
}

GameController::~GameController()
{
    qDebug() << "~GameController: " << this;
}

void GameController::addGrip(GripWidget* item)
{
    const size_t index = calcIndex(item->getPosition());
    m_grips[index] = item;
    connect(item, SIGNAL(stateChange(QPoint)), this, SLOT(stateChange(QPoint)));
}

void GameController::addLock(LockWidget *item)
{
    const size_t index = item->getColumn();
    m_locks[index] = item;
}

void GameController::stateChange(const QPoint &position)
{
    qDebug() << "GameController::stateChange " << position;

    swap(position);
    validate();
}

void GameController::validate()
{
    size_t solve_counter = 0;
    for(size_t i = 0; i < m_size; i++) {
        size_t counter = 0;
        for(size_t j = 0; j < m_size; j++) {
            const size_t index = i + j * m_size;
            counter += m_grips[index]->getState();
        }
        const bool open = (m_size == counter);
        m_locks[i]->setState(open);
        solve_counter += open;
        qDebug() << "lock " << i << " state: " << open;
    }
    if(m_size == solve_counter) {
        emit solve();
    }
}

void GameController::swap(const QPoint &position)
{
    for(size_t i = 0; i < m_size; i++) {
        const QPoint vertical(i, position.y());
        const QPoint horizontal(position.x(), i);
        trySwap(position, vertical);
        trySwap(position, horizontal);
    }
}

void GameController::trySwap(const QPoint &position, const QPoint &test_position)
{
    if(test_position != position) {
        const size_t index = calcIndex(test_position);
        const bool state = m_grips[index]->getState();
        m_grips[index]->setState( !state );
    }
}

size_t GameController::calcIndex(const QPoint &position)
{
    size_t index = position.x() + m_size * position.y();
    return index;
}
