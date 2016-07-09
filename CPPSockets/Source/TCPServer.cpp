//
//  TCPServer.cpp
//  CPPSockets
//
//  Created by Dmitry Sokolov on 7/4/16.
//

#include "TCPServer.hpp"
#include "TCPStream.hpp"



// constuctor
TCPServer::TCPServer(int portno, std::string host): port_number(portno), host(host), is_listening(false)
{
    self.startServer();
}



TCPServer::~TCPServer()
{
     //close connection
    if (self.sockfd > 0)
        close(self.sockfd);
}




/* private startStream() function
 *
 * @param: none
 * @pre: none
 * @post: none
 *
 * Initialize socket and bind the server to be able receive client connections
 */
void TCPServer::startServer()
{
    self.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (self.sockfd < 0)
        error("ERROR openning Socket!");
    
    
    bzero((char *)&self.serv_addr, sizeof(self.serv_addr));
    
    // assign the address and port
    self.serv_addr.sin_family = PF_INET;
    self.serv_addr.sin_port = htons(self.port_number);
    
    if (self.host.length() > 0)
        inet_pton(PF_INET, self.host.c_str(), &(self.serv_addr.sin_addr));
    else
        self.serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    int optValue = 1;
    
    setsockopt(self.sockfd, SOL_SOCKET, SO_REUSEADDR, &optValue, sizeof(optValue));
    
    // start the server
    int success = bind(self.sockfd, (struct sockaddr *)&self.serv_addr, sizeof(self.serv_addr));
    
    if (success < 0)
        error("ERROR on binding a socket");
    
    
    // start listening for clients
    success = listen(self.sockfd, 5);
    
    if (success != 0) {
        error("ERROR on listening for clients!");
        self.is_listening = false;
    } else {
        self.is_listening = true;
    }
    
}



/* acceptConnection() function
 *
 * @param: none
 * @pre: none
 * @post: none
 *
 * Wait for any connection (clients) and return the instance of TCPStream
 */
std::shared_ptr<TCPStream> TCPServer::acceptConnection()
{
    if (!is_listening)
        return NULL;
    
    
    struct sockaddr_in client_addr;                // client address info
    socklen_t client_len = sizeof(client_addr);  // socket client length
    
    bzero((struct sockaddr_in*)&client_addr, sizeof(client_addr));
    
    
    int newsockfd = ::accept(self.sockfd, (struct sockaddr *)&client_addr, &client_len);
    
    if ( newsockfd < 0 ) {
        error("ERROR on accept");
        return NULL;
    }
    std::shared_ptr<TCPStream> stream(new TCPStream(newsockfd, &client_addr));
    return stream;
}












