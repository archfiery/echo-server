#ifndef TCP_STREAM_H_
#define TCP_STREAM_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <cstdint>
#include <ctime>
#include <string>
#include <unistd.h>

class TCPStream
{
  int m_sd;
  uint16_t m_peerPort;
  std::string m_peerIP;
public:
  friend class TCPAcceptor;
  friend class TCPConnector;
  
  /**
   * delete default constructor
   */
  TCPStream() = delete;
  /**
   * delete copy constructor
   */
  TCPStream(const TCPStream&) = delete;
  /**
   * delete copy assignment operator
   */
  TCPStream& operator=(const TCPStream&) = delete;
  /**
   * destructor
   */
  virtual ~TCPStream();
  ssize_t send(const char* buffer, size_t len);
  ssize_t receive(char* buffer, size_t len, int timeout=0);

  std::string getPeerIP() const;
  uint16_t getPeerPort() const;

  enum {
    connectionClosed  =  0,
    connectionReset   = -1,
    connectionTimeOut = -2
  };

private:
  TCPStream(int sd, struct sockaddr_in* address);
  bool waitForReadEvent(int timeout);
};

#endif
