#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QTimer>
#include <QTime>
#include <QVector>

struct CANFrame {
    QString timestamp;
    QString canId;
    QString data;
    int dlc;
    QString direction; // "TX" or "RX"
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void toggleConnection();
    void sendFrame();
    void clearFrames();
    void updateFilter();
    void simulateCANTraffic();
    void updateTable();

private:
    void setupUI();
    void setDarkTheme();
    QWidget* createStatusBar();
    QGroupBox* createTransmitPanel();
    QGroupBox* createMonitorPanel();
    void updateStatus();

    // UI Components
    QLabel *statusIndicator;
    QLabel *statusLabel;
    QLabel *busLoadValue;
    QLabel *errorValue;
    QPushButton *connectBtn;
    QPushButton *sendBtn;
    QLineEdit *canIdInput;
    QTextEdit *canDataInput;
    QCheckBox *filterCheckbox;
    QLineEdit *filterInput;
    QTableWidget *table;
    QGroupBox *monitorGroup;
    QTimer *timer;

    // Data
    bool isConnected;
    QVector<CANFrame> canFrames;
    double busLoad;
    int errorCount;
};

#endif // MAINWINDOW_H
