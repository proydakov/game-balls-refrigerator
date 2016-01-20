#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSizePolicy>

#include <QDebug>

#include <record_widget.h>
#include <record_manager.h>

RecordWidget::RecordWidget(RecordManager* manager,  const QFont& buttonFont, QWidget* parent) :
    QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    QWidget *central = new QWidget(this);
    QPushButton *button = new QPushButton(tr("Back"), this);
    button->setFont(buttonFont);

    layout->addWidget(central);
    layout->addWidget(button);

    connect(button, SIGNAL(clicked(bool)), this, SIGNAL(back()));

    QGridLayout *dataLayout = new QGridLayout(central);
    central->setLayout(dataLayout);

    QFont labelFont;
    labelFont.setPointSize(25);
    labelFont.setBold(true);

    QLabel *textDescr = new QLabel(tr("Place"), central);
    textDescr->setFont(labelFont);
    QLabel *timeDescr = new QLabel(tr("Time (msec)"), central);\
    timeDescr->setFont(labelFont);
    dataLayout->addWidget(textDescr, 0, 0);
    dataLayout->addWidget(timeDescr, 0, 1);

    auto records = manager->getRecords();
    size_t max_y = RecordManager::params::size;
    for(size_t y = 0; y < max_y; y++) {
        QLabel *text = new QLabel(QString("%1").arg(y + 1),central);
        text->setFont(labelFont);

        QString timeText;
        if(y < records.size()) {
            timeText = QString("%1").arg(records[y]);
        }

        QLabel *time = new QLabel(timeText, central);
        time->setFont(labelFont);

        const size_t widget_y = y + 1;
        dataLayout->addWidget(text, widget_y, 0);
        dataLayout->addWidget(time, widget_y, 1);
    }
}

RecordWidget::~RecordWidget()
{
    qDebug() << "~RecordWidget:" << this;
}
