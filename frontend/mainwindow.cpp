#include "mainwindow.h"
#include "bankwindow.h"
#include "ui_mainwindow.h"
#include "myurl.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

//destroyataan pointterit
MainWindow::~MainWindow()
{
    delete ui;
    delete objectBankWindow;

}

//logini
void MainWindow::on_btnLogin_clicked()
{
    bankcard=ui->textBankCard->text();
    QString pincode=ui->textPinCode->text();

    QJsonObject jsonObj;
    jsonObj.insert("card_number",bankcard);
    jsonObj.insert("pin_code",pincode);

    QString site_url=MyURL::getBaseUrl()+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());

}


//loginin vastaus
void MainWindow::loginSlot(QNetworkReply *reply)
{

    response_data=reply->readAll();
    qDebug()<<response_data;
    int test=QString::compare(response_data,"false");
    qDebug()<<test;

    if(response_data.length()==0){
        ui->labelInfo->setText("Palvelin ei vastaa");
    }
    else {
        if(QString::compare(response_data,"-4078")==0){
            ui->labelInfo->setText("Virhe tietokannassa");
        }
        else{
            if(test==0){
                ui->textBankCard->clear();
                ui->textPinCode->clear();
                ui->labelInfo->setText("Tunnus ja salasana eivät täsmää");
            }
            else {
                objectBankWindow=new BankWindow(bankcard);
                objectBankWindow->setWebToken("Bearer "+response_data);
                objectBankWindow->show();
                hide();             // hides login window after succesfull login into bank
            }
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();



}
