#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "bankwindow.h"

#include <QDialog>

namespace Ui {
class transactions;
}

class transactions : public QDialog
{
    Q_OBJECT

public:
    explicit transactions(QWidget *parent = nullptr);
    ~transactions();

private slots:
    void on_closebtn_clicked();

private:
    Ui::transactions *ui;
};

#endif // TRANSACTIONS_H
