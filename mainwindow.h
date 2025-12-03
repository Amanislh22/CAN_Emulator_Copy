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
#include <QComboBox>

#include <QSerialPort>
#include <QSerialPortInfo>

class QSerialPort;

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
    explicit MainWindow(QWidget* parent = nullptr, QSerialPort* serialPort = nullptr);
    ~MainWindow();

public slots:
    void sendFrame();
    void clearFrames();
    void updateFilter(Qt::CheckState state);
    void handleSerialData();
    void updateTable();
    void updateSerialStatus();

private:
    void setupUI();
    void setDarkTheme();
    QWidget* createStatusBar();
    QGroupBox* createTransmitPanel();
    QGroupBox* createMonitorPanel();
    void updateStatus();
    QByteArray buildPayload(); // returns 8 reserved bytes for request

    // UI Components
    QLabel *statusIndicator;
    QLabel *statusLabel;
    QLabel *busLoadValue;
    QLabel *errorValue;
    QPushButton *sendBtn;
    QLineEdit *canIdInput;
    QTextEdit *canDataInput;
    QCheckBox *filterCheckbox;
    QLineEdit *filterInput;
    QTableWidget *table;
    QGroupBox *monitorGroup;
    QTimer *timer;
    QComboBox *requestCombo;

    // Data
    bool isConnected;
    QVector<CANFrame> canFrames;
    double busLoad;
    int errorCount;

    QSerialPort* serial;
};

#endif // MAINWINDOW_H
