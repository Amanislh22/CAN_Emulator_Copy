#include "homewindow.h";
#include "./ui_homewindow.h";
#include "mainwindow.h";

#include <QPropertyAnimation>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>

HomeWindow::HomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
    , sidebarVisible(true)
    , serial(new QSerialPort(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    resize(1000, 700);

    // ------------------------------
    // Sidebar setup
    // ------------------------------
    ui->sidebarFrame->setMinimumWidth(50);
    ui->sidebarFrame->setMaximumWidth(200);
    ui->sidebarFrame->setFixedWidth(200); // start expanded
    ui->toggleSidebarButton->setText("◀");
    connect(ui->toggleSidebarButton, &QPushButton::clicked, this, &HomeWindow::toggleSidebar);

    // ------------------------------
    // Populate COM port dropdown
    // ------------------------------
    refreshComPorts();

    // Populate baud rates with placeholders
    ui->labelBaud->clear();
    ui->labelBaud->addItem("Select Baud Rate"); // Add placeholder
    ui->labelBaud->setItemData(0, true, Qt::UserRole - 1); // Mark as non-selectable
    ui->labelBaud->addItems({"9600", "115200", "500000"});
    ui->labelBaud->setCurrentIndex(0); // Set placeholder as selected

    // ------------------------------
    // Connect Buttons for navigation
    // ------------------------------
    connect(ui->navHomeButton, &QPushButton::clicked, this, &HomeWindow::showHomePage);
    connect(ui->navMonitorButton, &QPushButton::clicked, this, &HomeWindow::showMonitorPage);
    connect(ui->navTransmitButton, &QPushButton::clicked, this, &HomeWindow::showTransmitPage);
    connect(ui->navDashboardButton, &QPushButton::clicked, this, &HomeWindow::showDashboardPage);
    connect(ui->navSettingsButton, &QPushButton::clicked, this, &HomeWindow::showSettingsPage);
    connect(ui->navHelpButton, &QPushButton::clicked, this, &HomeWindow::showHelpPage);
    connect(ui->navMonitorButton_2, &QPushButton::clicked, this, &HomeWindow::showMonitorPage);
    connect(ui->navTransmitButton_2, &QPushButton::clicked, this, &HomeWindow::showTransmitPage);
    connect(ui->navDashboardButton_2, &QPushButton::clicked, this, &HomeWindow::showDashboardPage);

    // ------------------------------
    // Connect/Disconnect buttons
    // ------------------------------
    // connect(ui->connectButton, &QPushButton::clicked, this, &HomeWindow::connectSerial);
    // connect(ui->disconnectButton, &QPushButton::clicked, this, &HomeWindow::disconnectSerial);

    // Test buttons (for design)
    connect(ui->connectButton, &QPushButton::clicked, this, &HomeWindow::testConnect);
    connect(ui->disconnectButton, &QPushButton::clicked, this, &HomeWindow::testDisconnect);

    // Initially disable disconnect button
    ui->disconnectButton->setEnabled(false);

    // ------------------------------
    // Initialize status label
    // ------------------------------
    ui->statusLabel->setText("⚪ Status: Idle");
    ui->statusLabel->setStyleSheet("color: gray; font-weight: bold; font-size: 14px;");
}

HomeWindow::~HomeWindow()
{
    if (serial->isOpen())
        serial->close();
    delete ui;
}

// ------------------------------
// Toggle sidebar
// ------------------------------
void HomeWindow::toggleSidebar()
{
    int expandedWidth = 200;
    int collapsedWidth = 50;

    // Animate maximumWidth
    QPropertyAnimation *animation = new QPropertyAnimation(ui->sidebarFrame, "maximumWidth");
    animation->setDuration(300);
    animation->setStartValue(ui->sidebarFrame->width());
    animation->setEndValue(sidebarVisible ? collapsedWidth : expandedWidth);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    // Animate minimumWidth for smooth layout
    QPropertyAnimation *animationMin = new QPropertyAnimation(ui->sidebarFrame, "minimumWidth");
    animationMin->setDuration(300);
    animationMin->setStartValue(ui->sidebarFrame->width());
    animationMin->setEndValue(sidebarVisible ? collapsedWidth : expandedWidth);
    animationMin->start(QAbstractAnimation::DeleteWhenStopped);

    // Hide or show sidebar buttons (except toggle)
    QList<QPushButton*> buttons = ui->sidebarFrame->findChildren<QPushButton*>();
    for (QPushButton* btn : buttons) {
        if (btn != ui->toggleSidebarButton)
            btn->setVisible(!sidebarVisible);
    }

    // Hide or show the status label as well
    ui->statusLabel->setVisible(!sidebarVisible);

    // Update toggle arrow
    ui->toggleSidebarButton->setText(sidebarVisible ? "▶" : "◀");

    sidebarVisible = !sidebarVisible;
}

// ------------------------------
// Refresh COM ports
// ------------------------------
void HomeWindow::refreshComPorts()
{
    ui->labelComPort->clear();

    // Add a placeholder for "Select COM Port"
    ui->labelComPort->addItem("Select COM Port");
    ui->labelComPort->setItemData(0, true, Qt::UserRole - 1); // Mark as non-selectable

    const auto ports = QSerialPortInfo::availablePorts();
    if (ports.isEmpty()) {
        ui->labelComPort->addItem("No COM ports detected");
        ui->labelComPort->setItemData(ui->labelComPort->count() - 1, true, Qt::UserRole - 1); // Mark as non-selectable
    } else {
        // Add the available COM ports
        for (const auto &port : ports)
            ui->labelComPort->addItem(port.portName(), port.description());
    }

    // Set the placeholder as the selected item initially
    ui->labelComPort->setCurrentIndex(0);
}

// ------------------------------
// Connect serial
// ------------------------------
void HomeWindow::connectSerial()
{
    QString portName = ui->labelComPort->currentText();
    if (portName == "No COM ports detected") return;

    serial->setPortName(portName);
    serial->setBaudRate(ui->labelBaud->currentText().toInt());
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        // Update status bar
        statusBar()->setStyleSheet("color: green;");
        statusBar()->showMessage("Connected to " + portName);

        // Update label
        ui->statusLabel->setText("🟢 Status: Connected");
        ui->statusLabel->setStyleSheet("color: #82C0E9; font-weight: bold; font-size: 14px;");

        // Enable/disable buttons
        ui->connectButton->setEnabled(false);
        ui->disconnectButton->setEnabled(true);
        ui->disconnectButton->setStyleSheet("");
    } else {
        statusBar()->setStyleSheet("color: red;");
        statusBar()->showMessage("Connection Failed: " + serial->errorString());
        QMessageBox::critical(this, "Connection Failed", serial->errorString());

        ui->statusLabel->setText("🔴 Status: Error");
        ui->statusLabel->setStyleSheet("color: red; font-weight: bold; font-size: 14px;");
    }
}

