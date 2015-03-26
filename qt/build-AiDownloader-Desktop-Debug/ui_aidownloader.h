/********************************************************************************
** Form generated from reading UI file 'aidownloader.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AIDOWNLOADER_H
#define UI_AIDOWNLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AiDownloader
{
public:
    QAction *actionFile;
    QAction *actionRestore;
    QAction *actionExit;
    QAction *actionLog;
    QAction *actionAdd_New_Source;
    QAction *actionUpdate_Sources;
    QAction *actionAbout;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QListView *listView;
    QListView *right;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSources;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AiDownloader)
    {
        if (AiDownloader->objectName().isEmpty())
            AiDownloader->setObjectName(QStringLiteral("AiDownloader"));
        AiDownloader->resize(1303, 680);
        actionFile = new QAction(AiDownloader);
        actionFile->setObjectName(QStringLiteral("actionFile"));
        actionRestore = new QAction(AiDownloader);
        actionRestore->setObjectName(QStringLiteral("actionRestore"));
        actionExit = new QAction(AiDownloader);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionLog = new QAction(AiDownloader);
        actionLog->setObjectName(QStringLiteral("actionLog"));
        actionAdd_New_Source = new QAction(AiDownloader);
        actionAdd_New_Source->setObjectName(QStringLiteral("actionAdd_New_Source"));
        actionUpdate_Sources = new QAction(AiDownloader);
        actionUpdate_Sources->setObjectName(QStringLiteral("actionUpdate_Sources"));
        actionAbout = new QAction(AiDownloader);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(AiDownloader);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8("../../res/logosmall.png")));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout->addWidget(listView, 3, 0, 1, 1);

        right = new QListView(centralWidget);
        right->setObjectName(QStringLiteral("right"));

        gridLayout->addWidget(right, 3, 1, 1, 1);

        AiDownloader->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AiDownloader);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1303, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSources = new QMenu(menuBar);
        menuSources->setObjectName(QStringLiteral("menuSources"));
        AiDownloader->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AiDownloader);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AiDownloader->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AiDownloader);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AiDownloader->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSources->menuAction());
        menuFile->addAction(actionFile);
        menuFile->addSeparator();
        menuFile->addAction(actionRestore);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuSources->addAction(actionAdd_New_Source);
        menuSources->addAction(actionUpdate_Sources);

        retranslateUi(AiDownloader);
        QObject::connect(actionExit, SIGNAL(triggered()), AiDownloader, SLOT(close()));
        QObject::connect(actionUpdate_Sources, SIGNAL(triggered()), AiDownloader, SLOT(updateMangaList()));

        QMetaObject::connectSlotsByName(AiDownloader);
    } // setupUi

    void retranslateUi(QMainWindow *AiDownloader)
    {
        AiDownloader->setWindowTitle(QApplication::translate("AiDownloader", "AiDownloader", 0));
        actionFile->setText(QApplication::translate("AiDownloader", "Backup", 0));
        actionRestore->setText(QApplication::translate("AiDownloader", "Restore", 0));
        actionExit->setText(QApplication::translate("AiDownloader", "Exit", 0));
        actionLog->setText(QApplication::translate("AiDownloader", "Log", 0));
        actionAdd_New_Source->setText(QApplication::translate("AiDownloader", "Add New Source", 0));
        actionUpdate_Sources->setText(QApplication::translate("AiDownloader", "Update Sources", 0));
        actionAbout->setText(QApplication::translate("AiDownloader", "About", 0));
        label->setText(QString());
        menuFile->setTitle(QApplication::translate("AiDownloader", "File", 0));
        menuSources->setTitle(QApplication::translate("AiDownloader", "Sources", 0));
    } // retranslateUi

};

namespace Ui {
    class AiDownloader: public Ui_AiDownloader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AIDOWNLOADER_H
