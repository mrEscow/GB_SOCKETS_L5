#include "Request_Gun.h"
//--------------------------------------------------------------------------------------------------
//class TCP_Server{
//private:
//    boost::asio::io_context& io_context_;
//    tcp::acceptor acceptor_;

//public:
//    TCP_Server(boost::asio::io_context& io_context):
//        io_context_(io_context),
//        acceptor_(io_context, tcp::endpoint(tcp::v4(), TimeServer::Get_Port()))
//    {
//        start_accept();
//    }

//private:
//    // Метод start_accept() создаёт сокет и выполняет асинхронный `accept()`,
//    // при соединении.
//    void start_accept()
//    {
//        TcpConnection::pointer new_connection = TcpConnection::create(io_context_);


//        acceptor_.async_accept(new_connection->socket(),
//        [this, new_connection] (const boost::system::error_code& error){
//                this->handle_accept(new_connection, error);
//            }
//        );
//    }

//    // Метод handle_accept() вызывается, когда асинхронный accept,
//    // инициированный в start_accept() завершается.
//    // Она выполняет обработку запроса клиента и запуск нового акцептора.
//    void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error){
//        if (!error){
//            new_connection->start();
//        }
//        start_accept();
//    }

//};
/*
TimeServer::TimeServer(const uint16_t &echo_port) : echo_port_(echo_port)
{

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

};
*/

//using boost::asio::ip::tcp;

struct client
{
    boost::asio::ip::tcp::socket sock;
    char buff[1024]; // each msg is at maximum this size
    int already_read; // how much have we already read?
};

std::vector<client> clients;


//--------------------------------------------------------------------------------------------------
Request_Gun::Request_Gun(uint16_t bullets)
{
    //for(uint16_t i = 0; i < bullets; i++)
        //sockets.push_back(i);
        //boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string("127.0.0.1"), 8001);

    //boost::asio::io_service service;
    //boost::asio::ip::udp::socket sock(service);
    //sock.set_option(boost::asio::ip::udp::socket::reuse_address(true));

    //using boost::asio::ip; //::tcp;


    using namespace boost::asio;


    io_service service;


    ip::udp::socket sock(service);


    //boost::asio::ip::udp::endpoint sender_ep;


    //char buff[512];




//    boost::asio::ip::udp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 8001);
//    sock.open(ep.protocol());
//    sock.set_option(boost::asio::ip::udp::socket::reuse_address(true));
//    sock.bind(ep);


    //ip::udp::socket sock(service);
    sock.open(ip::udp::v4());


    boost::asio::ip::udp::endpoint receiver_ep;//("87.248.112.181", 80);

    receiver_ep.address(boost::asio::ip::address::from_string("127.0.0.1"));
    receiver_ep.port(1989);



    std::future<void> f = std::async([&](){
        while(true){
            sock.send_to(buffer("Hello World!\n"), receiver_ep);
        }
        sock.close();
    });


    //f.get();


    service.run();
}


//--------------------------------------------------------------------------------------------------
//std::string make_daytime_string()
//{
//    using namespace std; // time_t, time и ctime;
//    time_t now = time(0);
//    return ctime(&now);
//}
//--------------------------------------------------------------------------------------------------
// Указатель shared_ptr и enable_shared_from_this нужны для того,
// чтобы сохранить объект tcp_connection до завершения выполнения операции.
//class TcpConnection2 : public std::enable_shared_from_this<TcpConnection2>
//{
//private:
//    tcp::socket socket_;
//    std::string message_;
//public:
//    // singolton
//    typedef std::shared_ptr<TcpConnection2> pointer;
//    static pointer create(boost::asio::io_context& io_context)
//    {
//        return pointer(new TcpConnection2(io_context));
//    }

//    tcp::socket& socket()
//    {
//        return socket_;
//    }

//    // В методе start(), вызывается asio::async_write(), отправляющий данные
//    // клиенту.
//    // Здесь используется asio::async_write(), вместо
//    // ip::tcp::socket::async_write_some(), чтобы весь блок данных был гарантированно
//    // отправлен.
//    void start()
//    {
//        // The data to be sent is stored in the class member message_ as we
//        // need to keep the data valid until the asynchronous operation is complete.
//        // Данные, подлежащие отправке, хранятся в члене класса message_, поскольку нам
//        // необходимо сохранить данные действительными до завершения асинхронной операции.
//        message_ = make_daytime_string();
//        auto s = shared_from_this();
//        // Здесь вместо boost::bind используется std::bind, чтобы уменьшить
//        // число зависимостей от Boost.
//        // Он не работает с плейсхолдерами из Boost.
//        // В комментариях указаны альтернативные плейсхолдеры.
//        boost::asio::async_write(socket_, boost::asio::buffer(message_),
//        // handle_write() выполнит обработку запроса клиента.
//        [s] (const boost::system::error_code& error, size_t bytes_transferred){
//                s->handle_write(error, bytes_transferred);
//            }
//        );
//    }
//private:
//    TcpConnection2(boost::asio::io_context& io_context)
//    : socket_(io_context)
//    {
//    }

//    void handle_write(const boost::system::error_code& /*error*/, size_t bytes_transferred){
//        std::cout << "Bytes transferred: " << bytes_transferred <<
//        std::endl;
//    }

//};

////--------------------------------------------------------------------------------------------------
//class TCP_Server{
//private:
//    boost::asio::io_context& io_context_;
//    //tcp::acceptor acceptor_;

//public:
//    TCP_Server(boost::asio::io_context& io_context):
//        io_context_(io_context)
//        //,
//        //acceptor_(io_context, tcp::endpoint(tcp::v4(), 1000))
//    {
//        start_accept();
//    }

//private:
//    // Метод start_accept() создаёт сокет и выполняет асинхронный `accept()`,
//    // при соединении.
//    void start_accept()
//    {
//        TcpConnection2::pointer new_connection = TcpConnection2::create(io_context_);


//        //acceptor_.async_accept(new_connection->socket(),
//        //[this, new_connection] (const boost::system::error_code& error){
//        //        this->handle_accept(new_connection, error);
//        //    }
//        //);
//    }

//    // Метод handle_accept() вызывается, когда асинхронный accept,
//    // инициированный в start_accept() завершается.
//    // Она выполняет обработку запроса клиента и запуск нового акцептора.
//    void handle_accept(TcpConnection2::pointer new_connection, const boost::system::error_code& error){
//        if (!error){
//            new_connection->start();
//        }
//        start_accept();
//    }

//};
