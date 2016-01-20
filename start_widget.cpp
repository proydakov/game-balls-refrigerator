#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

#include "start_widget.h"

StartWidget::StartWidget(size_t size, QWidget* parent) :
    QWidget(parent),
    m_size(size),
    m_background(QColor(255, 255, 255)),
    m_textPen(Qt::red)
{
    m_textFont.setPixelSize(50);
}

StartWidget::~StartWidget()
{
    qDebug() << "~StartWidget: " << this;
}

void StartWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), m_background);
    painter.setPen(m_textPen);
    painter.setFont(m_textFont);
    QString text = QString("%1 x %2").arg(m_size).arg(m_size);
    painter.drawText(event->rect(), Qt::AlignCenter, text);
}

void StartWidget::mousePressEvent(QMouseEvent *event)
{
    emit select(m_size);
    QWidget::mousePressEvent(event);
}
