#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<iostream>
#include<cstdlib>
#include<queue>
#include<cstdio>
#include<queue>
#include <QtGui>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QInputDialog>
#include "dialog.h"
struct process
{
    int id;
    int temps_traitement, temps_arrive;
    int temps_rotation , temps_attente , total_temps ;
    float rendement;
    int temps_restant;
    int priorite;
    QString coleur;
};


namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

   void on_pushButton_2_clicked();




private:
    Ui::MainWindow *ui;
    Dialog *second;

};
#endif // MAINWINDOW_H
