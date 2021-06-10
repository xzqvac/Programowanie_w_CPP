#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_widget.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_Koniec, SIGNAL(triggered()), this, SLOT(koniec_programu()) );
    connect(ui->przycisk, SIGNAL(clicked()), ui->widget, SLOT(on_przycisk_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::koniec_programu()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Mind Blowing Optical ilusion", "Quit?", QMessageBox::Yes|QMessageBox::No);
    if (reply ==  QMessageBox::Yes) qApp->quit();
}


void MainWindow::on_action_O_programie_triggered()
{
 QMessageBox::aboutQt(this,"O wspaniałym programie");
}


void MainWindow::on_przycisk_clicked()
{
    if(ui->przycisk->text() == "Start") ui->przycisk->setText("Stop");

    else ui->przycisk->setText("Start");
}

