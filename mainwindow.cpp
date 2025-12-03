#include "mainwindow.h"
#include <QHeaderView>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTime>
#include <QVector>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QMessageBox>
#include <algorithm>
#include <QDebug>

// -------------------- CONSTRUCTOR --------------------
MainWindow::MainWindow(QWidget *parent, QSerialPort* serialPort)
    : QMainWindow(parent)
    , serial(serialPort)
    , isConnected(false)
    , busLoad(0.0)
    , errorCount(0)
{
    setupUI();
    setDarkTheme();

    if (serial) {
        connect(serial, &QSerialPort::readyRead, this, &MainWindow::handleSerialData);
    }

    // Initial status
    updateSerialStatus();
}

// -------------------- DESTRUCTOR --------------------
MainWindow::~MainWindow()
{
}

// -------------------- SETUP UI --------------------
void MainWindow::setupUI()
{
    setWindowTitle("STM32 CAN Interface");
    setMinimumSize(1000, 700);

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

// -------------------- DARK THEME --------------------
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

// -------------------- STATUS BAR --------------------
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

    layout->addWidget(statusIndicator);
    layout->addWidget(statusLabel);
    layout->addSpacing(30);
    layout->addWidget(busLoadLabel);
    layout->addWidget(busLoadValue);
    layout->addSpacing(30);
    layout->addWidget(errorLabel);
    layout->addWidget(errorValue);
    layout->addStretch();

    return statusWidget;
}

// -------------------- TRANSMIT PANEL --------------------
QGroupBox* MainWindow::createTransmitPanel()
{
    QGroupBox *group = new QGroupBox("📤 Transmit Frame");
    QVBoxLayout *layout = new QVBoxLayout(group);

    QLabel *idLabel = new QLabel("CAN ID (Hex)");
    idLabel->setStyleSheet("font-weight: bold; margin-top: 10px;");
    canIdInput = new QLineEdit("0x123");
    canIdInput->setEnabled(false);
    layout->addWidget(idLabel);
    layout->addWidget(canIdInput);

    QLabel *dataLabel = new QLabel("Data (Hex bytes)");
    dataLabel->setStyleSheet("font-weight: bold; margin-top: 15px;");
    canDataInput = new QTextEdit();
    canDataInput->setPlainText("00 00 00 00 00 00 00 00");
    canDataInput->setMaximumHeight(100);
    canDataInput->setEnabled(false);
    layout->addWidget(dataLabel);
    layout->addWidget(canDataInput);

    QLabel *requestLabel = new QLabel("Request Type");
    requestLabel->setStyleSheet("font-weight: bold; margin-top: 20px;");
    layout->addWidget(requestLabel);

    requestCombo = new QComboBox();
    requestCombo->addItem("Select request...", 0);
    requestCombo->addItem("SOC of Total Voltage / Current", 0x1900140);
    requestCombo->addItem("Max/Min Cell Voltages", 0x1910140);
    requestCombo->addItem("Max/Min Temperature", 0x1920140);
    layout->addWidget(requestCombo);

    sendBtn = new QPushButton("📨 Send Frame");
    sendBtn->setEnabled(false);
    connect(sendBtn, &QPushButton::clicked, this, &MainWindow::sendFrame);
    layout->addWidget(sendBtn);

    QLabel *filterLabel = new QLabel("⚙️ Filter");
    filterLabel->setStyleSheet("font-weight: bold; margin-top: 20px; padding-top: 15px; border-top: 1px solid #334155;");
    layout->addWidget(filterLabel);

    filterCheckbox = new QCheckBox("Enable ID filter");
    connect(filterCheckbox, &QCheckBox::checkStateChanged, this, &MainWindow::updateFilter);
    layout->addWidget(filterCheckbox);

    filterInput = new QLineEdit();
    filterInput->setPlaceholderText("Filter by ID...");
    filterInput->setEnabled(false);
    connect(filterInput, &QLineEdit::textChanged, this, &MainWindow::updateTable);
    layout->addWidget(filterInput);

    layout->addStretch();
    return group;
}

// -------------------- MONITOR PANEL (CORRECTION) --------------------
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

    // ✅ CORRECTION: Meilleure configuration des colonnes
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents); // Time
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);            // Dir
    table->horizontalHeader()->resizeSection(1, 60);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents); // ID
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);            // DLC
    table->horizontalHeader()->resizeSection(3, 60);
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);          // Data

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    // ✅ CORRECTION: Activer le word wrap pour afficher le texte long
    table->setWordWrap(true);

    // ✅ CORRECTION: Permettre un défilement vertical fluide
    table->verticalHeader()->setDefaultSectionSize(40); // Hauteur minimale par défaut
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    layout->addWidget(table);
    return monitorGroup;
}

