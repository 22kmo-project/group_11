#ifndef BANKWINDOW_H
#define BANKWINDOW_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <payment.h>
#include "withdrawal.h"
#include "transactions.h"

namespace Ui {
class BankWindow;
}

class BankWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BankWindow(QString card_number,QWidget *parent = nullptr);
    ~BankWindow();

    const QString &getWebToken() const;

    void setWebToken(const QByteArray &newWebToken);

private slots:
    void balanceSlot(QNetworkReply *reply);

    void on_NostoPankkibtn_clicked();
    void on_MaksuPankkibtn_clicked();
    void on_TransBankbtn_clicked();
    void on_NostoCreditbtn_clicked();
    void on_MaksuCreditbtn_clicked();
    void on_TransCreditbtn_clicked();

private:
    Ui::BankWindow *ui;
    QByteArray webToken;
    QString myBankCard;
    QString idbank_account;
    QString creditacc;

    QNetworkAccessManager *bankManager;
    QNetworkAccessManager *balanceManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // BANKWINDOW_H
