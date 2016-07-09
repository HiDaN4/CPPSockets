//
//  TCPClient.cpp
//  CPPSockets
//
//  Created by Dmitry Sokolov on 7/5/16.
//

#include "TCPClient.hpp"
#include "TCPStream.hpp"

#include <arpa/inet.h>
#include <iostream>



// constructor
TCPClient::TCPClient(int portno, const std::string& host): port_number(portno), host_name(host)
{
    
    self.parseServerAddress();
}



/* private parseServerAddress() function
 *
 * @param: none
 * @pre: none
 * @post: none
 *
 * Parse host address and port
 */
void TCPClient::parseServerAddress()
{

    struct addrinfo* result;
    int res = getaddrinfo(self.host_name.c_str(), NULL, NULL, &result);
    
    if (res == 0) {
        memcpy(&self.serv_addr.sin_addr, &((struct sockaddr_in*)result->ai_addr)->sin_addr, sizeof(struct in_addr));
        freeaddrinfo(result);
    }
    
    
    if (self.server == NULL)
        error("ERROR, could not connect to the host!");
    
    bzero((char*)&self.serv_addr, sizeof(self.serv_addr));
    
    self.serv_addr.sin_family = AF_INET;
    
    self.serv_addr.sin_port = htons(self.port_number);
    
}



/* connectToHost() function
 *
 * @param: none
 * @pre: none
 * @post: none
 *
 * Try to connect to the host/server and return the instance of TCPStream
 */
std::shared_ptr<TCPStream> TCPClient::connectToHost()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // socket file descriptor
    
    
    if (sockfd < 0) {
        error("ERROR opening socket!");
        return NULL;
    }
    
    int success = ::connect(sockfd, (struct sockaddr *)&self.serv_addr, sizeof(self.serv_addr));
    
    if (success < 0) {
        error("Error connecting");
        return NULL;
    }
    
    std::shared_ptr<TCPStream> stream(new TCPStream(sockfd, &self.serv_addr) );
    return stream;
}

