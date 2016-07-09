//
//  TCPClient.hpp
//  CPPSockets
//
//  Created by Dmitry Sokolov on 7/5/16.
//

#ifndef TCPClient_hpp
#define TCPClient_hpp

#include <stdio.h>
#include <unistd.h>
#include <memory>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>

#define self (*this)

extern void error(const std::string& msg);

class TCPStream;



class TCPClient
{
private:
    int port_number;       // port number to connect to
    std::string host_name;  // host address

    struct sockaddr_in serv_addr;   // struct with socket server address
    struct hostent* server;         // struct with socket server
    
    
    void parseServerAddress();
    
    
public:
    TCPClient(int portno, const std::string& host);  // start socket on given port and address of the host
    
    
    std::shared_ptr<TCPStream> connectToHost();        // connect to the server/host and get the TCPStream instance
    
};


#endif /* TCPClient_hpp */
