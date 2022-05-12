#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialog.h>
#include <QPixmap>
extern int nombre;
extern int ch;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap p(":/pic/pic/az.png");
    int w=ui->label->width();
    int h=ui->label->height();
    ui->label->setPixmap(p.scaled(w,h,Qt::IgnoreAspectRatio));
    ui->lineEdit->setPlaceholderText("veuiller entre le nombre...");



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString text=ui->lineEdit->text();
    nombre=text.toInt();
    if(nombre==0||nombre<4||nombre>10)
    {

         QMessageBox::warning(this,"Waring","veuiller entrer un nombre entre 1 et 10!");
    }

    else
    {
        bool ok = false;
        QString pseudo = QInputDialog::getText(this, "nom", "Quel est votre nom ?", QLineEdit::Normal, QString(), &ok);
        if (ok && !pseudo.isEmpty())
        {
            QMessageBox::information(this, "Pseudo", "Bonjour " + pseudo + ",bienvenue dans cette simulation");
        }
        else
        {
            QMessageBox::critical(this, "Pseudo", "ok vous n'avez pas de nom trs bien");
        }

        second=new Dialog(this);
        second->setModal(true);
        second->exec();

    }
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}






