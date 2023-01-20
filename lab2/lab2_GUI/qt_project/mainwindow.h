#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "game_widget.h"
#include "../life_gui_interface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_exitButton_clicked();

    void on_dumpButton_clicked();

private:
    Ui::MainWindow *ui;
    GameWidget* game;
    life_gui::LifeGuiInterface model;
};
#endif // MAINWINDOW_H
