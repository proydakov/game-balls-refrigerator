#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <vector>

#include <QObject>

class GripWidget;
class LockWidget;

class GameController : public QObject
{
    Q_OBJECT

public:
    GameController(size_t size, QObject* parent);
    ~GameController();

    void addGrip(GripWidget* item);
    void addLock(LockWidget* item);

    void start();

signals:
    void solve(qint64);

public slots:
    void stateChange(const QPoint &position);
    void validate();

private slots:
    void swap(const QPoint &position);

private:
    void trySwap(const QPoint &position, const QPoint &test_position);
    size_t calcIndex(const QPoint &position);

private:
    const size_t m_size;
    std::vector<GripWidget*> m_grips;
    std::vector<LockWidget*> m_locks;
    qint64 m_start;
};

#endif // GAME_CONTROLLER_H
