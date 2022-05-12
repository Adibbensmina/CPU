#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QElapsedTimer>
#include<QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>
#include <cmath>
#include <QTextStream>
using namespace std;
extern int nombre;
extern int ch;
extern struct process p[10],p1[10],temp;
int tempo[10];
int condition=0;
int time_slice;
int q,h;
extern queue<int>q1;
int c=0;
int time_slice1;
float total_tempsrotation = 0;
float total_tempsattente = 0;
float total_rendement=0;

float x=0, y=0;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,200,100);
     ui->tableWidget->setRowCount(nombre);
     ui->tableWidget->setColumnCount(5);//4
     ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:yellow;}");
     ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:red;}");
     ui->lineEdit->setPlaceholderText("entre le temps...");


}

void Dialog::afficher(int n)

{

    int i;

    QStringList header;
    header<<"ID"<<"temps achevement"<<"temps rotation"<<"temps attente"<<"rendement";
    ui->tableWidget_2->setRowCount(nombre);
    ui->tableWidget_2->setColumnCount(5);//4
    ui->tableWidget_2->setHorizontalHeaderLabels(header);
    ui->tableWidget_2->setHorizontalHeaderLabels(header);
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:yellow;}");
    ui->tableWidget_2->verticalHeader()->setStyleSheet("QHeaderView::section{background:red;}");
    for (i=0 ; i<=ui->tableWidget_2->rowCount() ; i++ )
    {

        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].id);
        item->setText(temp_string);
        ui->tableWidget_2->setItem(i,0,item);
    }

    for (i=0 ; i<=ui->tableWidget_2->rowCount() ; i++ )
      {

          QTableWidgetItem* item = new QTableWidgetItem();
          QString temp_string=QString::number(p[i+1].total_temps);
          item->setText(temp_string);
          ui->tableWidget_2->setItem(i,1,item);
      }

      for (i=0 ; i<=ui->tableWidget_2->rowCount() ; i++ )
      {
          QTableWidgetItem* item = new QTableWidgetItem();
          QString temp_string=QString::number(p[i+1].temps_rotation);
          item->setText(temp_string);
          ui->tableWidget_2->setItem(i,2,item);
      }

      for (i=0 ; i<=ui->tableWidget_2->rowCount() ; i++ )
      {
          QTableWidgetItem* item = new QTableWidgetItem();
          QString temp_string=QString::number(p[i+1].temps_attente);
          item->setText(temp_string);
          ui->tableWidget_2->setItem(i,3,item);
      }
      for (i=0 ; i<=ui->tableWidget_2->rowCount() ; i++ )
      {
          QTableWidgetItem* item = new QTableWidgetItem();
          QString temp_string=QString::number(p[i+1].rendement,'f',2);
          item->setText(temp_string);
          ui->tableWidget_2->setItem(i,4,item);
      }

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_3_clicked()
{

    int temp_data[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];

    QString tableData[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];
    //memset(tableData, 0, sizeof(tableData));
    //memset(temp_data, 0, sizeof(temp_data));

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {

            tableData[i][j]=ui->tableWidget->item(i,j)->text();

        }
    }

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->columnCount()-1;j++)
        {

            temp_data[i][j]=tableData[i][j].toInt();
        }
    }




       for(int i=0;i<ui->tableWidget->rowCount();i++)
       {
           p[i+1].id=temp_data[i][0];

       }

       for(int i=0;i<ui->tableWidget->rowCount();i++)
       {
           p[i+1].temps_arrive=temp_data[i][1];
       }

       for(int i=0;i<ui->tableWidget->rowCount();i++)
       {
           p[i+1].temps_traitement=temp_data[i][2];
       }

       for(int i=0;i<ui->tableWidget->rowCount();i++)
       {
           p[i+1].coleur=tableData[i][3];
       }
       for(int i=0;i<ui->tableWidget->rowCount();i++)
       {
           p[i+1].priorite=temp_data[i][4];
       }
       QString text_tempa=ui->lineEdit->text();
       time_slice=text_tempa.toInt();

       if(time_slice==0)
       {
           QMessageBox::warning(this,"Attention","entrer un temps d'execution pls!!!");
       }
       else
       {
           condition+=1;
       }


}

