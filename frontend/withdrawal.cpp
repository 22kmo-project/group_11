#include "withdrawal.h"
#include "ui_withdrawal.h"
#include "bankwindow.h"
#include "ui_bankwindow.h"
#include "mainwindow.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

withdrawal::withdrawal(QString id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::withdrawal)
{

    ui->setupUi(this);
    bank_id = id;

    qDebug()<<id;
}

withdrawal::~withdrawal()
{
    delete ui;
}

void withdrawal::on_closebtn_clicked()
{
    hide();
}


void withdrawal::withdraw(QString amount)
{
    QJsonObject jsonObj;
    QString site_url=MyURL::getBaseUrl()+"/bank_operations/withdraw/"+bank_id;
    QNetworkRequest request((site_url));
    jsonObj.insert("amount",amount);


    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    withdrawManager = new QNetworkAccessManager(this);
    connect(withdrawManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(withdrawSlot(QNetworkReply*)));

    reply = withdrawManager->post(request, QJsonDocument(jsonObj).toJson());
}

void withdrawal::withdrawSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    int test=QString::compare(response_data,"false");
    int test2=QString::compare(response_data,"Not enough balance");
    qDebug()<<response_data;
    if(response_data.length()==0){
        ui->labelInfo->setText("Palvelin ei vastaa");
    }
    else{
        if(test==0){

            ui->labelInfo->setText("Nosto ei onnistunut");
        }else if(test2==0) {
            ui->labelInfo->setText("Tilillä ei tarpeeksi rahaa");
        }else {
            ui->labelInfo->setText("Nosto onnistui");
        }

}
}
void withdrawal::on_btn20with_clicked()
{
    withdraw("20");
}


void withdrawal::on_btn40with_clicked()
{
    withdraw("40");
}


void withdrawal::on_btn60with_clicked()
{
    withdraw("60");
}


void withdrawal::on_btn100with_clicked()
{
    withdraw("100");
}


void withdrawal::on_btn200with_clicked()
{
    withdraw("200");
}


void withdrawal::on_btn500with_clicked()
{
    withdraw("500");
}

