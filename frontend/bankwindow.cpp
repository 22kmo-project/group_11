#include "bankwindow.h"
#include "ui_bankwindow.h"
#include "myurl.h"
#include <QDebug>
#include "payment.h"
#include "ui_payment.h"

BankWindow::BankWindow(QString bankcard, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankWindow)
{
    ui->setupUi(this);  
    ui->UserName->setText(bankcard);        //display bankcard info in lineEdit
    myBankCard=bankcard;


    QString site_url=MyURL::getBaseUrl()+"/bank_account/";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    bankManager = new QNetworkAccessManager(this);
    connect(bankManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(balanceSlot(QNetworkReply*)));
    reply = bankManager->get(request);

}

BankWindow::~BankWindow()
{
    delete ui;

}

void BankWindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void BankWindow::balanceSlot(QNetworkReply *reply)
{

    //get function to fetch balance from backend
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString balance="";
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_object = value.toObject();
        balance+=QString::number(json_object["balance"].toDouble());
    }
    //get function to fetch idbank_account from backend
    QString idbank_account="";
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_object1 = value.toObject();
        idbank_account+=QString::number(json_object1["idbank_account"].toInt());
    }
    //get function to fetch credit_limit from backend
    QString creditlimit="";
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        creditlimit+=QString::number(json_obj["credit_limit"].toDouble());
    }
    //get fuction to fetch credit_acc from backend
    QString creditacc="";
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        creditacc+=QString::number(json_obj[""].toDouble());
    }
    /*qDebug()<<idbank_account;
    qDebug()<<balance;
    qDebug()<<creditlimit;
    qDebug()<<creditacc;*/
    ui->Pankkitili_num->setText(idbank_account);
    ui->Saldo_pankTili->setText(balance);
    ui->Saldo_luotTili->setText(creditlimit);
    ui->LuottoTiliNum->setText(creditacc);

    //reply->deleteLater();
    //balanceManager->deleteLater();
}



//opens withdraw window from bank account
void BankWindow::on_NostoPankkibtn_clicked()
{
    withdrawal withwindow;
    withwindow.setModal(true);
    withwindow.exec();
    hide();
}

//opens transfer window from bank account
void BankWindow::on_MaksuPankkibtn_clicked()
{
    payment paymentwindow;
    paymentwindow.setModal(true);
    paymentwindow.exec();
    hide();
}

//opens transactions window from bank account
void BankWindow::on_TransBankbtn_clicked()
{
    transactions debitrans;
    debitrans.setModal(true);
    debitrans.exec();
    hide();
}

//opens withdraw window from credit account
void BankWindow::on_NostoCreditbtn_clicked()
{
    withdrawal creditwithwindow;
    creditwithwindow.setModal(true);
    creditwithwindow.exec();
    //hide();
}

//opens transfer window from credit account
void BankWindow::on_MaksuCreditbtn_clicked()
{
    payment creditpaywindow;
    creditpaywindow.setModal(true);
    creditpaywindow.exec();
    //hide();
}

//opens transactions window from credit account
void BankWindow::on_TransCreditbtn_clicked()
{
    transactions creditrans;
    creditrans.setModal(true);
    creditrans.exec();
    //hide();
}

