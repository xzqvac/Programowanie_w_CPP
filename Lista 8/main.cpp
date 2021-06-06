#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QMessageBox::information(&w, "Informacja",
                             "Ten program reaguje na <br>"
                             "<b><span style=\"color:red\">kliknięcia myszą</span></b>");
    return a.exec();
}
