//
//  TCPStream.hpp
//  CPPSockets
//
//  Created by Dmitry Sokolov on 7/5/16.
//

#ifndef TCPStream_hpp
#define TCPStream_hpp

#include <stdio.h>
#include <string>


extern void error(const std::string& err);

class TCPServer;
class TCPClient;


class TCPStream
{
private:
    int socketfd;                           // file descriptor for connected socket
    
    int peerPort;                           // port of the connected peer
    std::string peerIP;                     // ip address of the connected peer
    bool is_open;                           // check if the stream open or close
    

    // Constructors
    TCPStream();
    TCPStream(const TCPStream& rhs);
    
    TCPStream(int clientfd, struct sockaddr_in* addr); // constructor with socket filedescriptors and status (opened or closed)
    
    // allow these classes to create streams
    friend class TCPServer;
    friend class TCPClient;
    
public:
    ~TCPStream();
    ssize_t send(const char* msg, size_t size);                   // send a message
    ssize_t receive(char* buffer, size_t size);                   // read a message and put into given buffer
    
    inline bool isOpen() const { return is_open; }          // return the status of the stream
    inline int getPeerPort() const { return peerPort; }     // return the port on which the socket is open
    inline std::string getPeerIP() const { return peerIP; } // return the ip address of the peer
};

#endif /* TCPStream_hpp */
