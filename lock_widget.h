#ifndef LOCK_WIDGET_H
#define LOCK_WIDGET_H

#include <QPen>
#include <QFont>
#include <QWidget>

class LockWidget : public QWidget
{
    Q_OBJECT

public:
    LockWidget(size_t column, QWidget *parent = 0);
    ~LockWidget();

    size_t getColumn() const;

    void setState(bool s);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    bool  m_state;
    const size_t m_column;
    const QBrush m_backgroundLock;
    const QBrush m_backgroundUnlock;
    QPen  m_textPen;
    QFont m_textFont;
};

#endif // LOCK_WIDGET_H
