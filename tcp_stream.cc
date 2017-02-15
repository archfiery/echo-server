#include "tcp_stream.h"
#include <string>
#include <arpa/inet.h>

using namespace std;

TCPStream::TCPStream(int sd, struct sockaddr_in* address)
: m_sd(sd)
{
  char ip[50];
  ::inet_ntop(PF_INET, (struct in_addr*) &(address->sin_addr.s_addr), ip, sizeof(ip) - 1);
  m_peerIP = string(ip);
  m_peerPort = ::ntohs(address->sin_port);
}

TCPStream::TCPStream(TCPStream&& other)
: m_sd(other.m_sd)
, m_peerPort(other.m_peerPort)
, m_peerIP(other.m_peerIP)
{

}

TCPStream& TCPStream::operator=(TCPStream&& other)
{
  m_sd = other.m_sd;
  m_peerPort = other.m_peerPort;
  m_peerIP = other.m_peerIP;
}

TCPStream::~TCPStream()
{
  close(m_sd);
}

ssize_t TCPStream::send(const char* buffer, size_t len)
{
  return ::write(m_sd, buffer, len);
}

ssize_t TCPStream::receive(char* buffer, size_t len, int timeout)
{
  if (timeout <= 0) 
    return ::read(m_sd, buffer, len);

  if (waitForReadEvent(timeout))
    return ::read(m_sd, buffer, len);

  return connectionTimeOut;
}

string TCPStream::getPeerIP() const
{
  return m_peerIP;
}

uint16_t TCPStream::getPeerPort() const
{
  return m_peerPort;
}

bool TCPStream::waitForReadEvent(int timeout)
{
  fd_set sdset;
  struct timeval tv;
  tv.tv_sec = timeout;
  tv.tv_usec = 0;
  
  FD_ZERO(&sdset);
  FD_SET(m_sd, &sdset);
  if (::select(m_sd + 1, &sdset, NULL, NULL, &tv) > 0)
    return true;

  return false;
}
