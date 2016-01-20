#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

#include <QTimer>
#include <QObject>

class AnimatedWidget;

class AnimationController : public QObject
{
    Q_OBJECT

public:
    AnimationController(QObject* parent = 0);
    ~AnimationController();

    void addAnimatedWidget(AnimatedWidget* widget);

signals:
    void allAnimationsComplete();

public slots:
    void stateChange();
    void requireAnimate();
    void finishAnimate();

private:
    void tryFinishAnimations();

private:
    int    m_animate;
    QTimer m_timer;
    std::vector<AnimatedWidget*> m_widgets;
};

#endif // ANIMATION_CONTROLLER_H
