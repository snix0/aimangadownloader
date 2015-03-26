#include <fstream>
#include <vector>
#include <string>
#include "../../src/AiDownloader/curlpprequest.cpp"
#include "aidownloader.h"
#include "ui_aidownloader.h"
#include <QStringListModel>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>

AiDownloader::AiDownloader(QWidget *parent) :
    ui(new Ui::AiDownloader)
{
    ui->setupUi(this);


    std::vector<QString> vec;
//    std::ifstream infile("mangalist");
    QFile input_file("mangalist");
    if (input_file.open(QIODevice::ReadOnly)) {
        QTextStream in(&input_file);
        while (!in.atEnd())
            vec.push_back(in.readLine().split("|").at(0));
        input_file.close();
    } else {
        CurlRequest curl = CurlRequest();
        std::vector<QString> manga_data = curl.requestList();
        for (auto i = manga_data.begin(); i != manga_data.end(); ++i)
            vec.push_back(i->split("|").at(0));
    }

    ui->listView->setModel(new QStringListModel(QList<QString>::fromVector(QVector<QString>::fromStdVector(vec))));
}

AiDownloader::~AiDownloader()
{
    delete ui;
}
