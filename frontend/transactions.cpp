#include "transactions.h"
#include "ui_transactions.h"
#include "bankwindow.h"
#include "ui_bankwindow.h"
#include "mainwindow.h"

transactions::transactions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::transactions)
{
    ui->setupUi(this);
}

transactions::~transactions()
{
    delete ui;
}

void transactions::on_closebtn_clicked()
{

}

