#include "lol.h"
#include "ui_lol.h"

lol::lol(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lol)
{
    ui->setupUi(this);
}

lol::~lol()
{
    delete ui;
}
