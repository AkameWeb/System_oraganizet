#ifndef DIALOGPRINT_H
#define DIALOGPRINT_H

#include <QDialog>

namespace Ui {
class DialogPrint;
}

class DialogPrint : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPrint(QWidget *parent = nullptr);
    ~DialogPrint();

private:
    Ui::DialogPrint *ui;
};

#endif // DIALOGPRINT_H
