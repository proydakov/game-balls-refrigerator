#include <QApplication>
#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

#if defined( Q_OS_ANDROID ) || defined( Q_OS_IOS )
    w.showFullScreen();
#else
    w.setFixedSize(600, 750);
    w.show();
#endif

    return a.exec();
}
