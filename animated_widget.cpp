#include "animated_widget.h"

AnimatedWidget::AnimatedWidget(QWidget* parent) :
    QWidget(parent),
    m_active(true)
{
}

AnimatedWidget::~AnimatedWidget()
{
}

void AnimatedWidget::setActive(bool state)
{
    m_active = state;
}

bool AnimatedWidget::isActive() const
{
    return m_active;
}
