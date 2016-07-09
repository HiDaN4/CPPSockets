CC = g++
OUT = -o
INCLUDE_CPP = TCPStream.cpp
SERVER_CPP = TCPServer.cpp main_server.cpp
CLIENT_CPP = TCPClient.cpp main_client.cpp
FLAGS = -std=c++11

all:

server:
	$(CC) $(FLAGS) $(INCLUDE_CPP) $(SERVER_CPP) $(OUT) server


client:
	$(CC) $(FLAGS) $(INCLUDE_CPP) $(CLIENT_CPP) $(OUT) client


