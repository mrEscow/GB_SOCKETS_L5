#include "TimeClient.h"
/*
TimeClient::TimeClient() : QObject(this)
{

    try
    {
//          if (argc != 4)
//          {
//            std::cout << "Usage: sync_client <socks4server> <socks4port> <user>\n";
//            std::cout << "Examples:\n";
//            std::cout << "  sync_client 127.0.0.1 1080 chris\n";
//            std::cout << "  sync_client localhost socks chris\n";
//            return 1;
//          }

      boost::asio::io_service io_service;

      // Get a list of endpoints corresponding to the SOCKS 4 server name.
      tcp::resolver resolver(io_service);
      tcp::resolver::query socks_query("127.0.0.1", "1111");
      tcp::resolver::iterator endpoint_iterator = resolver.resolve(socks_query);

      // Try each endpoint until we successfully establish a connection to the
      // SOCKS 4 server.
      tcp::socket socket(io_service);
      boost::asio::connect(socket, endpoint_iterator);

      // Get an endpoint for the Boost website. This will be passed to the SOCKS
      // 4 server. Explicitly specify IPv4 since SOCKS 4 does not support IPv6.
      tcp::resolver::query http_query(tcp::v4(), "www.boost.org", "http");
      tcp::endpoint http_endpoint = *resolver.resolve(http_query);

      // Send the request to the SOCKS 4 server.
      socks4::request socks_request(
          socks4::request::connect, http_endpoint, "chris");
      boost::asio::write(socket, socks_request.buffers());

      // Receive a response from the SOCKS 4 server.
      socks4::reply socks_reply;
      boost::asio::read(socket, socks_reply.buffers());

      // Check whether we successfully negotiated with the SOCKS 4 server.
      if (!socks_reply.success())
      {
        std::cout << "Connection failed.\n";
        std::cout << "status = 0x" << std::hex << socks_reply.status();
        exit(1);
      }

//          // Form the HTTP request. We specify the "Connection: close" header so that
//          // the server will close the socket after transmitting the response. This
//          // will allow us to treat all data up until the EOF as the response.
//          std::string request =
//            "GET / HTTP/1.0\r\n"
//            "Host: www.boost.org\r\n"
//            "Accept: *//*\r\n"  // more / )))
//            "Connection: close\r\n\r\n";

//          // Send the HTTP request.
//          boost::asio::write(socket, boost::asio::buffer(request));

//          // Read until EOF, writing data to output as we go.
//          boost::array<char, 512> response;
//          boost::system::error_code error;
//          while (std::size_t s = socket.read_some(
//                boost::asio::buffer(response), error))
//            std::cout.write(response.data(), s);
//          if (error != boost::asio::error::eof)
//            throw boost::system::system_error(error);
    }
    catch (std::exception& e)
    {
      std::cout << "Exception: " << e.what() << "\n";
    }
};
*/

void TCP_Client::connect_handler( const boost::system::error_code & ec)
{
    //enum { max_msg = 1024 };
    //char read_buffer_[max_msg];
    // here we know we connected successfully
    // if ec indicates success


//    boost::system::error_code error;
//    sock_.read_some(boost::asio::buffer(read_buffer_), error);
    std::string message;
    while(true){
        if ( !ec){
            qDebug()  << "connect_handler connect_handler connect_handler connect_handler connect_handler";
            //do_write(message + "\n");
        }
        else{
            qDebug()  << "ec";
        }
    }

    //else stop();


}


TCP_Client::TCP_Client(boost::asio::io_context& io_context, Protocol protocol, QObject *parent)
    :
      QObject(parent),
      io_context_(io_context),
      protocol_(protocol),
      socket_(io_context)

{
    message_.resize(1024);
    //using boost::asio;
    //boost::asio::io_service service;
    boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string("127.0.0.1"), protocol_.Port.number);
    //boost::asio::ip::tcp::socket sock(io_context_);

    socket_.async_connect(ep,connect_handler);
//    socket_.async_connect(ep, [&](){
//        //socket_.async_read_some(boost::asio::buffer(message_),message_.size());
//    });
    qDebug()<< "Create TCP_Client";
    //socket_.async_receive(boost::asio::buffer(message_),100);
    //message_.resize(1024);

    //socket_.async_read_some(boost::asio::buffer(message_),message_.size());
    //boost::asio::async_read(socket_, boost::asio::buffer(message_));
    //boost::system::error_code error;
    //sock_.read_some(boost::asio::buffer(read_buffer_), error);


}

