#ifndef PAYMENT_H
#define PAYMENT_H
#include "bankwindow.h"

#include <QDialog>

namespace Ui {
class payment;
}

class payment : public QDialog
{
    Q_OBJECT

public:
    explicit payment(QWidget *parent = nullptr);
    ~payment();

private slots:
    void on_closebtn_clicked();

private:
    Ui::payment *ui;
};

#endif // PAYMENT_H
