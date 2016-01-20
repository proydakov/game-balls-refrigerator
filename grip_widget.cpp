#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

#include "grip_widget.h"

GripWidget::GripWidget(const QPoint& position, const QPixmap& pixmap, QWidget* parent) :
    QWidget(parent),
    m_state(false),
    m_pixmap(pixmap),
    m_position(position),
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
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(m_textPen);
    painter.setFont(m_textFont);

    auto drawRect = event->rect();

    painter.save();
    painter.translate(drawRect.width() / 2, drawRect.height() / 2);
    if(!m_state) {
        painter.rotate(90);
    }
    QRect target( -drawRect.width() / 2, -drawRect.height() / 2, drawRect.width(), drawRect.height());
    painter.drawPixmap(target, m_pixmap, m_pixmap.rect());

    painter.restore();
    QString text = QString("%1,%2").arg(m_position.x()).arg(m_position.y());
    painter.drawText(event->rect(), Qt::AlignCenter, text);
}

void GripWidget::mousePressEvent( QMouseEvent * event )
{
    setState(!m_state);
    emit stateChange(m_position);
    QWidget::mousePressEvent(event);
}
