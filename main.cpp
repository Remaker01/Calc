#include "calcMainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
int main(int argc, char *argv[]) {
    //Qapplication有且只有一个
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(":/qm/qt_zh_CN.qm");
    a.installTranslator(&translator);
    CalcMainWindow window;
    window.show();
    return a.exec();
}
