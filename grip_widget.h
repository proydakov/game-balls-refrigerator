#ifndef GRIP_WIDGET_H
#define GRIP_WIDGET_H

#include <QPen>
#include <QFont>
#include <QWidget>

class GripWidget : public QWidget
{
    Q_OBJECT

public:
    GripWidget(const QPoint& position, const QPixmap& pixmap, QWidget *parent = 0);
    ~GripWidget();

    const QPoint& getPosition() const;

    void setState(bool state);
    bool getState() const;

signals:
    void stateChange(const QPoint &position);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    bool m_state;
    const QPixmap m_pixmap;
    const QPoint m_position;
    QPen  m_textPen;
    QFont m_textFont;
};

#endif // GRIP_WIDGET_H
