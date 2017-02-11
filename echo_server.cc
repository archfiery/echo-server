#include <iostream>
#include <memory>
#include <cstdlib>
#include "tcp_acceptor.h"

using namespace std;

int main(int argc, char** argv)
{
  if (argc < 2 || argc > 4) {
    cerr << "usage: server <port> [<ip>]" << endl;
    exit(1);
  }

  TCPAcceptor acceptor(atoi(argv[1]));
  if (argc == 3) {
    acceptor = TCPAcceptor(atoi(argv[1]), argv[2]);
  }

  TCPStream* stream;
  if (acceptor.start() == 0) {
    while (true) {
      stream = acceptor.accept();
      if (stream != nullptr) {
        size_t len;
        char line[256];
        while ((len = stream->receive(line, sizeof(line))) > 0) {
          line[len] = NULL;
          cout << "received - " << line << endl;
          stream->send(line, len);
        }
      }
    }
  }
  cerr << "could not start the server" << endl;
  exit(-1);
}
