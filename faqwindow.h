#ifndef FAQWINDOW_H
#define FAQWINDOW_H

#include <QWidget>

namespace Ui {
class FAQWindow;
}

class FAQWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FAQWindow(QWidget *parent = 0);
    ~FAQWindow();

private:
    Ui::FAQWindow *ui;
};

#endif // FAQWINDOW_H
