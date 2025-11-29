#include "homewindow.h";

#include <QApplication>
#include <QFile>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load stylesheet
    QFile styleFile(":/resources/style.qss");
    if(styleFile.open(QFile::ReadOnly)) {
        QString style = styleFile.readAll();
        a.setStyleSheet(style);
    }

    HomeWindow w;
    w.show();
    return a.exec();
}
