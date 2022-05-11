#include "TimeServer.h"
/*
    try
    {
        // io_context предоставляет службы ввода-вывода, которые будет
        // использовать сервер, такие как сокеты.
        boost::asio::io_context io_context;
        TCP_Server server(io_context);


        // Запуск асинхронных операций.
        io_context.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
*/

#include <QDebug>

std::string make_daytime_string()
{
    using namespace std; // time_t, time и ctime;
    time_t now = time(0);
    return ctime(&now);
}
//--------------------------------------------------------------------------------------------------
TcpConnection::TcpConnection(boost::asio::io_context& io_context)
: socket_(io_context)
{
}

TcpConnection::pointer TcpConnection::create(boost::asio::io_context& io_context)
{
    return pointer(new TcpConnection(io_context));
}

tcp::socket& TcpConnection::socket()
{
    return socket_;
}

    // В методе start(), вызывается asio::async_write(), отправляющий данные
    // клиенту.
    // Здесь используется asio::async_write(), вместо
    // ip::tcp::socket::async_write_some(), чтобы весь блок данных был гарантированно
    // отправлен.

void TcpConnection::start()
{

    // Данные, подлежащие отправке, хранятся в члене класса message_, поскольку нам
    // необходимо сохранить данные действительными до завершения асинхронной операции.

    message_ = make_daytime_string();
    auto s = shared_from_this();

    // Здесь вместо boost::bind используется std::bind, чтобы уменьшить
    // число зависимостей от Boost.
    // Он не работает с плейсхолдерами из Boost.
    // В комментариях указаны альтернативные плейсхолдеры.

    // WTF ^^^

    // Здесь используется asio::async_write(), вместо ip::tcp::socket::async_write_some(),
    // чтобы весь блок данных был гарантированно отправлен.


    boost::asio::async_write(socket_, boost::asio::buffer(message_),

    // handle_write() выполнит обработку запроса клиента.
    [s] (const boost::system::error_code& error, size_t bytes_transferred){
            s->handle_write(error, bytes_transferred);
        }
    );
}

void TcpConnection::handle_write(const boost::system::error_code& /*error*/, size_t bytes_transferred){
    std::cout << "Bytes transferred: " << bytes_transferred <<
    std::endl;
}

//--------------------------------------------------------------------------------------------------
TCP_Server::TCP_Server(boost::asio::io_context& io_context, uint16_t port, QObject *parent)
    :
    QObject(parent),
    io_context_(io_context),
    port_(port),
    acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        start_accept();
        qDebug()<< "Create TCP_Server";
    };

    // Метод start_accept() создаёт сокет и выполняет асинхронный `accept()`,
    // при соединении.

    void TCP_Server::start_accept()
    {
        TcpConnection::pointer new_connection = TcpConnection::create(io_context_);
        acceptor_.async_accept(new_connection->socket(),
        [this, new_connection] (const boost::system::error_code& error){
                this->handle_accept(new_connection, error);
            }
        );
    }

    // Метод handle_accept() вызывается, когда асинхронный accept,
    // инициированный в start_accept() завершается.
    // Она выполняет обработку запроса клиента и запуск нового акцептора.

void TCP_Server::handle_accept
    (TcpConnection::pointer new_connection, const boost::system::error_code& error){
        if (!error){
            new_connection->start();
        }

    start_accept();
}
