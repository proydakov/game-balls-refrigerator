#include "animation_controller.h"

#include "QDebug"

#include "grip_widget.h"

AnimationController::AnimationController(size_t size, QObject* parent) :
    QObject(parent),
    m_size(size),
    m_animate(0)
{
    m_grips.resize(m_size * m_size, nullptr);
}

AnimationController::~AnimationController()
{
    qDebug() << "~AnimationController: " << this;
}

void AnimationController::addGrip(GripWidget* item)
{
    const size_t index = calcIndex(item->getPosition());
    m_grips[index] = item;
}

void AnimationController::stateChange()
{
    for(size_t i = 0; i < m_grips.size(); i++) {
        m_grips[i]->setProcess(false);
    }
    m_timer.start(17);
}

void AnimationController::requireAnimate(const QPoint &position)
{
    qDebug() << "requireAnimate: " << sender();

    const size_t index = calcIndex(position);
    auto item = m_grips[index];
    connect(&m_timer, SIGNAL(timeout()), item, SLOT(animate()));
    m_animate++;
}

void AnimationController::finishAnimate()
{
    qDebug() << "finishAnimate: " << sender();

    auto item = qobject_cast<GripWidget*>(sender());
    disconnect(&m_timer, SIGNAL(timeout()), item, SLOT(animate()));
    m_animate--;
    tryFinishAnimations();
}

void AnimationController::tryFinishAnimations()
{
    if(0 == m_animate) {
        emit allAnimationsComplete();
        m_timer.stop();
        for(size_t i = 0; i < m_grips.size(); i++) {
            m_grips[i]->setProcess(true);
        }
    }
}

size_t AnimationController::calcIndex(const QPoint &position)
{
    size_t index = position.x() + m_size * position.y();
    return index;
}
