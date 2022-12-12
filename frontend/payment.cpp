#include "payment.h"
#include "ui_payment.h"
#include "bankwindow.h"
#include "ui_bankwindow.h"
#include "mainwindow.h"





payment::payment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::payment)
{
    ui->setupUi(this);
}

payment::~payment()
{
    delete ui;
}

void payment::on_closebtn_clicked()
{

}

