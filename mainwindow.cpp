#include "mainwindow.h"
#include <QHeaderView>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , isConnected(false)
    , busLoad(0.0)
    , errorCount(0)
{
    setupUI();
    setDarkTheme();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::simulateCANTraffic);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    setWindowTitle("STM32 CAN Interface");
    setMinimumSize(1400, 800);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // Header
    QVBoxLayout *headerLayout = new QVBoxLayout();
    QLabel *title = new QLabel("STM32 CAN Interface");
    QFont titleFont("Arial", 24, QFont::Bold);
    title->setFont(titleFont);
    title->setStyleSheet("color: #60A5FA;");

    QLabel *subtitle = new QLabel("Monitor and transmit CAN bus frames");
    subtitle->setStyleSheet("color: #94A3B8; font-size: 14px;");

    headerLayout->addWidget(title);
    headerLayout->addWidget(subtitle);
    mainLayout->addLayout(headerLayout);

    // Status Bar
    QWidget *statusBar = createStatusBar();
    mainLayout->addWidget(statusBar);

    // Main content
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->setSpacing(15);

    QGroupBox *transmitPanel = createTransmitPanel();
    contentLayout->addWidget(transmitPanel, 1);

    QGroupBox *monitorPanel = createMonitorPanel();
    contentLayout->addWidget(monitorPanel, 2);

    mainLayout->addLayout(contentLayout);
}

void MainWindow::setDarkTheme()
{
    setStyleSheet(R"(
        QMainWindow {
            background-color: #0F172A;
        }
        QWidget {
            background-color: #0F172A;
            color: #F1F5F9;
            font-family: Arial;
            font-size: 13px;
        }
        QGroupBox {
            background-color: #1E293B;
            border: 1px solid #334155;
            border-radius: 8px;
            margin-top: 10px;
            padding: 15px;
            font-weight: bold;
            font-size: 16px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px;
            color: #60A5FA;
        }
        QLineEdit, QTextEdit {
            background-color: #334155;
            border: 1px solid #475569;
            border-radius: 6px;
            padding: 8px;
            color: #F1F5F9;
        }
        QLineEdit:focus, QTextEdit:focus {
            border: 2px solid #3B82F6;
        }
        QPushButton {
            background-color: #3B82F6;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 10px 20px;
            font-weight: bold;
            font-size: 13px;
        }
        QPushButton:hover {
            background-color: #2563EB;
        }
        QPushButton:pressed {
            background-color: #1D4ED8;
        }
        QPushButton:disabled {
            background-color: #475569;
            color: #94A3B8;
        }
        QTableWidget {
            background-color: #0F172A;
            border: 1px solid #334155;
            border-radius: 6px;
            gridline-color: #334155;
        }
        QTableWidget::item {
            padding: 8px;
            border-bottom: 1px solid #334155;
        }
        QTableWidget::item:selected {
            background-color: #1E293B;
        }
        QHeaderView::section {
            background-color: #334155;
            color: #F1F5F9;
            padding: 10px;
            border: none;
            font-weight: bold;
        }
        QCheckBox {
            spacing: 8px;
        }
        QCheckBox::indicator {
            width: 18px;
            height: 18px;
            border-radius: 3px;
            border: 2px solid #475569;
            background-color: #334155;
        }
        QCheckBox::indicator:checked {
            background-color: #3B82F6;
            border-color: #3B82F6;
        }
    )");
}

