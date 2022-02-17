#include "calcMainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
int main(int argc, char *argv[]) {
    //Qapplication有且只有一个
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "qt_" + QLocale(locale).name();
        if (translator.load(":/qm/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    CalcMainWindow window;
    window.show();
    return a.exec();
}
