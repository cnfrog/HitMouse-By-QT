#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"


#include <QDebug>
#include <QList>
#include <QTableWidgetItem>
#include <QFile>
#include <QByteArray>


extern QList<pppp> list;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    QStringList headers;
    headers << "id"  << "score" << "level";
    ui->tableWidget->setHorizontalHeaderLabels(headers);




}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_1_clicked()
{

    sortAndPrint(1);

}

void Dialog::on_pushButton_2_clicked()
{

        sortAndPrint(2);
}

void Dialog::on_pushButton_3_clicked()
{

       sortAndPrint(3);
}

void Dialog::on_pushButton_4_clicked()
{
    int i=0;
    ui->tableWidget->selectAll();
    Clear();
    for (i=0;i< list.size();i++){
      ui->tableWidget->insertRow(0);
      ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString(" ")));
      ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString(" ")));
      ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString(" ")));
    }
    for(i = 0 ; i< list.size();i++)
    {
        QString qId = list.at(i).id;
        QString qScore = QString::number(list.at(i).score);
        QString qLevel = QString::number(list.at(i).level);
        ui->tableWidget->item(i,0)->setText(qId);
        ui->tableWidget->item(i,1)->setText(qScore);
        ui->tableWidget->item(i,2)->setText(qLevel);
    }
}

void Dialog::sortAndPrint(int level)
{
    int i=0;
    ui->tableWidget->selectAll();
    Clear();
    QList<dddd> blist = BubbleSort(level);
    int n = blist.size() >= 3 ? 3:blist.size();
    for (i=0;i< n;i++){
      ui->tableWidget->insertRow(0);
      ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString(" ")));
      ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString(" ")));
      ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString(" ")));
     }
    for(i = 0 ; i < n;i++)
    {
        QString qId = blist.at(i).id;
        QString qScore = QString::number(blist.at(i).score);
        QString qLevel = QString::number(blist.at(i).level);
        ui->tableWidget->item(i,0)->setText(qId);
        ui->tableWidget->item(i,1)->setText(qScore);
        ui->tableWidget->item(i,2)->setText(qLevel);
    }


}
QList<dddd> Dialog::BubbleSort(int level)
{
    QList<dddd> blist;
    dddd temp;
    int i,j;
    dddd dd;
    for(i=0;i<list.size();i++)
    {
        if(list.at(i).level==level)
        {
            dd.id = list.at(i).id;
            dd.level = list.at(i).level;
            dd.score = list.at(i).score;
            blist.append(dd);
        }

    }


    for(i=0;i<blist.size()-1;i++)
    {
        for(j=i+1;j<blist.size();j++){
            if(blist.at(i).score < blist.at(j).score){
                temp = blist[i];
                blist[i] = blist[j];
                blist[j] = temp;
            }
        }
    }
    return blist;
}
void Dialog::Clear()
{
    int iLen = ui->tableWidget->rowCount();
    for(int i=0;i<iLen;i++)
    {
        ui->tableWidget->removeRow(0);
    }

}


