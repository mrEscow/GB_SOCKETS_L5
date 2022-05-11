#ifndef TIMESERVER_H
#define TIMESERVER_H
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
//--------------------------------------------------------------------------------------------------
#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>
//--------------------------------------------------------------------------------------------------
using boost::asio::ip::tcp;
//--------------------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
//--------------------------------------------------------------------------------------------------
class TCP_Time_Server_Interfase{
    virtual void Start() = 0;
    virtual void Restart() = 0;
    virtual void Stop() = 0;
    virtual void SetPort() = 0;
};
// Указатель shared_ptr и enable_shared_from_this нужны для того,
// чтобы сохранить объект tcp_connection до завершения выполнения операции.
class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
//private:
    tcp::socket socket_;
    std::string message_;
public:
    // singolton
    typedef std::shared_ptr<TcpConnection> pointer;
    static pointer create(boost::asio::io_context& io_context);


    tcp::socket& socket();

    // В методе start(), вызывается asio::async_write(), отправляющий данные клиенту.

    void start();

private:

    TcpConnection(boost::asio::io_context& io_context);

    void handle_write(const boost::system::error_code& /*error*/, size_t bytes_transferred);


};
//--------------------------------------------------------------------------------------------------
class TCP_Server : public QObject, public std::enable_shared_from_this<TcpConnection>
{
    Q_OBJECT

private:

    boost::asio::io_context &io_context_;
    uint16_t port_;
    tcp::acceptor acceptor_;

public:

    TCP_Server(boost::asio::io_context& io_context, uint16_t port, QObject *parent = nullptr );

private:

    // Метод start_accept() создаёт сокет и выполняет асинхронный `accept()`,
    // при соединении.

    void start_accept();

    // Метод handle_accept() вызывается, когда асинхронный accept,
    // инициированный в start_accept() завершается.
    // Она выполняет обработку запроса клиента и запуск нового акцептора.

    void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error);
};
//--------------------------------------------------------------------------------------------------



#endif // TIMESERVER_H
