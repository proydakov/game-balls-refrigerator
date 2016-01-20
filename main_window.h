#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

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
    void solve();

private:
    QBrush m_background;
};

#endif // MAIN_WINDOW_H
