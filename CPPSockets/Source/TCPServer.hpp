//
//  TCPServer.hpp
//  CPPSockets
//
//  Created by Dmitry Sokolov on 7/4/16.
//

#ifndef TCPServer_hpp
#define TCPServer_hpp

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>


#define self (*this)

extern void error(const std::string&);

class TCPStream;


class TCPServer {
private:
    int sockfd;                     // file descriptor for this connector

    int port_number;               // port on which the acceptor works
    std::string host;
    
    bool is_listening;              // status of server

    struct sockaddr_in serv_addr;   // server address info
    
    void startServer();
    
public:
    TCPServer(int portno, std::string host="");      // constructor with port number on which open socket and host
    ~TCPServer();
    
    std::shared_ptr<TCPStream> acceptConnection();        // get the stream to send or receive data
    
};




#endif /* TCPServer_hpp */
