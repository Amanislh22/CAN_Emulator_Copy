/********************************************************************************
** Form generated from reading UI file 'homewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEWINDOW_H
#define UI_HOMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *sidebarFrame;
    QVBoxLayout *verticalLayout;
    QPushButton *toggleSidebarButton;
    QPushButton *navHomeButton;
    QPushButton *navMonitorButton;
    QPushButton *navTransmitButton;
    QPushButton *navDashboardButton;
    QPushButton *navSettingsButton;
    QPushButton *navHelpButton;
    QLabel *statusLabel;
    QStackedWidget *stackedWidget;
    QWidget *homePage;
    QLabel *titleWelcome;
    QLabel *subtitleWelcome;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *connectButton;
    QPushButton *disconnectButton;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *navMonitorButton_2;
    QPushButton *navTransmitButton_2;
    QPushButton *navDashboardButton_2;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *labelComPort;
    QComboBox *labelBaud;
    QWidget *monitorPage;
    QWidget *transmitPage;
    QWidget *dashboardPage;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HomeWindow)
    {
        if (HomeWindow->objectName().isEmpty())
            HomeWindow->setObjectName(QString::fromUtf8("HomeWindow"));
        HomeWindow->resize(1425, 618);
        centralwidget = new QWidget(HomeWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        sidebarFrame = new QFrame(centralwidget);
        sidebarFrame->setObjectName(QString::fromUtf8("sidebarFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sidebarFrame->sizePolicy().hasHeightForWidth());
        sidebarFrame->setSizePolicy(sizePolicy);
        sidebarFrame->setFrameShape(QFrame::Shape::StyledPanel);
        sidebarFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(sidebarFrame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toggleSidebarButton = new QPushButton(sidebarFrame);
        toggleSidebarButton->setObjectName(QString::fromUtf8("toggleSidebarButton"));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        toggleSidebarButton->setFont(font);

        verticalLayout->addWidget(toggleSidebarButton);

        navHomeButton = new QPushButton(sidebarFrame);
        navHomeButton->setObjectName(QString::fromUtf8("navHomeButton"));

        verticalLayout->addWidget(navHomeButton);

        navMonitorButton = new QPushButton(sidebarFrame);
        navMonitorButton->setObjectName(QString::fromUtf8("navMonitorButton"));

        verticalLayout->addWidget(navMonitorButton);

        navTransmitButton = new QPushButton(sidebarFrame);
        navTransmitButton->setObjectName(QString::fromUtf8("navTransmitButton"));

        verticalLayout->addWidget(navTransmitButton);

        navDashboardButton = new QPushButton(sidebarFrame);
        navDashboardButton->setObjectName(QString::fromUtf8("navDashboardButton"));

        verticalLayout->addWidget(navDashboardButton);

        navSettingsButton = new QPushButton(sidebarFrame);
        navSettingsButton->setObjectName(QString::fromUtf8("navSettingsButton"));

        verticalLayout->addWidget(navSettingsButton);

        navHelpButton = new QPushButton(sidebarFrame);
        navHelpButton->setObjectName(QString::fromUtf8("navHelpButton"));
        navHelpButton->setFont(font);

        verticalLayout->addWidget(navHelpButton);

        statusLabel = new QLabel(sidebarFrame);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statusLabel->sizePolicy().hasHeightForWidth());
        statusLabel->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setBold(true);
        statusLabel->setFont(font1);

        verticalLayout->addWidget(statusLabel);


        horizontalLayout->addWidget(sidebarFrame);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        homePage = new QWidget();
        homePage->setObjectName(QString::fromUtf8("homePage"));
        titleWelcome = new QLabel(homePage);
        titleWelcome->setObjectName(QString::fromUtf8("titleWelcome"));
        titleWelcome->setGeometry(QRect(180, 60, 501, 91));
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        titleWelcome->setFont(font2);
        titleWelcome->setAlignment(Qt::AlignmentFlag::AlignCenter);
        subtitleWelcome = new QLabel(homePage);
        subtitleWelcome->setObjectName(QString::fromUtf8("subtitleWelcome"));
        subtitleWelcome->setGeometry(QRect(230, 140, 431, 61));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        subtitleWelcome->setFont(font3);
        subtitleWelcome->setAlignment(Qt::AlignmentFlag::AlignCenter);
        layoutWidget = new QWidget(homePage);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(560, 250, 92, 67));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        connectButton = new QPushButton(layoutWidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        verticalLayout_2->addWidget(connectButton);

        disconnectButton = new QPushButton(layoutWidget);
        disconnectButton->setObjectName(QString::fromUtf8("disconnectButton"));

        verticalLayout_2->addWidget(disconnectButton);

        layoutWidget1 = new QWidget(homePage);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(210, 470, 481, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        navMonitorButton_2 = new QPushButton(layoutWidget1);
        navMonitorButton_2->setObjectName(QString::fromUtf8("navMonitorButton_2"));

        horizontalLayout_2->addWidget(navMonitorButton_2);

        navTransmitButton_2 = new QPushButton(layoutWidget1);
        navTransmitButton_2->setObjectName(QString::fromUtf8("navTransmitButton_2"));

        horizontalLayout_2->addWidget(navTransmitButton_2);

        navDashboardButton_2 = new QPushButton(layoutWidget1);
        navDashboardButton_2->setObjectName(QString::fromUtf8("navDashboardButton_2"));

        horizontalLayout_2->addWidget(navDashboardButton_2);

        layoutWidget2 = new QWidget(homePage);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(240, 280, 291, 30));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelComPort = new QComboBox(layoutWidget2);
        labelComPort->setObjectName(QString::fromUtf8("labelComPort"));

        horizontalLayout_3->addWidget(labelComPort);

        labelBaud = new QComboBox(layoutWidget2);
        labelBaud->setObjectName(QString::fromUtf8("labelBaud"));
        labelBaud->setEditable(false);

        horizontalLayout_3->addWidget(labelBaud);

        stackedWidget->addWidget(homePage);
        monitorPage = new QWidget();
        monitorPage->setObjectName(QString::fromUtf8("monitorPage"));
        stackedWidget->addWidget(monitorPage);
        transmitPage = new QWidget();
        transmitPage->setObjectName(QString::fromUtf8("transmitPage"));
        stackedWidget->addWidget(transmitPage);
        dashboardPage = new QWidget();
        dashboardPage->setObjectName(QString::fromUtf8("dashboardPage"));
        stackedWidget->addWidget(dashboardPage);

        horizontalLayout->addWidget(stackedWidget);

        HomeWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(HomeWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        HomeWindow->setStatusBar(statusbar);

        retranslateUi(HomeWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(HomeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HomeWindow)
    {
        HomeWindow->setWindowTitle(QCoreApplication::translate("HomeWindow", "HomeWindow", nullptr));
        toggleSidebarButton->setText(QString());
        navHomeButton->setText(QCoreApplication::translate("HomeWindow", "Home", nullptr));
        navMonitorButton->setText(QCoreApplication::translate("HomeWindow", "Monitor", nullptr));
        navTransmitButton->setText(QCoreApplication::translate("HomeWindow", "Transmit", nullptr));
        navDashboardButton->setText(QCoreApplication::translate("HomeWindow", "Dashboard", nullptr));
        navSettingsButton->setText(QCoreApplication::translate("HomeWindow", "Settings", nullptr));
        navHelpButton->setText(QCoreApplication::translate("HomeWindow", "Help", nullptr));
        statusLabel->setText(QCoreApplication::translate("HomeWindow", "Status", nullptr));
        titleWelcome->setText(QCoreApplication::translate("HomeWindow", "Welcome to CAN Emulator Tool", nullptr));
        subtitleWelcome->setText(QCoreApplication::translate("HomeWindow", "Monitor \342\200\242 Send \342\200\242 Visualize CAN frames", nullptr));
        connectButton->setText(QCoreApplication::translate("HomeWindow", "Connect", nullptr));
        disconnectButton->setText(QCoreApplication::translate("HomeWindow", "Disconnect", nullptr));
        navMonitorButton_2->setText(QCoreApplication::translate("HomeWindow", "Start monitor", nullptr));
        navTransmitButton_2->setText(QCoreApplication::translate("HomeWindow", "Send test frame", nullptr));
        navDashboardButton_2->setText(QCoreApplication::translate("HomeWindow", "View dashboard", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomeWindow: public Ui_HomeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEWINDOW_H
