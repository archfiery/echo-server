#ifndef TCP_ACCEPTOR_H_
#define TCP_ACCEPTOR_H_

#include <memory>
#include <string>
#include <netinet/in.h>
#include "tcp_stream.h"

class TCPAcceptor
{
  int         m_lsd;
  std::string m_address;
  int         m_port;
  bool        m_listening;
public:
  TCPAcceptor(int port, const char* address="");
  virtual ~TCPAcceptor();

  int start();
  std::unique_ptr<TCPStream> accept();
};

#endif