QWidget* MainWindow::createStatusBar()
{
    QWidget *statusWidget = new QWidget();
    statusWidget->setStyleSheet(R"(
        QWidget {
            background-color: #1E293B;
            border-radius: 8px;
            padding: 15px;
        }
    )");

    QHBoxLayout *layout = new QHBoxLayout(statusWidget);

    statusIndicator = new QLabel("●");
    statusIndicator->setStyleSheet("color: #EF4444; font-size: 20px;");

    statusLabel = new QLabel("Disconnected");
    QFont boldFont("Arial", 12, QFont::Bold);
    statusLabel->setFont(boldFont);

    QLabel *busLoadLabel = new QLabel("Bus Load:");
    busLoadValue = new QLabel("0.0%");
    busLoadValue->setStyleSheet("color: #60A5FA;");

    QLabel *errorLabel = new QLabel("Errors:");
    errorValue = new QLabel("0");
    errorValue->setStyleSheet("color: #FBBF24;");

    connectBtn = new QPushButton("Connect");
    connectBtn->setMinimumWidth(120);
    connectBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #10B981;
        }
        QPushButton:hover {
            background-color: #059669;
        }
    )");
    connect(connectBtn, &QPushButton::clicked, this, &MainWindow::toggleConnection);

    layout->addWidget(statusIndicator);
    layout->addWidget(statusLabel);
    layout->addSpacing(30);
    layout->addWidget(busLoadLabel);
    layout->addWidget(busLoadValue);
    layout->addSpacing(30);
    layout->addWidget(errorLabel);
    layout->addWidget(errorValue);
    layout->addStretch();
    layout->addWidget(connectBtn);

    return statusWidget;
}

QGroupBox* MainWindow::createTransmitPanel()
{
    QGroupBox *group = new QGroupBox("📤 Transmit Frame");
    QVBoxLayout *layout = new QVBoxLayout(group);

    QLabel *idLabel = new QLabel("CAN ID (Hex)");
    idLabel->setStyleSheet("font-weight: bold; margin-top: 10px;");
    canIdInput = new QLineEdit("0x123");

    layout->addWidget(idLabel);
    layout->addWidget(canIdInput);

    QLabel *dataLabel = new QLabel("Data (Hex bytes)");
    dataLabel->setStyleSheet("font-weight: bold; margin-top: 15px;");
    canDataInput = new QTextEdit();
    canDataInput->setPlainText("00 00 00 00 00 00 00 00");
    canDataInput->setMaximumHeight(100);

    layout->addWidget(dataLabel);
    layout->addWidget(canDataInput);

    sendBtn = new QPushButton("📨 Send Frame");
    sendBtn->setEnabled(false);
    connect(sendBtn, &QPushButton::clicked, this, &MainWindow::sendFrame);
    layout->addWidget(sendBtn);

    QLabel *filterLabel = new QLabel("⚙️ Filter");
    filterLabel->setStyleSheet("font-weight: bold; margin-top: 20px; padding-top: 15px; border-top: 1px solid #334155;");
    layout->addWidget(filterLabel);

    filterCheckbox = new QCheckBox("Enable ID filter");
    connect(filterCheckbox, &QCheckBox::stateChanged, this, &MainWindow::updateFilter);
    layout->addWidget(filterCheckbox);

    filterInput = new QLineEdit();
    filterInput->setPlaceholderText("Filter by ID...");
    filterInput->setEnabled(false);
    connect(filterInput, &QLineEdit::textChanged, this, &MainWindow::updateTable);
    layout->addWidget(filterInput);

    layout->addStretch();

    return group;
}

QGroupBox* MainWindow::createMonitorPanel()
{
    monitorGroup = new QGroupBox("📊 CAN Monitor (0 frames)");
    QVBoxLayout *layout = new QVBoxLayout(monitorGroup);

    QPushButton *clearBtn = new QPushButton("🗑️ Clear");
    clearBtn->setMaximumWidth(100);
    clearBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #334155;
        }
        QPushButton:hover {
            background-color: #475569;
        }
    )");
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::clearFrames);

    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addStretch();
    headerLayout->addWidget(clearBtn);
    layout->addLayout(headerLayout);

    table = new QTableWidget();
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"Time", "Dir", "ID", "DLC", "Data"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    layout->addWidget(table);

    return monitorGroup;
}

