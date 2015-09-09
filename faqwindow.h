#ifndef FAQ_H
#define FAQ_H

#include <QWidget>

namespace Ui {
class FAQ;
}

class FAQ : public QWidget
{
    Q_OBJECT

public:
    explicit FAQ(QWidget *parent = 0);
    ~FAQ();

private:
    Ui::FAQ *ui;
};

#endif // FAQ_H
