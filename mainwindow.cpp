#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QRect>
#include <QPoint>
#include <QPixmap>
#include <QTime>
#include <QLabel>
#include <QtAlgorithms>
#include <QTableWidgetItem>
#include <QFile>
#include <QByteArray>
#include <QDir>
#include <QDesktopWidget>
#include <QRect>

int wz;
QList<pppp> list;
QString dbfile = "/root/mydata.db";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start = 0;
    ui->lcdNumber_3->display(1);
    creatDB();
    QDesktopWidget* pDw = QApplication::desktop();//获得桌面窗体
    QRect rect = pDw->screenGeometry();//获得分辨率
    this->move(rect.width()/4,rect.height()/4);

}
void MainWindow::init(int timerId1,int score1,int leftTime1,int start1,int level1)
{
    id =  ui->lineEdit->text();
    level = level1;

    if(id.size()==0 || id=="" ){
        QMessageBox::warning(this,QString::fromUtf8("提示"),QString::fromUtf8("用户名不能为空！"));
    }else{
    timerId = this->startTimer(timerId1);
    leftTimerId = this->startTimer(1000);
    score = score1;//分数
    leftTime = leftTime1;//倒计时
    start = start1;
    hampoint.setX(-80);
    hampoint.setY(0);
    ui->lcdNumber->display(score);
    ui->lcdNumber_3->display(level);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    QBrush brush;
    brush.setColor(QColor(180,228,196));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0,0,480,480);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawEllipse(35,60,80,30);
    painter.drawEllipse(195,60,80,30);
    painter.drawEllipse(355,60,80,30);
    painter.drawEllipse(35,200,80,30);
    painter.drawEllipse(195,200,80,30);
    painter.drawEllipse(355,200,80,30);
    painter.drawEllipse(35,340,80,30);
    painter.drawEllipse(195,340,80,30);
    painter.drawEllipse(355,340,80,30);
    QPixmap pixmap;
    if(pixmap.load("://image/hampic.png")&& start == 1)
        painter.drawPixmap(hampoint.x(),hampoint.y(),pixmap);
    if(start == 1) {
        ui->lineEdit->setEnabled(false);
        ui->pushButton->setEnabled(false);
        shengji();
    }
}
void MainWindow::shengji()
{
    if(level == 1 && leftTime==1 && score >=10 ){
        qDebug() << id << score << level;
        saveScore();
        init(800,0,45,1,2);
    }else if(level == 2 && leftTime==1 && score >= 15 ){
        qDebug() << id << score << level;
        saveScore();
        init(500,0,30,1,3);
    }
    if(leftTime==0 && start == 1 ){
        //game over
         killTimer(timerId);
         killTimer(leftTimerId);
         if(level == 3 && score >= 10)  {
             ui->info_label->setText(QString::fromUtf8("恭喜通关"));
         }
             else ui->info_label->setText("Game Over");
         saveScore();

         start = 0;
         ui->lineEdit->setEnabled(true);
         ui->pushButton->setEnabled(true);
    }
}

void MainWindow::timerEvent(QTimerEvent *event){
    if(event->timerId()==timerId){
        int pre_wz =wz;
        wz =(qrand()%9);
        if(pre_wz == wz)
            wz=((wz+4)%9);//前后两秒位置不一样
        switch(wz)
        {
          case 0:
              hampoint.setX(40);
              hampoint.setY(22);
              break;
          case 1:
              hampoint.setX(200);
              hampoint.setY(22);
              break;
          case 2:
              hampoint.setX(360);
              hampoint.setY(22);
              break;
          case 3:
              hampoint.setX(40);
              hampoint.setY(162);
              break;
          case 4:
              hampoint.setX(200);
              hampoint.setY(162);
              break;
          case 5:
              hampoint.setX(360);
              hampoint.setY(162);
              break;
          case 6:
              hampoint.setX(40);
              hampoint.setY(302);
              break;
          case 7:
              hampoint.setX(200);
              hampoint.setY(302);
              break;
          case 8:
              hampoint.setX(360);
              hampoint.setY(302);
              break;
        }
        this->update();
    }
    if(event->timerId()==leftTimerId){
        ui->lcdNumber_2->display(--leftTime);
    }


}
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton){
        xx=e->pos().x();
        yy=e->pos().y();
        if((qAbs(hampoint.x()-xx)<50) && (qAbs(hampoint.y()-yy)<80) && leftTime != 0){
            ui->lcdNumber->display(++score);
        }
        this->update();
    }
}



