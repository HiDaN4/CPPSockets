//
//  TCPStream.cpp
//  CPPSockets
//
//  Created by Dmitry Sokolov on 7/5/16.
//

#include "TCPStream.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



// constructor
TCPStream::TCPStream(int clientfd, struct sockaddr_in* addr): socketfd(clientfd), is_open(true)
{
    char ipAddr[50];
    // get ip address from host
    inet_ntop(PF_INET, (struct in_addr*)&(addr->sin_addr.s_addr), ipAddr, sizeof(ipAddr)-1);
    
    peerPort = ntohs(addr->sin_port);
    peerIP = ipAddr;
    
}


TCPStream::~TCPStream()
{
    // close the connection with peer
    close(socketfd);
}


/* write(const std::string &msg) function
 *
 * @param = msg: std::string& - message to send
 * @pre: none
 * @post: none
 *
 * Send given message to socket (server or client)
 */
ssize_t TCPStream::send(const char* msg, size_t size)
{
    if (!is_open)
        return 0;
    
    ssize_t res = ::write(socketfd, msg, size);
    if (res < 0) {
        error("Error sending message");
        is_open = false;
    }
    
    return res;
    
}




/* read(std::string* msg) function
 *
 * @param = msg: std::string* - buffer where to put received message
 * @pre: none
 * @post: none
 *
 * Read a message from socket (server or client); If the stream is close, do nothing
 */
ssize_t TCPStream::receive(char* buffer, size_t size)
{
    
    if (!is_open) {
        return 0;
    }
    
    ssize_t res = ::read(socketfd, buffer, size);
    // read the message
    if (res < 0) {
        error("Error receiving message!");
        is_open = false;
    }
    
    return res;
    
}

