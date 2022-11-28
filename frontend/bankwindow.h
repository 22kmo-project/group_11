#ifndef BANKWINDOW_H
#define BANKWINDOW_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

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
    void on_btnGrades_clicked();
    void gradeSlot(QNetworkReply *reply);
    void dataSlot(QNetworkReply *reply);

    void on_btnMyData_clicked();

private:
    Ui::BankWindow *ui;
    QByteArray webToken;
    QString myBankCard;

    //QNetworkAccessManager *gradeManager;
    //QNetworkAccessManager *dataManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // BANKWINDOW_H
