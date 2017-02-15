#ifndef TCP_CONNECTOR_H_
#define TCP_CONNECTOR_H_

#include "tcp_stream.h"
#include <memory>
#include <netinet/in.h>

class TCPConnector
{
public:
  TCPConnector();
  virtual ~TCPConnector();
  std::unique_ptr<TCPStream> connect(int port, const char* server);
  void connect(TCPStream& stream, int port, const char* server);
private:
  int resolveHostName(const char* host, struct in_addr* addr);
};

#endif
