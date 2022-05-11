#ifndef TIMECLIENT_H
#define TIMECLIENT_H

#include <QObject>
#include <QDebug>
//
// sync_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <iomanip>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
//#include "socks4.hpp"

#include "Protocol.h"

using boost::asio::ip::tcp;

//#include <string>
//#include <boost/asio.hpp>
//#include <boost/array.hpp>

namespace socks4 {

const unsigned char version = 0x04;

class request
{
public:
  enum command_type
  {
    connect = 0x01,
    bind = 0x02
  };

  request(command_type cmd, const boost::asio::ip::tcp::endpoint& endpoint,
      const std::string& user_id)
    : version_(version),
      command_(cmd),
      user_id_(user_id),
      null_byte_(0)
  {
    // Only IPv4 is supported by the SOCKS 4 protocol.
    if (endpoint.protocol() != boost::asio::ip::tcp::v4())
    {
      throw boost::system::system_error(
          boost::asio::error::address_family_not_supported);
    }

    // Convert port number to network byte order.
    unsigned short port = endpoint.port();
    port_high_byte_ = (port >> 8) & 0xff;
    port_low_byte_ = port & 0xff;

    // Save IP address in network byte order.
    address_ = endpoint.address().to_v4().to_bytes();
  }

  boost::array<boost::asio::const_buffer, 7> buffers() const
  {
    boost::array<boost::asio::const_buffer, 7> bufs =
    {
      {
        boost::asio::buffer(&version_, 1),
        boost::asio::buffer(&command_, 1),
        boost::asio::buffer(&port_high_byte_, 1),
        boost::asio::buffer(&port_low_byte_, 1),
        boost::asio::buffer(address_),
        boost::asio::buffer(user_id_),
        boost::asio::buffer(&null_byte_, 1)
      }
    };
    return bufs;
  }

private:
  unsigned char version_;
  unsigned char command_;
  unsigned char port_high_byte_;
  unsigned char port_low_byte_;
  boost::asio::ip::address_v4::bytes_type address_;
  std::string user_id_;
  unsigned char null_byte_;
};

class reply
{
public:
  enum status_type
  {
    request_granted = 0x5a,
    request_failed = 0x5b,
    request_failed_no_identd = 0x5c,
    request_failed_bad_user_id = 0x5d
  };

  reply()
    : null_byte_(0),
      status_()
  {
  }

  boost::array<boost::asio::mutable_buffer, 5> buffers()
  {
    boost::array<boost::asio::mutable_buffer, 5> bufs =
    {
      {
        boost::asio::buffer(&null_byte_, 1),
        boost::asio::buffer(&status_, 1),
        boost::asio::buffer(&port_high_byte_, 1),
        boost::asio::buffer(&port_low_byte_, 1),
        boost::asio::buffer(address_)
      }
    };
    return bufs;
  }

  bool success() const
  {
    return null_byte_ == 0 && status_ == request_granted;
  }

  unsigned char status() const
  {
    return status_;
  }

  boost::asio::ip::tcp::endpoint endpoint() const
  {
    unsigned short port = port_high_byte_;
    port = (port << 8) & 0xff00;
    port = port | port_low_byte_;

    boost::asio::ip::address_v4 address(address_);

    return boost::asio::ip::tcp::endpoint(address, port);
  }

private:
  unsigned char null_byte_;
  unsigned char status_;
  unsigned char port_high_byte_;
  unsigned char port_low_byte_;
  boost::asio::ip::address_v4::bytes_type address_;
};

} // namespace socks4


#define MEM_FN(x) boost::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x,y) boost::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z) boost::bind(&self_type::x, shared_from_this(),y,z)

// equivalent to "sock_.async_connect(ep, MEM_FN1(on_connect,_1));"
// sock_.async_connect(ep, boost::bind(&talk_to_svr::on_connect,shared_ptr_from_this(),_1));
// sock_.async_connect(ep, boost::bind(&talk_to_svr::on_connect,this,_1));

class TCP_Client : public QObject//, public boost::enable_shared_from_this<TCP_Client>,boost::asio::noncopyable
{
    Q_OBJECT
private:
    boost::asio::io_context& io_context_;
    Protocol protocol_;
    boost::asio::ip::tcp::endpoint ep;//( ip::address::from_string("127.0.0.1"), 8001);
private:
    boost::asio::ip::tcp::socket socket_;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    bool started_;
    std::string message_;
private:
    TCP_Client();
public:
    TCP_Client(boost::asio::io_context& io_context, Protocol protocol, QObject *parent = nullptr );
public:
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<TCP_Client> ptr;

    static void connect_handler(const boost::system::error_code & ec);
//    static ptr start(boost::asio::ip::tcp::endpoint ep, const std::string & message)
//    {
//        ptr new_(new TCP_Client());
//        //new_->start(ep);
//        return new_;
//    }
//    void stop()
//    {
//        if ( !started_) return;
//        started_ = false;
//        sock_.close();
//    }
//    bool started() { return started_; }

//    void do_read()
//    {
//        async_read(sock_, boost::asio::buffer(read_buffer_),
//        MEM_FN2(read_complete,_1,_2), MEM_FN2(on_read,_1,_2));
//    }
//    void do_write(const std::string & msg)
//    {
//        if ( !started() ) return;
//        std::copy(msg.begin(), msg.end(), write_buffer_);
//        sock_.async_write_some( boost::asio::buffer(write_buffer_, msg.size()),
//        MEM_FN2(on_write,_1,_2));
//    }
//    size_t read_complete(const boost::system::error_code & err, size_t bytes)
//    {
//        // similar to the one shown in TCP Synchronous Client
//    }
//    void on_connect(const error_code & err)
//    {
//        if ( !err) do_write(message_ + "\n");
//        else stop();
//    }
//    void on_read(const error_code & err, size_t bytes)
//    {
//        if ( !err)
//        {
//            std::string copy(read_buffer_, bytes - 1);
//            std::cout << "server echoed our " << message_ << ": "<< (copy == message_ ? "OK" : "FAIL") << std::endl;
//        }
//        stop();
//    }
//    void on_write(const error_code & err, size_t bytes)
//    {
//        do_read();
//    }
};


using boost::asio::ip::tcp;
#endif // TIMECLIENT_H
