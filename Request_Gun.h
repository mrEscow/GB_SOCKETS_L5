#ifndef REQUEST_GUN_H
#define REQUEST_GUN_H

#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>

#include <QVector>
#include <QThread>



using boost::asio::ip::tcp;

class Request_Gun
{
public:
    Request_Gun(uint16_t bullets);
private:
    QVector<QThread> sockets;
};




#endif // REQUEST_GUN_H
