#ifndef TCPSESSION_H
#define TCPSESSION_H

#include <boost/asio.hpp>
#include "session.h"
#include "../qyhbuffer.h"
#include "../protocol.h"
#include "../agv.h"

using boost::asio::ip::tcp;

class TcpSession : public Session
{
public:
    TcpSession(tcp::socket socket, int sessionId);

    virtual ~TcpSession();

    virtual void send(const Json::Value &json);

    virtual bool doSend(const char *data,int len);

    virtual void close();

    virtual void start();

    inline void setAGVPtr(AgvPtr agv){_agvPtr = agv;}
    inline AgvPtr getAgvPtr(){return _agvPtr;}
private:
    void packageProcess(const char *data,int len);
    tcp::socket socket_;
    QyhBuffer buffer;
    char read_buffer[MSG_READ_BUFFER_LENGTH];
    int json_len;

    int _acceptID = -1;

    AgvPtr _agvPtr;
};


using TcpSessionPtr = std::shared_ptr<TcpSession>;

#endif // TCPSESSION_H
