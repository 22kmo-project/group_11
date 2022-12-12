#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H
#include "bankwindow.h"
#include <QMainWindow>


#include <QDialog>

namespace Ui {
class withdrawal;
}

class withdrawal : public QDialog
{
    Q_OBJECT

public:
    explicit withdrawal(QString id,QWidget *parent = nullptr);
    ~withdrawal();

private slots:
    void on_closebtn_clicked();
    void withdrawSlot (QNetworkReply *reply);
    void on_btn20with_clicked();
    void withdraw(QString amount);

    void on_btn40with_clicked();

    void on_btn60with_clicked();

    void on_btn100with_clicked();

    void on_btn200with_clicked();

    void on_btn500with_clicked();

private:

    Ui::withdrawal *ui;
    QString bank_id;
    QNetworkAccessManager *withdrawManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // WITHDRAWAL_H
