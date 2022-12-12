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


    QString site_url=MyURL::getBaseUrl()+"/bank_operations/cardinfo/"+bankcard;
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
        QJsonObject json_object = json_doc.object();

        QString balance="";
        if(json_object["debit"].isObject()){
            QJsonObject debit = json_object["debit"].toObject();

            //fetch balance from backend
            balance=QString::number(debit["balance"].toDouble());

            //fetch idbank_account from backend
            idbank_account=QString::number(debit["idbank_account"].toInt());
        }

        QString creditlimit="";
        if(json_object["credit"].isObject()){
            QJsonObject credit = json_object["credit"].toObject();

            //fetch credit_limit from backend
            creditlimit=QString::number(credit["credit_limit"].toDouble());

            //fetch credit_acc from backend
            creditacc=QString::number(credit["idbank_account"].toDouble());
        }

        qDebug()<<idbank_account;
        qDebug()<<balance;
        qDebug()<<creditlimit;
        qDebug()<<creditacc;
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
    qDebug()<<idbank_account;
    withdrawal withwindow(idbank_account);
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
    withdrawal creditwithwindow(creditacc);
    creditwithwindow.setModal(true);
    creditwithwindow.exec();
    hide();
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

