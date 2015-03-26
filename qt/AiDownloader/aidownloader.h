#ifndef AIDOWNLOADER_H
#define AIDOWNLOADER_H

#include <vector>
#include <QString>
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
    std::vector<QString>* active_list;

public slots:
    void updateMangaList();
    void on_listView_clicked();
};

#endif // AIDOWNLOADER_H
