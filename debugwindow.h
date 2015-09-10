#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QWidget>

namespace Ui {
class DebugWindow;
}

class DebugWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DebugWindow(QWidget *parent = 0);
    ~DebugWindow();

private slots:
    void on_updateButton_clicked();

private:
    Ui::DebugWindow *ui;
    void updateVariables();
};

#endif // DEBUGWINDOW_H