void Dialog::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked())
    {
        ch=1;
        condition+=1;
    }
    else if(ui->radioButton_3->isChecked())
    {
        ch=2;
        condition+=1;
    }
    else if(ui->radioButton_4->isChecked())
    {
        ch=3;
        condition+=1;
    }
    else if(ui->radioButton_2->isChecked())
    {
        ch=4;
        condition+=1;
    }
    else if(ui->radioButton_5->isChecked())
    {
            ch=5;
            condition+=1;

    }

    else
    {
        QMessageBox::warning(this,"Warning","veuiller entre un algorithme!");
    }
    //################################################################################################//
    if(condition>=2)
    {
    if (ch==1)
    {

        int i, sum=0;
        /*
        for(i=1;i<=nombre;i++)
        {
            p1[i]=p[i];
        }
        **/
       for (int j = 1; j <= nombre; j++)
          {
              sum += p[j].temps_traitement;
              p[j].total_temps += sum;
          }
       for (int k = 0; k <= nombre; k++)
                 {
                     p[k].temps_rotation = p[k].total_temps -p[k].temps_arrive;
                     p[k].rendement=p[k].temps_traitement/float(p[k].temps_rotation);
                      total_tempsrotation +=p[k].temps_rotation;
                      total_rendement+=p[k].rendement;
                       //ui->label_5->setText("le rendement moyenne:" + QString::number());


                 }
                 for (int k = 0; k <= nombre; k++)

                 {

                     p[k].temps_attente = p[k].temps_rotation - p[k].temps_traitement;
                     total_tempsattente +=p[k].temps_attente;

                 }

                    float x = total_tempsrotation/ nombre;
                    float y = total_tempsattente/ nombre;
                    //float z=total_rendement/ nombre;


         QBrush color_brush(QColor(p[1].coleur));
                     QPen blackpen(Qt::black);
                     blackpen.setWidth(1);
                     QElapsedTimer t;
                     t.start();
                     //QGraphicsRectItem *rectangle=new QGraphicsRectItem();
                     rectangle=scene->addRect(-200,0,Rectangle_Width*p[1].temps_traitement,Rectangle_Height,blackpen,color_brush);

                     QGraphicsTextItem *txtitem = new QGraphicsTextItem("0");
                     txtitem->setPos(QPointF(-200, 100));
                     scene->addItem(txtitem);


                     while(t.elapsed() < 2500)
                     {
                         QCoreApplication::processEvents();
                     }
                     for(i=2;i<=nombre;i++)
                     {
                         QBrush color_brush(QColor(p[i].coleur));
                         QPen blackpen(Qt::black);
                         blackpen.setWidth(1);
                         rectangle=scene->addRect(-200+Rectangle_Width*p[i-1].total_temps,0,Rectangle_Width*p[i].temps_traitement,Rectangle_Height,blackpen,color_brush);
                         QString temp_str=QString::number(p[i-1].total_temps);
                         QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                         txtitem->setPos(QPointF(-200+Rectangle_Width*p[i-1].total_temps, 100));
                         scene->addItem(txtitem);
                         //text=scene->addText();
                         QElapsedTimer t;
                         t.start();
                         while(t.elapsed() < 2500)
                         {
                             QCoreApplication::processEvents();
                         }

                     }

                     QString temp_str=QString::number(p[nombre].total_temps);
                     QGraphicsTextItem *txtitema = new QGraphicsTextItem(temp_str);
                     txtitema->setPos(QPointF(-200+Rectangle_Width*p[nombre].total_temps, 100));
                     scene->addItem(txtitema);

                     condition=0;
                     ui->label_4->setText("le temps de rotation moyenne:" + QString::number(x));
                      ui->label_5->setText("le temps d'attente moyenne:" + QString::number(y));
                      //ui->label_2->setText("le rendement moyenne:" + QString::number(z,'f',2));

                    afficher(nombre);
                    QMessageBox::information(this,"reussi","fin de la simulation!");

    }

    //#############################################################################################//
    if(ch==2)
    {
        int min,sum=0,traitement=0;
        int variable;
        QString color;
        int k=1;
        // on trie la table du temps arrive
          for (int i = 0; i <= nombre; i++)
          {
              for (int j = 0; j <= nombre; j++)  // on parcout le tems d_arrive des processus
              {
                  if (p[j].temps_arrive > p[i].temps_arrive)
                  {
                      variable = p[j].id;//on parcoure les deux tables si le temps du taitement superieue a la date arrive
                      p[j].id = p[i].id;// si la condition est vraie on permute les processus avec la date d'arrive et temps traitement
                      p[i].id = variable;
                      color=p[j].coleur;
                      p[j].coleur=p[i].coleur;
                      p[i].coleur=color;
                      variable = p[j].temps_arrive;
                      p[j].temps_arrive =  p[i].temps_arrive;
                      p[i].temps_arrive = variable;
                      variable = p[j].temps_traitement;
                      p[j].temps_traitement = p[i].temps_traitement;
                      p[i].temps_traitement = variable;
                  }
              }
          }
        for (int j = 0; j <= nombre; j++)
           {
               traitement = traitement + p[j].temps_traitement;// calcule le totale du temsp du traitement pour comparer avec la date d'arrive des processus
               min = p[k].temps_traitement;//  variable qui permet de tester le temps de traitement le  plus petit
               for (int i = k; i <= nombre; i++)
               {
                   if (traitement >= p[i].temps_arrive && p[i].temps_traitement < min)// on teste si le temps de traitement est superieur au temps d'arrive du deuxieme processus
                       //puis le temps de traitement le plus petit grace a cette boucle
                   {
                       variable = p[k].id;//on parcoure les deux tables si le temps du taitement superieue a la date arrive
                       p[k].id = p[i].id;// si la condition est vraie on permute les processus avec la date d'arrive et temps traitement
                       p[i].id = variable;
                       color=p[k].coleur;
                       p[k].coleur=p[i].coleur;
                       p[i].coleur=color;
                       variable = p[k].temps_arrive;
                       p[k].temps_arrive =  p[i].temps_arrive;
                       p[i].temps_arrive = variable;
                       variable = p[k].temps_traitement;
                       p[k].temps_traitement = p[i].temps_traitement;
                       p[i].temps_traitement = variable;
                   }
               }
               k++;
            }
        for (int i = 0; i <= nombre; i++)
           {
               sum += p[i].temps_traitement;
               p[i].total_temps += sum;
           }
           for (int k = 0; k <= nombre; k++)
           {
               p[k].temps_rotation = p[k].total_temps - p[k].temps_arrive;
                 p[k].rendement=p[k].temps_traitement/float(p[k].temps_rotation);
               total_tempsrotation +=p[k].temps_rotation;

           }
           for (int k = 0; k <= nombre; k++)

           {

               p[k].temps_attente = p[k].temps_rotation - p[k].temps_traitement;
               total_tempsattente +=p[k].temps_attente;
           }
           float x1 = total_tempsrotation/ nombre;
           float y1 = total_tempsattente/ nombre;

           QBrush color_brush(QColor(p[1].coleur));
                       QPen blackpen(Qt::black);
                       blackpen.setWidth(1);
                       QElapsedTimer t;
                       t.start();
                       //QGraphicsRectItem *rectangle=new QGraphicsRectItem();
                       rectangle=scene->addRect(-200,0,Rectangle_Width*p[1].temps_traitement,Rectangle_Height,blackpen,color_brush);

                       QGraphicsTextItem *txtitem = new QGraphicsTextItem("0");
                       txtitem->setPos(QPointF(-200, 100));
                       scene->addItem(txtitem);


                       while(t.elapsed() < 2500)
                       {
                           QCoreApplication::processEvents();
                       }
                       for(int i=2;i<=nombre;i++)
                       {
                           QBrush color_brush(QColor(p[i].coleur));
                           QPen blackpen(Qt::black);
                           blackpen.setWidth(1);
                           rectangle=scene->addRect(-200+Rectangle_Width*p[i-1].total_temps,0,Rectangle_Width*p[i].temps_traitement,Rectangle_Height,blackpen,color_brush);
                           QString temp_str=QString::number(p[i-1].total_temps);
                           QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                           txtitem->setPos(QPointF(-200+Rectangle_Width*p[i-1].total_temps, 100));
                           scene->addItem(txtitem);
                           //text=scene->addText();
                           QElapsedTimer t;
                           t.start();
                           while(t.elapsed() < 2500)
                           {
                               QCoreApplication::processEvents();
                           }

                       }

                       QString temp_str=QString::number(p[nombre].total_temps);
                       QGraphicsTextItem *txtitema = new QGraphicsTextItem(temp_str);
                       txtitema->setPos(QPointF(-200+Rectangle_Width*p[nombre].total_temps, 100));
                       scene->addItem(txtitema);

                       ui->label_4->setText("le temps de rotation moyenne:" + QString::number(x1));
                        ui->label_5->setText("le temps d'attente moyenne:" + QString::number(y1));

                       condition=0;
           afficher(nombre);
           QMessageBox::information(this,"reussi","fin de la simulation!");
    }
    //###################################################################################################//
    if(ch==5)
    {
        int pos,sum=0;
        int tempo;
        QString color1;
        int traitement1=0;
        for (int i = 0; i <= nombre; i++)
           {
               pos = i;//la position de i

               traitement1 = traitement1 + p[pos].temps_traitement;// calcule le totale du temsp du traitement pour comparer avec la date d'arrive des processus


               for (int j = i; j <= nombre; j++)
               {
                   if (p[j].priorite > p[pos].priorite)//si le traitement du premier processus est superieur a la date d'arrive du deuxieme alors le deuxime est arrive
                  //et la priorite du deuxime(j) est plus grand que la priorite du premier processus
                   {
                       pos = j;// alors la position est donc j




                   }
                   tempo = p[i].priorite;//
                   p[i].priorite = p[pos].priorite;//la priorite du premier processus(i) est donc attribuer au deuxieme processus(j)
                   p[pos].priorite = tempo;
                   tempo = p[i].temps_arrive;//pareil pour temps arrive
                   p[i].temps_arrive = p[pos].temps_arrive;
                   p[pos].temps_arrive = tempo;
                   tempo = p[i].temps_traitement;
                   p[i].temps_traitement = p[pos].temps_traitement;
                   p[pos].temps_traitement = tempo;
                   color1=p[i].coleur;
                   p[i].coleur=p[pos].coleur;
                   p[pos].coleur=color1;
                   tempo = p[i].id;
                   p[i].id = p[pos].id;
                   p[pos].id = tempo;
                   break;
               }

           }


        for (int i = 0; i <= nombre; i++)
           {
               sum += p[i].temps_traitement;
               p[i].total_temps += sum;
           }
           for (int k = 0; k <= nombre; k++)
           {
               p[k].temps_rotation = p[k].total_temps - p[k].temps_arrive;
               p[k].rendement=p[k].temps_traitement/float(p[k].temps_rotation);
               total_tempsrotation +=p[k].temps_rotation;

           }
           for (int k = 0; k <= nombre; k++)

           {

               p[k].temps_attente = p[k].temps_rotation - p[k].temps_traitement;
               total_tempsattente +=p[k].temps_attente;
           }
           float x1 = total_tempsrotation/ nombre;
           float y1 = total_tempsattente/ nombre;
           QBrush color_brush(QColor(p[1].coleur));
                       QPen blackpen(Qt::black);
                       blackpen.setWidth(1);
                       QElapsedTimer t;
                       t.start();
                       //QGraphicsRectItem *rectangle=new QGraphicsRectItem();
                       rectangle=scene->addRect(-200,0,Rectangle_Width*p[1].temps_traitement,Rectangle_Height,blackpen,color_brush);

                       QGraphicsTextItem *txtitem = new QGraphicsTextItem("0");
                       txtitem->setPos(QPointF(-200, 100));
                       scene->addItem(txtitem);


                       while(t.elapsed() < 2500)
                       {
                           QCoreApplication::processEvents();
                       }
                       for(int i=2;i<=nombre;i++)
                       {
                           QBrush color_brush(QColor(p[i].coleur));
                           QPen blackpen(Qt::black);
                           blackpen.setWidth(1);
                           rectangle=scene->addRect(-200+Rectangle_Width*p[i-1].total_temps,0,Rectangle_Width*p[i].temps_traitement,Rectangle_Height,blackpen,color_brush);
                           QString temp_str=QString::number(p[i-1].total_temps);
                           QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                           txtitem->setPos(QPointF(-200+Rectangle_Width*p[i-1].total_temps, 100));
                           scene->addItem(txtitem);
                           //text=scene->addText();
                           QElapsedTimer t;
                           t.start();
                           while(t.elapsed() < 2500)
                           {
                               QCoreApplication::processEvents();
                           }

                       }

                       QString temp_str=QString::number(p[nombre].total_temps);
                       QGraphicsTextItem *txtitema = new QGraphicsTextItem(temp_str);
                       txtitema->setPos(QPointF(-200+Rectangle_Width*p[nombre].total_temps, 100));
                       scene->addItem(txtitema);

                       ui->label_4->setText("le temps de rotation moyenne:" + QString::number(x1));
                        ui->label_5->setText("le temps d'attente moyenne:" + QString::number(y1));

                       condition=0;
           afficher(nombre);
           QMessageBox::information(this,"reussi","fin de la simulation!");




    }

    //#####################################################################//
    if(ch==3)
    {
        int i,limit,nextval,m,min;
                    p[0].temps_attente=p[0].temps_rotation=0;

                    limit=p[1].temps_arrive;
                    for(i=1;i<=nombre;i++)
                    {
                        limit+=p[i].temps_traitement;
                    }

                    for(i=1;i<=nombre;i++)
                    {
                        p1[i]=p[i];
                    }

                    nextval=p[1].temps_arrive;
                    m=1;
                    //pre_min=1;
                    QString temp_str=QString::number(p[1].temps_arrive);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF(-200,100));
                    scene->addItem(txtitem);

                    do{
                        min=9999;
                        for(i=1;p[i].temps_arrive<=nextval && i<=nombre;i++)
                        {
                            if(p[i].temps_traitement<min && p[i].temps_traitement>0)
                            {
                                m=i;
                                min=p[i].temps_traitement;
                            }
                        }
                        nextval+=1;
                        p[m].temps_traitement=p[m].temps_traitement-1;
                        QBrush color_brush(QColor(p[m].coleur));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle=scene->addRect(-200+Rectangle_Width*nextval,0,Rectangle_Width,Rectangle_Height,blackpen,color_brush);
                        QString temp_str=QString::number(nextval);
                        QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                        txtitem->setPos(QPointF(-200+Rectangle_Width*nextval+1, 100));
                        scene->addItem(txtitem);
                        QElapsedTimer t;
                        t.start();
                        while(t.elapsed() < 2500)
                        {
                            QCoreApplication::processEvents();
                        }

                        //pre_min=m;
                        if (p[m].temps_traitement == 0)
                        {
                            p[m].total_temps = nextval;
                            p[m].temps_rotation = p[m].total_temps - p[m].temps_arrive;
                            p[m].temps_attente = p[m].temps_rotation - p1[m].temps_traitement;
                             //p[m].rendement = p1[m].temps_traitement / float(p[i].temps_rotation);
                            //p[0].temps_rotation += p[m].temps_rotation;
                            total_tempsrotation +=p[i].temps_rotation;
                            //p[0].temps_attente += p[m].temps_attente;
                            total_tempsattente +=p[i].temps_attente;
                        }

                        //pre_min=m;
                    }while(nextval<limit);
                    for(int i=0;i<=nombre;i++)
                    {
                         p[i].rendement = p1[i].temps_traitement / float(p[i].temps_rotation);
                         total_tempsrotation +=p[i].temps_rotation;
                         total_tempsattente +=p[i].temps_attente;


                    }
                    float x1 = total_tempsrotation/ nombre;
                    float y1 = total_tempsattente/ nombre;

                    ui->label_4->setText("le temps de rotation moyenne:" + QString::number(x1));
                     ui->label_5->setText("le temps d'attente moyenne:" + QString::number(y1));

                    condition=0;


                    afficher(nombre);
                    QMessageBox::information(this,"reussi","fin de la simulation!");


    }
    if(ch==4)
    {
        int i,m,nextval,nextarr;


        QString hi = ui->lineEdit_2->text();
        time_slice1 = hi.toInt();

                    for(i=1;i<=nombre;i++)
                    {
                        p1[i]=p[i];
                    }
                    nextval=p[0].temps_arrive;
                    for(i=1;i<=nombre,p[i].temps_arrive<=nextval;i++)
                    {
                        q1.push(p[i].id);
                    }
                    nextarr=p[0].temps_arrive;
                    //p[1].ft=p[1].bt;
                    while(!q1.empty())
                    {
                        m=q1.front();
                        q1.pop();
                        if(p[m].temps_traitement>=time_slice1)
                        {
                            QBrush color_brush(QColor(p[m].coleur));
                            QPen blackpen(Qt::black);
                            blackpen.setWidth(1);
                            rectangle=scene->addRect(-200+Rectangle_Width*nextval,0,Rectangle_Width*time_slice1,Rectangle_Height,blackpen,color_brush);
                            QString temp_str=QString::number(nextval);
                            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                            txtitem->setPos(QPointF(-200+Rectangle_Width*nextval, 100));
                            scene->addItem(txtitem);

                            nextval=nextval+time_slice1;
                        }
                        else
                        {
                            QBrush color_brush(QColor(p[m].coleur));
                            QPen blackpen(Qt::black);
                            blackpen.setWidth(1);
                            rectangle=scene->addRect(-200+Rectangle_Width*nextval,0,Rectangle_Width*p[m].temps_traitement,Rectangle_Height,blackpen,color_brush);
                            QString temp_str=QString::number(nextval);
                            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                            txtitem->setPos(QPointF(-200+Rectangle_Width*nextval, 100));
                            scene->addItem(txtitem);

                            nextval=nextval+p[m].temps_traitement;
                        }



                        p[m].temps_traitement=p[m].temps_traitement-time_slice1;

                        if (nextval < nextarr)
                        {
                            if (p[m].temps_traitement>0)
                            {
                                q1.push(m);
                            }
                            if (p1[m].temps_traitement <= 0)
                            {
                                p[m].total_temps = nextval;
                            }
                        }
                        else
                        {
                            while (i <= nombre && p1[i].temps_arrive <= nextval)
                            {
                                q1.push(p[i].id);
                                i++;
                            }
                            if (i <= nombre)
                                nextarr = p[i].temps_arrive;
                            if (p[m].temps_traitement>0)
                                q1.push(m);
                            if (p[m].temps_traitement <= 0)
                                p[m].total_temps = nextval;
                        }
                        QElapsedTimer t;
                        t.start();
                        while(t.elapsed() < 2500)
                        {
                            QCoreApplication::processEvents();
                        }

                    }
                    QString temp_str=QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF(-200+Rectangle_Width*nextval, 100));
                    scene->addItem(txtitem);

                    condition=0;


                        for(i=0;i<=nombre;i++)
                        {
                            p[i].temps_rotation=p[i].total_temps-p1[i].temps_arrive;
                            p[i].temps_attente=p[i].temps_rotation-p1[i].temps_traitement;
                            p[i].rendement = p1[i].temps_traitement / float(p[i].temps_rotation);
                            total_tempsrotation +=p[i].temps_rotation;

                            total_tempsattente +=p[i].temps_attente;


                        }

                        float x1 = total_tempsrotation/ nombre;
                        float y1 = total_tempsattente/ nombre;

                        ui->label_4->setText("le temps de rotation moyenne:" + QString::number(x1));
                         ui->label_5->setText("le temps d'attente moyenne:" + QString::number(y1));


                    afficher(nombre);
                    QMessageBox::information(this,"reussi","fin de la simulation!");


    }




}

