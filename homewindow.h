#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include "mainwindow.h"
#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class HomeWindow; }
QT_END_NAMESPACE

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow();

private slots:
    void toggleSidebar();      // Toggle sidebar visibility
    void refreshComPorts();    // Populate COM port dropdown
    void connectSerial();      // Connect to selected serial port
    void disconnectSerial();   // Disconnect serial port

    // Test slots
    void testConnect();
    void testDisconnect();

    // Declare the functions to show pages
    void showHomePage();
    void showMonitorPage();
    void showDashboardPage();
    void showSettingsPage();
    void showHelpPage();
    void showTransmitPage();

private:
    Ui::HomeWindow *ui;
    bool sidebarVisible;       // Sidebar state
    QSerialPort *serial;       // Serial port object
    MainWindow* monitorPage = nullptr;
};

#endif // HOMEWINDOW_H