void MainWindow::toggleConnection()
{
    isConnected = !isConnected;

    if (isConnected) {
        statusIndicator->setStyleSheet("color: #10B981; font-size: 20px;");
        statusLabel->setText("Connected");
        connectBtn->setText("Disconnect");
        connectBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #EF4444;
                min-width: 120px;
            }
            QPushButton:hover {
                background-color: #DC2626;
            }
        )");
        sendBtn->setEnabled(true);
        busLoad = 15.0;
        timer->start(1000);
    } else {
        statusIndicator->setStyleSheet("color: #EF4444; font-size: 20px;");
        statusLabel->setText("Disconnected");
        connectBtn->setText("Connect");
        connectBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #10B981;
                min-width: 120px;
            }
            QPushButton:hover {
                background-color: #059669;
            }
        )");
        sendBtn->setEnabled(false);
        timer->stop();
        busLoad = 0.0;
    }

    updateStatus();
}

void MainWindow::sendFrame()
{
    if (!isConnected) return;

    CANFrame frame;
    frame.timestamp = QTime::currentTime().toString("HH:mm:ss.zzz");
    frame.canId = canIdInput->text();
    frame.data = canDataInput->toPlainText();
    frame.dlc = frame.data.split(' ', Qt::SkipEmptyParts).size();
    frame.direction = "TX";

    canFrames.prepend(frame);

    if (canFrames.size() > 50) {
        canFrames.resize(50);
    }

    updateTable();
}

void MainWindow::clearFrames()
{
    canFrames.clear();
    updateTable();
}

void MainWindow::updateFilter()
{
    filterInput->setEnabled(filterCheckbox->isChecked());
    updateTable();
}

void MainWindow::simulateCANTraffic()
{
    QStringList ids = {"0x100", "0x123", "0x200", "0x456"};
    QString randomId = ids[QRandomGenerator::global()->bounded(ids.size())];

    QStringList dataBytes;
    for (int i = 0; i < 8; i++) {
        int byte = QRandomGenerator::global()->bounded(256);
        dataBytes << QString("%1").arg(byte, 2, 16, QChar('0')).toUpper();
    }

    CANFrame frame;
    frame.timestamp = QTime::currentTime().toString("HH:mm:ss.zzz");
    frame.canId = randomId;
    frame.data = dataBytes.join(' ');
    frame.dlc = 8;
    frame.direction = "RX";

    canFrames.prepend(frame);

    if (canFrames.size() > 50) {
        canFrames.resize(50);
    }

    busLoad = qMin(95.0, busLoad + QRandomGenerator::global()->generateDouble() * 5.0);
    updateStatus();
    updateTable();
}

void MainWindow::updateStatus()
{
    busLoadValue->setText(QString("%1%").arg(busLoad, 0, 'f', 1));
    errorValue->setText(QString::number(errorCount));
}

void MainWindow::updateTable()
{
    QVector<CANFrame> frames = canFrames;

    if (filterCheckbox->isChecked() && !filterInput->text().isEmpty()) {
        QString filterText = filterInput->text().toLower();
        frames.erase(std::remove_if(frames.begin(), frames.end(),
                                    [&filterText](const CANFrame& f) {
                                        return !f.canId.toLower().contains(filterText);
                                    }), frames.end());
    }

    monitorGroup->setTitle(QString("📊 CAN Monitor (%1 frames)").arg(frames.size()));

    table->setRowCount(frames.size());

    for (int row = 0; row < frames.size(); row++) {
        const CANFrame& frame = frames[row];

        table->setItem(row, 0, new QTableWidgetItem(frame.timestamp));

        QTableWidgetItem *dirItem = new QTableWidgetItem(frame.direction);
        if (frame.direction == "TX") {
            dirItem->setForeground(QColor("#60A5FA"));
        } else {
            dirItem->setForeground(QColor("#34D399"));
        }
        table->setItem(row, 1, dirItem);

        QTableWidgetItem *idItem = new QTableWidgetItem(frame.canId);
        idItem->setForeground(QColor("#FBBF24"));
        table->setItem(row, 2, idItem);

        table->setItem(row, 3, new QTableWidgetItem(QString::number(frame.dlc)));
        table->setItem(row, 4, new QTableWidgetItem(frame.data));
    }
}
