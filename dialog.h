#ifndef DIALOG_H
#define DIALOG_H
#include <QtCore>
#include <QDialog>
#include<QGraphicsScene>
#include <QtGui>
#include <QTableWidget>
#include<QLCDNumber>
const int Rectangle_Width=15;
const int Rectangle_Height=100;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void afficher(int n);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();






    void on_pushButton_4_clicked();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectangle;


};

#endif // DIALOG_H
