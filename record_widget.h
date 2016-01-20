#ifndef RECORD_WIDGET_H
#define RECORD_WIDGET_H

#include <QFont>
#include <QWidget>

class RecordManager;

class RecordWidget : public QWidget
{
    Q_OBJECT

public:
    RecordWidget(RecordManager* manager, const QFont& buttonFont, QWidget* parent);
    ~RecordWidget();

signals:
    void back();
};

#endif // RECORD_WIDGET_H
