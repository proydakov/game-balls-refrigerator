#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <memory>

#include <QFont>
#include <QMainWindow>

class RecordManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void start(size_t size);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private slots:
    void create();
    void records();
    void solve(qint64 time);

private:
    std::unique_ptr<RecordManager> m_records;
    QBrush m_background;
    QFont  m_buttonFont;
};

#endif // MAIN_WINDOW_H