void MainWindow::closeEvent(QCloseEvent *e)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QString::fromUtf8("退出程序"),
                                       QString::fromUtf8("确认退出程序?"),
                                       QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::No) {
              e->ignore();  //忽略退出信号，程序继续运行
        }
        else if (button == QMessageBox::Yes) {
              e->accept();  //接受退出信号，程序退出
        }

}

void MainWindow::on_action_2_triggered()
{
    QMessageBox::StandardButton button;
       button = QMessageBox::question(this, QString::fromUtf8("退出程序"),
                                          QString::fromUtf8("确认退出程序?"),
                                          QMessageBox::Yes | QMessageBox::No);
           if (button == QMessageBox::No) {
           }
           else if (button == QMessageBox::Yes) {
                 qApp->quit();
    }
}

void MainWindow::on_action_3_triggered()
{
    init(1000,0,60,1,1);
    ui->info_label->setText("");
}

void MainWindow::on_pushButton_clicked()
{
   init(1000,0,60,1,1);
   ui->info_label->setText("");
}


void MainWindow::on_action_triggered()
{
    QList<pppp> qList;
    pppp user;
    QSqlDatabase db2;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db2 = QSqlDatabase::database("qt_sql_default_connection");
    else
        db2 = QSqlDatabase::addDatabase("QSQLITE");

    db2.setDatabaseName(dbfile);
    if(!db2.open()) //打开数据库
    {

    }
    QSqlQuery query1;
    query1.exec("select * from mytable");
    while(query1.next())
    {
    user.id = query1.value(0).toString();
    user.score =query1.value(1).toInt();
    user.level =query1.value(2).toInt();
    // qList << user;
     qList.prepend(user);
    }
    db2.close();
    list = qList;
    this->hide();
    dialog.setWindowTitle(QString::fromUtf8("分数统计"));
    dialog.show();
    dialog.exec();
    this->show();
}


 void MainWindow::saveScore()
 {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbfile);
    if(!db.open()) //打开数据库
    {

    }
    QSqlQuery query(db);
    qDebug() << userIsExists();
    if(userIsExists()==1){
       //更新表id的score,当前分数最大
        QString update_sql = "update mytable set score = :score where id = :id and level = :level";
        query.prepare(update_sql);
        query.bindValue(0, score);
        query.bindValue(1, id);
        query.bindValue(2, level);
        if(query.exec())  qDebug()<< QString::fromUtf8("更新表中数据成功");;
    }else if(userIsExists()==3){
        qDebug()<<QString::fromUtf8("插入表中数据");
        query.prepare("insert into mytable values(:id,:score,:level)");
        query.bindValue(0, id);
        query.bindValue(1, score);
        query.bindValue(2, level);
        query.exec();
    }
    db.close();
}
void MainWindow::creatDB()
{
    QFile file(dbfile);
    if(!file.exists()){
         QSqlDatabase db2;
        if(QSqlDatabase::contains("qt_sql_default_connection"))
          db2 = QSqlDatabase::database("qt_sql_default_connection");
        else
          db2 = QSqlDatabase::addDatabase("QSQLITE");  //第二次按按钮会多次装入同一驱动出现错误，因此加个判断，或者把这些语句放入构造函数也可避免多次运行，
          db2.setDatabaseName(dbfile);
        if(!db2.open()) //打开数据库
        {
           qDebug()<<"error";
        }
        QSqlQuery query;
        query.exec("create table mytable(id varchar(20),score int,level int)");
        db2.close();
    }
}
int MainWindow::userIsExists()
{
    QString uid;
    int uscore,ulevel;
    QSqlQuery query1;
    query1.exec("select * from mytable");
    while(query1.next())
    {
        uid = query1.value(0).toString();
        uscore = query1.value(1).toInt();
        ulevel = query1.value(2).toInt();
        if(uid == id && ulevel == level && uscore <= score) return 1;//保存最大分数
        else if(uid == id && ulevel == level && uscore > score) return 2;//无需保存
    }
    return 3;
}





