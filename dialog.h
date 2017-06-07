#ifndef DIALOG_H
#define DIALOG_H


#include <QDialog>
#include <QList>

namespace Ui {
    class Dialog;
}


typedef struct Bar {
    QString id;
    int level;
    int score;
  }dddd;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void sortAndPrint(int level);
    QList<dddd> BubbleSort(int level);
    void Clear();

private:
    Ui::Dialog *ui;

private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // DIALOG_H
