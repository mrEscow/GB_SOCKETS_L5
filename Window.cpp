#include "Window.h"
#include "ui_mainwindow.h"




Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{




    try
    {

        //--------------------

        QSpinBox* p_spinbox = new QSpinBox;
        p_spinbox->setFixedHeight(20);
        p_spinbox->setMaximum(TimeServerProtocol.Port.min);
        p_spinbox->setMaximum(TimeServerProtocol.Port.max);
        p_spinbox->setValue(TimeServerProtocol.Port.number);


        ui->setupUi(this);

        wgt = new QWidget(this);

        pbxLayout = new QHBoxLayout(wgt);

        label = new QLabel("TCP Time Server:     ");

        p_button_Start = new QPushButton("START");
        p_button_ReStart = new QPushButton("RESTART");
        p_button_Stop = new QPushButton("STOP");

        label2 = new QLabel("Port:");
        label2->setAlignment(Qt::AlignCenter);

        p_button_SetPort = new QPushButton("SET/RESTART");

        pbxLayout->addWidget(label,0);

        pbxLayout->addWidget(p_button_Start,3);
        pbxLayout->addWidget(p_button_ReStart,4);
        pbxLayout->addWidget(p_button_Stop,5);

        pbxLayout->addWidget(label2,7);
        pbxLayout->addWidget(p_spinbox,8);

        pbxLayout->addWidget(p_button_SetPort,9);

        wgt->resize(700,200);

        wgt->setLayout(pbxLayout);

        //--------------------
    }
    catch (const std::exception& e)
    {
        //std::cerr << e.what() << std::endl;
    }

}

Window::~Window()
{
    delete ui;
}

