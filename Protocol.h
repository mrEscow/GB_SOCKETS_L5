#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <QApplication>
struct Protocol{
    struct Port{
        quint16 number{1111};
        quint16 min{1024};
        quint16 max{65535};
    }Port;
};

inline static Protocol TimeServerProtocol;

#endif // PROTOCOL_H