//###############################################################################""//




    //##########################################################################################//

    else
       {
           QMessageBox::warning(this,"Warning","veuiller cliquer sur le bouton enregistrer les donnes!");
       }
}
//###############################################################################################//


void Dialog::on_pushButton_2_clicked()
{
    scene->clear();
    ui->label_4->clear();
    ui->label_5->clear();

    total_tempsrotation=0;
    total_tempsattente=0;
    total_rendement=0;

    for(int i=0;i<=nombre;i++)
    {
        p[i].temps_arrive=0;
        p[i].temps_traitement=0;
        p[i].coleur="";
        p[i].total_temps=0;
        p[i].id=0;
        p[i].temps_rotation=0;
        p[i].temps_attente=0;

    }
    QStringList header;
    header<<"ID"<<"temps achevement"<<"temps rotation"<<"temps attente";
    ui->tableWidget_2->setRowCount(nombre);
    ui->tableWidget_2->setColumnCount(4);
    ui->tableWidget_2->setHorizontalHeaderLabels(header);
    ui->tableWidget_2->setHorizontalHeaderLabels(header);
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:yellow;}");
    ui->tableWidget_2->verticalHeader()->setStyleSheet("QHeaderView::section{background:red;}");
}





void Dialog::on_pushButton_4_clicked()
{
    close();
}

