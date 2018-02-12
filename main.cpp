#include "maindialog.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;

    if (translator.load(QLocale(), QLatin1String("res/assessmentscientificwork"), QLatin1String("_"), QLatin1String(":/translations")))
        a.installTranslator(&translator);

    MainDialog w;
    w.show();

    return a.exec();
}
