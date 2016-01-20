#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

#include <QTimer>
#include <QObject>

class GripWidget;

class AnimationController : public QObject
{
    Q_OBJECT

public:
    AnimationController(size_t size, QObject* parent = 0);
    ~AnimationController();

    void addGrip(GripWidget* item);

signals:
    void allAnimationsComplete();

public slots:
    void stateChange();
    void requireAnimate(const QPoint &position);
    void finishAnimate();

private:
    void tryFinishAnimations();
    size_t calcIndex(const QPoint &position);

private:
    size_t m_size;
    int    m_animate;
    QTimer m_timer;
    std::vector<GripWidget*> m_grips;
};

#endif // ANIMATION_CONTROLLER_H
