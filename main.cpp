//

#include <QApplication>



/*
.Переработайте TCP-сервер так, чтобы внутри потоков обрабатывающих запросы клиента,
использовался Asio, либо Boost.Asio, т.е. работа с клиентскими запросами внутри потока
велась асинхронно. В итоге, каждый поток сервера мог обрабатывать несколько клиентов в
асинхронном режиме. Будет полезно совместить в одном приложении такой сервер и
возможность отдачи файла по частям из задания 1.
*/

#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>

#include "Protocol.h"

#include "Window.h"
#include "TimeServer.h"
#include "TimeClient.h".h"
#include "Request_Gun.h"


//--------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::thread *TRD_For_Server;
    std::thread *TRD_For_Client;
    std::thread *TRD_For_Window;

    Window w;

    TCP_Server *time_server;
    TCP_Client *time_client;

    TRD_For_Server = new std::thread([&](){
        qDebug()<<"start server boost";
        boost::asio::io_context IO_context_TCP_Time_Server;
        qDebug()<<"boost::asio::io_context IO_context_TCP_Time_Server";
        time_server = new  TCP_Server(IO_context_TCP_Time_Server, TimeServerProtocol.Port.number);
        qDebug()<<"time_server = new  TCP_Server(IO_context_TCP_Time_Server, TimeServerProtocol.Port.number)";

        qDebug()<<"IO_context_TCP_Time_Server.run() START";
        IO_context_TCP_Time_Server.run();
        qDebug()<<"IO_context_TCP_Time_Server.run() STOP";
    });
    qDebug()<<"TRD_For_Server->detach(); Start";
    TRD_For_Server->detach();

    //Request_Gun{47};

    TRD_For_Client = new std::thread([&](){
        qDebug()<<"start client boost";
        boost::asio::io_context IO_context_TCP_Time_Client;
        qDebug()<<"boost::asio::io_context IO_context_TCP_Time_Client";
        time_client = new  TCP_Client(IO_context_TCP_Time_Client, TimeServerProtocol);
        qDebug()<<"time_client = new  TCP_Client(IO_context_TCP_Time_Client, TimeServerProtocol.Port.number)";

        qDebug()<<"IO_context_TCP_Time_Client.run() START";
        IO_context_TCP_Time_Client.run();
        qDebug()<<"IO_context_TCP_Time_Client.run() STOP";
    });
    qDebug()<<"TRD_For_Client->detach(); Start";
    TRD_For_Client->detach();

    //TRD_For_Window = new std::thread([&](){
        qDebug()<<"start Window";

        qDebug()<<"start Window Show()";
        w.show();
        qDebug()<<"stop Window";
    //});
    qDebug()<<"TRD_For_Window->detach() Start";
    //TRD_For_Window->detach();

    qDebug()<<"a.exec() in main,cpp";

    //connect(w,SIGNAL(),time_server,SLOT());
    return a.exec();
}
//--------------------------------------------------------------------------------------------------
