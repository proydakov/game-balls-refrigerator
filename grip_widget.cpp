#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

#include <QDebug>

#include "grip_widget.h"

GripWidget::GripWidget(bool state, const QPoint& position, const QPixmap& pixmap, QWidget* parent) :
    AnimatedWidget(parent),
    m_state(state),
    m_angle(0),
    m_destAngle(0),
    m_background(QColor(160, 160, 160)),
    m_pixmap(pixmap),
    m_position(position),
    m_textPen(Qt::red)
{
    if(!m_state) {
        m_angle = 90;
        m_destAngle = 90;
    }
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
    m_destAngle += 90;
    emit requireAnimate(m_position);
}

bool GripWidget::getState( ) const
{
    return m_state;
}

void GripWidget::animate()
{
    //qDebug() <<"update: " << this << "current: " << m_angle << "dest: " << m_destAngle;

    if(m_angle < m_destAngle) {
        m_angle += 5;
    }
    else {
        if(m_angle >= 360) {
            m_angle = m_angle % 360;
            m_destAngle = m_angle % 360;
        }
        emit finishAnimate();
    }
    update();
}

void GripWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(m_textPen);
    painter.setFont(m_textFont);

    auto drawRect = event->rect();

    painter.fillRect(drawRect, m_background);

    painter.save();
    painter.translate(drawRect.width() / 2, drawRect.height() / 2);
    painter.rotate(m_angle);
    QRect target( -drawRect.width() / 2, -drawRect.height() / 2, drawRect.width(), drawRect.height());
    painter.drawPixmap(target, m_pixmap, m_pixmap.rect());

    painter.restore();
    QString text = QString("%1,%2").arg(m_position.x()).arg(m_position.y());
    painter.drawText(event->rect(), Qt::AlignCenter, text);
}

void GripWidget::mousePressEvent( QMouseEvent * event )
{
    if(isActive()) {
        setState(!m_state);
        emit stateChange(m_position);
    }
    QWidget::mousePressEvent(event);
}
