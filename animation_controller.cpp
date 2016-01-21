#include "animation_controller.h"

#include "QDebug"

#include "animated_widget.h"

AnimationController::AnimationController(QObject* parent) :
    QObject(parent),
    m_animate(0)
{
}

AnimationController::~AnimationController()
{
    qDebug() << "~AnimationController: " << this;
}

void AnimationController::addAnimatedWidget(AnimatedWidget* widget)
{
    m_widgets.push_back(widget);
}

void AnimationController::stateChange()
{
    for(size_t i = 0; i < m_widgets.size(); i++) {
        m_widgets[i]->setActive(false);
    }
    m_timer.start(50);
}

void AnimationController::requireAnimate()
{
    qDebug() << "requireAnimate: " << sender();

    auto item = qobject_cast<AnimatedWidget*>(sender());
    Q_ASSERT(item);

    connect(&m_timer, SIGNAL(timeout()), item, SLOT(animate()));
    m_animate++;
}

void AnimationController::finishAnimate()
{
    qDebug() << "finishAnimate: " << sender();

    auto item = qobject_cast<AnimatedWidget*>(sender());
    Q_ASSERT(item);

    disconnect(&m_timer, SIGNAL(timeout()), item, SLOT(animate()));
    m_animate--;
    tryFinishAnimations();
}

void AnimationController::tryFinishAnimations()
{
    if(0 == m_animate) {
        emit allAnimationsComplete();
        m_timer.stop();
        for(size_t i = 0; i < m_widgets.size(); i++) {
            m_widgets[i]->setActive(true);
        }
    }
}