// -------------------- SERIAL STATUS --------------------
void MainWindow::updateSerialStatus()
{
    if (serial && serial->isOpen()) {
        isConnected = true;
        statusIndicator->setStyleSheet("color: #10B981; font-size: 20px;");
        statusLabel->setText("Connected");
        sendBtn->setEnabled(true);
    } else {
        isConnected = false;
        statusIndicator->setStyleSheet("color: #EF4444; font-size: 20px;");
        statusLabel->setText("Disconnected");
        sendBtn->setEnabled(false);
    }
    updateStatus();
}

// -------------------- SEND FRAME --------------------
QByteArray MainWindow::buildPayload()
{
    QByteArray frame(8, 0x00); // 8 bytes reserved
    return frame;
}

void MainWindow::sendFrame()
{
    if (!isConnected) return;

    quint32 canId = requestCombo->currentData().toUInt();
    if (canId == 0) {
        QMessageBox::warning(this, "Request Type", "Please select a request type!");
        return;
    }

    // Build payload for table only (display purpose)
    QByteArray payload(8, 0x00); // 8 bytes reserved

    // Send only CAN ID via UART
    if (serial && serial->isOpen()) {
        QByteArray packet;
        packet.append((canId >> 24) & 0xFF);
        packet.append((canId >> 16) & 0xFF);
        packet.append((canId >> 8) & 0xFF);
        packet.append(canId & 0xFF);

        serial->write(packet);
        serial->flush();

        // Log sent CAN ID
        qDebug() << "Sent CAN ID to UART:" << QString("0x%1").arg(canId, 7, 16, QChar('0')).toUpper();
        qDebug() << "Raw bytes:" << packet.toHex(' ').toUpper();
    }

    // Update table with CAN ID + display payload
    CANFrame frame;
    frame.timestamp = QTime::currentTime().toString("HH:mm:ss.zzz");
    frame.canId = QString("0x%1").arg(canId, 7, 16, QChar('0')).toUpper();
    frame.data = payload.toHex(' ').toUpper(); // Keep display payload
    frame.dlc = payload.size();
    frame.direction = "TX";

    canFrames.prepend(frame);
    if (canFrames.size() > 50)
        canFrames.resize(50);

    updateTable();
}


// -------------------- CLEAR FRAMES --------------------
void MainWindow::clearFrames()
{
    canFrames.clear();
    updateTable();
}

// -------------------- FILTER --------------------
void MainWindow::updateFilter(Qt::CheckState)
{
    filterInput->setEnabled(filterCheckbox->isChecked());
    updateTable();
}

// -------------------- SERIAL DATA --------------------
void MainWindow::handleSerialData()
{
    if (!serial) return;

    // ✅ CORRECTION: Accumuler les données dans un buffer
    static QByteArray serialBuffer;
    serialBuffer.append(serial->readAll());

    // 🔍 DEBUG: Afficher les données brutes reçues
    qDebug() << "========== NEW SERIAL DATA ==========";
    qDebug() << "Buffer size:" << serialBuffer.size() << "bytes";
    qDebug() << "Buffer content:" << QString(serialBuffer);

    // ✅ CORRECTION: Traiter uniquement les lignes complètes (terminées par \n ou \r\n)
    int newlinePos;
    while ((newlinePos = serialBuffer.indexOf('\n')) != -1)
    {
        // Extraire une ligne complète
        QByteArray lineData = serialBuffer.left(newlinePos);
        serialBuffer.remove(0, newlinePos + 1);

        QString line = QString::fromUtf8(lineData).trimmed();

        // 🔍 DEBUG: Afficher la ligne traitée
        qDebug() << "Processing line:" << line;
        qDebug() << "Line length:" << line.length();

        // ✅ Ignorer les lignes vides
        if (line.isEmpty()) {
            qDebug() << "⚠️ Skipping empty line";
            continue;
        }

        // ✅ CORRECTION: Vérifier si la ligne commence par [ID 0x
        if (!line.startsWith("[ID 0x")) {
            qDebug() << "⚠️ Line doesn't start with '[ID 0x' - skipping";
            continue;
        }

        // ✅ Créer une nouvelle trame CAN
        CANFrame frame;
        frame.timestamp = QTime::currentTime().toString("HH:mm:ss.zzz");
        frame.direction = "RX";

        // ✅ CORRECTION: Extraire le CAN ID
        int idStart = line.indexOf("0x");
        int idEnd = line.indexOf("]", idStart);

        if (idStart == -1 || idEnd == -1) {
            qDebug() << "❌ Failed to extract CAN ID - malformed line";
            continue;
        }

        frame.canId = line.mid(idStart, idEnd - idStart).toUpper();
        qDebug() << "✅ Extracted CAN ID:" << frame.canId;

        // ✅ CORRECTION: Extraire les données après le ']'
        int dataStart = idEnd + 1;
        if (dataStart < line.length()) {
            frame.data = line.mid(dataStart).trimmed();
            qDebug() << "✅ Extracted data:" << frame.data;
        } else {
            frame.data = "No data";
            qDebug() << "⚠️ No data after ] - setting to 'No data'";
        }

        // ✅ DLC = longueur du texte formaté
        frame.dlc = frame.data.length();

        // 🔍 DEBUG: Afficher la trame complète
        qDebug() << "📦 Complete Frame:";
        qDebug() << "  Timestamp:" << frame.timestamp;
        qDebug() << "  Direction:" << frame.direction;
        qDebug() << "  CAN ID:" << frame.canId;
        qDebug() << "  Data:" << frame.data;
        qDebug() << "  DLC:" << frame.dlc;

        // ✅ Ajouter la trame à la liste
        canFrames.prepend(frame);
        if (canFrames.size() > 50)
            canFrames.resize(50);

        qDebug() << "✅ Frame added. Total frames:" << canFrames.size();
    }

    qDebug() << "========== END SERIAL DATA ==========";
    qDebug() << "Remaining buffer size:" << serialBuffer.size();
    qDebug() << "";

    // ✅ Mettre à jour le tableau
    updateTable();
}

