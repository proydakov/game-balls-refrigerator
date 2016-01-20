#ifndef START_WIDGET_H
#define START_WIDGET_H

#include <QPen>
#include <QFont>
#include <QWidget>

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    StartWidget(size_t size, QWidget* parent);
    ~StartWidget();

signals:
    void select(size_t);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    const size_t m_size;
    const QBrush m_background;
    QPen  m_textPen;
    QFont m_textFont;
};

#endif // START_WIDGET_H
