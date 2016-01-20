#ifndef GRIP_WIDGET_H
#define GRIP_WIDGET_H

#include <QPen>
#include <QFont>
#include <animated_widget.h>

class GripWidget : public AnimatedWidget
{
    Q_OBJECT

public:
    GripWidget(bool state, const QPoint& position, const QPixmap& pixmap, QWidget *parent = 0);
    ~GripWidget();

    const QPoint& getPosition() const;

    void setState(bool state);
    bool getState() const;

public slots:
    void animate() Q_DECL_OVERRIDE;

signals:
    void stateChange(const QPoint &position);
    void requireAnimate(const QPoint &position);
    void finishAnimate();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    bool m_state;
    bool m_process;
    QBrush m_background;
    const QPixmap m_pixmap;
    const QPoint m_position;
    QPen  m_textPen;
    QFont m_textFont;
    int m_angle;
    int m_destAngle;
};

#endif // GRIP_WIDGET_H
