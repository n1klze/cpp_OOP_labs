#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString inputFilename = QFileDialog::getOpenFileName(this, "Выбрать файл", "../../examples", "Life files (*.life);; All files (*.*)");
    ui->label->setText(inputFilename);
}

void MainWindow::on_dumpButton_clicked()
{
    QString outputFilename = QFileDialog::getOpenFileName(this, "Выбрать файл", "../../examples", "Life files (*.life);; All files (*.*)");
    //model.Dump(outputFilename.toStdString());
}

void MainWindow::on_exitButton_clicked()
{
    delete this;
    exit(0);
}
