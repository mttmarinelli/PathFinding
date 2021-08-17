/********************************************************************************
** Form generated from reading UI file 'PathFindingWindowjGUANX.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef PATHFINDINGWINDOWJGUANX_H
#define PATHFINDINGWINDOWJGUANX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *cmbAlgorithm;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnStartPos;
    QPushButton *btnObstaclePos;
    QPushButton *btnEndPos;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnPlay;
    QPushButton *btnClear;
    QSpacerItem *horizontalSpacer_4;
    QGraphicsView *graphicsView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(953, 594);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        cmbAlgorithm = new QComboBox(centralwidget);
        cmbAlgorithm->addItem(QString());
        cmbAlgorithm->addItem(QString());
        cmbAlgorithm->addItem(QString());
        cmbAlgorithm->addItem(QString());
        cmbAlgorithm->setObjectName(QString::fromUtf8("cmbAlgorithm"));
        cmbAlgorithm->setLayoutDirection(Qt::RightToLeft);
        cmbAlgorithm->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_2->addWidget(cmbAlgorithm);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnStartPos = new QPushButton(centralwidget);
        btnStartPos->setObjectName(QString::fromUtf8("btnStartPos"));
        btnStartPos->setCheckable(true);
        btnStartPos->setAutoExclusive(false);
        btnStartPos->setFlat(false);

        horizontalLayout->addWidget(btnStartPos);

        btnObstaclePos = new QPushButton(centralwidget);
        btnObstaclePos->setObjectName(QString::fromUtf8("btnObstaclePos"));
        btnObstaclePos->setCheckable(true);
        btnObstaclePos->setAutoExclusive(false);
        btnObstaclePos->setFlat(false);

        horizontalLayout->addWidget(btnObstaclePos);

        btnEndPos = new QPushButton(centralwidget);
        btnEndPos->setObjectName(QString::fromUtf8("btnEndPos"));
        btnEndPos->setCheckable(true);
        btnEndPos->setAutoExclusive(false);
        btnEndPos->setFlat(false);

        horizontalLayout->addWidget(btnEndPos);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnPlay = new QPushButton(centralwidget);
        btnPlay->setObjectName(QString::fromUtf8("btnPlay"));

        horizontalLayout_3->addWidget(btnPlay);

        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));

        horizontalLayout_3->addWidget(btnClear);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setFrameShadow(QFrame::Sunken);
        graphicsView->setLineWidth(1);

        gridLayout->addWidget(graphicsView, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Algorithm", nullptr));
        cmbAlgorithm->setItemText(0, QCoreApplication::translate("MainWindow", "DFS", nullptr));
        cmbAlgorithm->setItemText(1, QCoreApplication::translate("MainWindow", "BFS", nullptr));
        cmbAlgorithm->setItemText(2, QCoreApplication::translate("MainWindow", "Dijkstra", nullptr));
        cmbAlgorithm->setItemText(3, QCoreApplication::translate("MainWindow", "A*", nullptr));

        cmbAlgorithm->setCurrentText(QCoreApplication::translate("MainWindow", "DFS", nullptr));
        btnStartPos->setText(QCoreApplication::translate("MainWindow", "Start Position", nullptr));
        btnObstaclePos->setText(QCoreApplication::translate("MainWindow", "Obstacle Position", nullptr));
        btnEndPos->setText(QCoreApplication::translate("MainWindow", "End Position", nullptr));
        btnPlay->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PATHFINDINGWINDOWJGUANX_H
