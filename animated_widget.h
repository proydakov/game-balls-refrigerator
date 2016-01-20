#ifndef ANIMATED_WIDGET_H
#define ANIMATED_WIDGET_H

#include <QWidget>

class AnimatedWidget : public QWidget
{
    Q_OBJECT

public:
    AnimatedWidget(QWidget* parent = 0);
    ~AnimatedWidget();

    void setActive(bool state);
    bool isActive() const;

public slots:
    virtual void animate() = 0;

private:
    bool m_active;
};

#endif // ANIMATED_WIDGET_H
