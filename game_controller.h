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
    GameController(int size);
    ~GameController();

    void addGrip(GripWidget* item);
    void addLock(LockWidget* item);

signals:
    void solve();

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
};

#endif // GAME_CONTROLLER_H
