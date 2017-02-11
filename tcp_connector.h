#ifndef TCP_CONNECTOR_H_
#define TCP_CONNECTOR_H_

#include "tcp_stream.h"
#include <memory>
#include <netinet/in.h>

class TCPConnector
{
public:
  TCPStream* connect(int port, const char* server);
private:
  int resolveHostName(const char* host, struct in_addr* addr);
};

#endif
