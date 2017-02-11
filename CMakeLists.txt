CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (CMAKE_CXX_STANDARD 11)

SET (CMAKE_CXX_FLAGS -Wall)
SET (CMAKE_CXX_FLAGS -w)

PROJECT (echo_server CXX)

SET (SERVER_SRC echo_server.cc tcp_stream.cc tcp_acceptor.cc)
SET (CLIENT_SRC echo_client.cc tcp_stream.cc tcp_connector.cc)

ADD_EXECUTABLE (server ${SERVER_SRC})
ADD_EXECUTABLE (client ${CLIENT_SRC})
