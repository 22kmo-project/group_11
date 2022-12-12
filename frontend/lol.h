#ifndef LOL_H
#define LOL_H

#include <QDialog>

namespace Ui {
class lol;
}

class lol : public QDialog
{
    Q_OBJECT

public:
    explicit lol(QWidget *parent = nullptr);
    ~lol();

private:
    Ui::lol *ui;
};

#endif // LOL_H