// ------------------------------
// Disconnect serial
// ------------------------------
void HomeWindow::disconnectSerial()
{
    if (serial->isOpen()) {
        QString portName = serial->portName();
        serial->close();

        // Update status bar
        statusBar()->setStyleSheet("color: red;");
        statusBar()->showMessage("Disconnected from " + portName);

        // Update label
        ui->statusLabel->setText("🔴 Status: Disconnected");
        ui->statusLabel->setStyleSheet("color: red; font-weight: bold; font-size: 14px;");

        // Enable/disable buttons
        ui->connectButton->setEnabled(true);
        ui->disconnectButton->setEnabled(false);
        ui->disconnectButton->setStyleSheet("background-color: #cccccc; color: #666666;");
    }
}

// ------------------------------
// Test connect/disconnect (no real port)
// ------------------------------
void HomeWindow::testConnect()
{
    statusBar()->setStyleSheet("color: green;");
    statusBar()->showMessage("Connected to FAKE_PORT", 5000);
    ui->connectButton->setEnabled(false);
    ui->disconnectButton->setEnabled(true);
    ui->disconnectButton->setStyleSheet("");

    // Update status label
    ui->statusLabel->setText("🔵 Status: Connected");
    ui->statusLabel->setStyleSheet("color: #82C0E9; font-weight: bold; font-size: 14px;");
}

void HomeWindow::testDisconnect()
{
    statusBar()->setStyleSheet("color: red;");
    statusBar()->showMessage("Disconnected from FAKE_PORT", 5000);
    ui->connectButton->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
    ui->disconnectButton->setStyleSheet("background-color: #cccccc; color: #666666;");

    // Update status label
    ui->statusLabel->setText("🔴 Status: Disconnected");
    ui->statusLabel->setStyleSheet("color: #e57373; font-weight: bold; font-size: 14px;");
}

// ------------------------------
// Show Home Page
// ------------------------------
void HomeWindow::showHomePage()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void HomeWindow::showTransmitPage() {
    // Logic to switch to the Transmit page
    ui->stackedWidget->setCurrentIndex(2);  // For example, if page 2 is the Transmit page
}

// ------------------------------
// Show Monitor Page
// ------------------------------
void HomeWindow::showMonitorPage()
{
    if (!monitorPage) {
        monitorPage = new MainWindow(this);
        ui->stackedWidget->addWidget(monitorPage);
    }
    ui->stackedWidget->setCurrentWidget(monitorPage);
}


// ------------------------------
// Show Dashboard Page
// ------------------------------
void HomeWindow::showDashboardPage()
{
    ui->stackedWidget->setCurrentIndex(2);
}

// ------------------------------
// Show Settings Page
// ------------------------------
void HomeWindow::showSettingsPage()
{
    ui->stackedWidget->setCurrentIndex(3);
}

// ------------------------------
// Show Help Page
// ------------------------------
void HomeWindow::showHelpPage()
{
    ui->stackedWidget->setCurrentIndex(4);
}
