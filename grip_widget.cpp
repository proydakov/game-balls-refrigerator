#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

#include "grip_widget.h"

GripWidget::GripWidget(const QPoint& position, QWidget* parent) :
    QWidget(parent),
    m_state(false),
    m_position(position),
    m_backgroundWhite(QColor(255, 255, 255)),
    m_backgroundBlack(QColor(0, 0, 0)),
    m_textPen(Qt::red)
{
    m_textFont.setPixelSize(30);
}

GripWidget::~GripWidget()
{
    qDebug() << "~GripWidget: " << this;
}

const QPoint& GripWidget::getPosition() const
{
    return m_position;
}

void GripWidget::setState( bool state )
{
    m_state = state;
    update();
}

bool GripWidget::getState( ) const
{
    return m_state;
}

void GripWidget::paintEvent(QPaintEvent *event)
{
    const QBrush* brush;
    if(m_state) {
        brush = &m_backgroundWhite;
    }
    else {
        brush = &m_backgroundBlack;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), *brush);
    painter.setPen(m_textPen);
    painter.setFont(m_textFont);
    QString text = QString("%1,%2").arg(m_position.x()).arg(m_position.y());
    painter.drawText(event->rect(), Qt::AlignCenter, text);
}

void GripWidget::mousePressEvent( QMouseEvent * event )
{
    setState(!m_state);
    emit stateChange(m_position);
    QWidget::mousePressEvent(event);
}
