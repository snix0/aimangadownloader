#ifndef AIDOWNLOADER_H
#define AIDOWNLOADER_H

#include <QMainWindow>

namespace Ui {
class AiDownloader;
}

class AiDownloader : public QMainWindow
{
    Q_OBJECT

public:
    explicit AiDownloader(QWidget *parent = 0);
    ~AiDownloader();

private:
    Ui::AiDownloader *ui;
};

#endif // AIDOWNLOADER_H
