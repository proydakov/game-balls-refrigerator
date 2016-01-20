#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

#include "lock_widget.h"

LockWidget::LockWidget(size_t column, QWidget *parent) :
    QWidget(parent),
    m_state(false),
    m_column(column),
    m_backgroundLock(QColor(255, 0, 0)),
    m_backgroundUnlock(QColor(0, 255, 0)),
    m_textPen(Qt::blue)
{
    m_textFont.setPixelSize(50);
    setFixedSize(100, 100);
}

LockWidget::~LockWidget()
{
    qDebug() << "~LockWidget: " << this;
}

size_t LockWidget::getColumn() const
{
    return m_column;
}

void LockWidget::setState(bool s)
{
    m_state = s;
    update();
}

void LockWidget::paintEvent(QPaintEvent *event)
{
    const QBrush* brush;
    if(m_state) {
        brush = &m_backgroundUnlock;
    }
    else {
        brush = &m_backgroundLock;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), *brush);
    painter.setPen(m_textPen);
    painter.setFont(m_textFont);
    QString text = QString("%1").arg(m_column);
    painter.drawText(event->rect(), Qt::AlignCenter, text);

}
