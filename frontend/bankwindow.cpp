#include "bankwindow.h"
#include "qdebug.h"
#include "ui_bankwindow.h"

#include <myurl.h>

BankWindow::BankWindow(QString bankcard, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankWindow)
{
    ui->setupUi(this);
    ui->labelCard->setText(bankcard);
    myBankCard=bankcard;
}

BankWindow::~BankWindow()
{
    delete ui;
}


void BankWindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}
