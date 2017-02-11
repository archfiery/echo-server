#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include "tcp_connector.h"

using namespace std;

int main(int argc, char** argv)
{
  if (argc != 4) {
    cerr << "usage: "<< argv[0] << " <port> <ip>" << endl;
    return 1;
  }

  int timeout = atoi(argv[3]);
  string message;
  char line[256];

  TCPConnector connector;
  TCPStream* stream(connector.connect(atoi(argv[1]), argv[2]));

  if (stream != nullptr) {
    string msg("hello world, c++ network programming.");
    stream->send(msg.c_str(), msg.size());
    cout << "sent - " << msg << endl;
    stream->receive(line, sizeof(line), timeout);
    cout << "received - " << line << endl;
    delete stream;
  }

  return 0;
}
