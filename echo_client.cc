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
    cerr << "usage: "<< argv[0] << " <port> <ip> <timeout> " << endl;
    return 1;
  }

  int timeout = atoi(argv[3]);
  string message;
  char line[256];

  TCPConnector connector;

  unique_ptr<TCPStream> stream = connector.connect(atoi(argv[1]), argv[2]);

  if (stream.get() != nullptr) {
    string msg("hello world, c++ network programming.");
    auto st = stream.get();
    st->send(msg.c_str(), msg.size());
    cout << "sent - " << msg << endl;
    st->receive(line, sizeof(line), timeout);
    cout << "received - " << line << endl;
  }

  return 0;

}
