#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dialog.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QTime>
#include <QPoint>
#include <QList>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QModelIndexList>
#include <QModelIndex>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>

typedef struct BarAmount {
    QString id;
    int level;
    int score;
  }pppp;




namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    int timerId,leftTimerId;
    int leftTime;
    int score;
    int xx,yy;
    int level;
    int start;
    QString id;


    QPoint hampoint;
    void init(int timerId1,int score1,int leftTime1,int start1,int level1);
    void shengji();
    void saveScore();
    void creatDB();
    int userIsExists();
    void closeEvent(QCloseEvent *e);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *event);
    void mousePressEvent(QMouseEvent *e);



private:
    Ui::MainWindow *ui;
    Dialog dialog;

private slots:

    void on_action_triggered();
    void on_pushButton_clicked();
    void on_action_2_triggered();
    void on_action_3_triggered();
};

#endif // MAINWINDOW_H