// -------------------- UPDATE TABLE (CORRECTION) --------------------
void MainWindow::updateTable()
{
    QVector<CANFrame> frames = canFrames;

    // Appliquer le filtre si activé
    if (filterCheckbox->isChecked() && !filterInput->text().isEmpty()) {
        QString filterText = filterInput->text().toLower();
        frames.erase(std::remove_if(frames.begin(), frames.end(),
                                    [&filterText](const CANFrame& f) {
                                        return !f.canId.toLower().contains(filterText);
                                    }), frames.end());
    }

    // Mettre à jour le titre du groupe
    monitorGroup->setTitle(QString("📊 CAN Monitor (%1 frames)").arg(frames.size()));

    // ✅ CORRECTION: Définir le nombre de lignes
    table->setRowCount(frames.size());

    // ✅ CORRECTION: Remplir le tableau
    for (int row = 0; row < frames.size(); row++) {
        const CANFrame& frame = frames[row];

        // Colonne 0: Timestamp
        QTableWidgetItem *timeItem = new QTableWidgetItem(frame.timestamp);
        timeItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, 0, timeItem);

        // Colonne 1: Direction (TX/RX)
        QTableWidgetItem *dirItem = new QTableWidgetItem(frame.direction);
        dirItem->setTextAlignment(Qt::AlignCenter);
        dirItem->setForeground(frame.direction == "TX" ? QColor("#60A5FA") : QColor("#34D399"));
        table->setItem(row, 1, dirItem);

        // Colonne 2: CAN ID
        QTableWidgetItem *idItem = new QTableWidgetItem(frame.canId);
        idItem->setTextAlignment(Qt::AlignCenter);
        idItem->setForeground(QColor("#FBBF24"));
        table->setItem(row, 2, idItem);

        // Colonne 3: DLC
        QTableWidgetItem *dlcItem;
        if (frame.direction == "RX") {
            dlcItem = new QTableWidgetItem("N/A");
        } else {
            dlcItem = new QTableWidgetItem(QString::number(frame.dlc));
        }
        dlcItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, 3, dlcItem);

        // ✅ CORRECTION: Colonne 4: Data (avec support pour texte long)
        QTableWidgetItem *dataItem = new QTableWidgetItem(frame.data);
        dataItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        // ✅ IMPORTANT: Définir des flags pour permettre l'affichage de texte long
        dataItem->setFlags(dataItem->flags() & ~Qt::ItemIsEditable);

        table->setItem(row, 4, dataItem);
    }

    // ✅ CORRECTION: Ajuster automatiquement la hauteur des lignes
    table->resizeRowsToContents();

    // ✅ OPTIONNEL: S'assurer que la colonne Data est assez large
    table->resizeColumnToContents(4);
}

// -------------------- UPDATE STATUS --------------------
void MainWindow::updateStatus()
{
    busLoadValue->setText(QString("%1%").arg(busLoad, 0, 'f', 1));
    errorValue->setText(QString::number(errorCount));
}
