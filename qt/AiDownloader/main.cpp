#include "aidownloader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AiDownloader w;
    w.show();

    return a.exec();
}
