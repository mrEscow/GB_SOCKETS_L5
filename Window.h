#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>



#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>

#include <thread>

#include "Protocol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();


private:
    Ui::MainWindow *ui;

    QLabel *label;
    QLabel *label2;

    QWidget *wgt;
    QHBoxLayout* pbxLayout;

    QPushButton* p_button_Start;
    QPushButton* p_button_ReStart;
    QPushButton* p_button_Stop;
    QPushButton* p_button_SetPort;



};
#endif // WINDOW_H
