#include "withdrawal.h"
#include "ui_withdrawal.h"
#include "bankwindow.h"
#include "ui_bankwindow.h"
#include "mainwindow.h"

withdrawal::withdrawal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::withdrawal)
{
    ui->setupUi(this);
}

withdrawal::~withdrawal()
{
    delete ui;
}

void withdrawal::on_closebtn_clicked()
{

}

