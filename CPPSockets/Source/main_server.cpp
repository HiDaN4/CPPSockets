//
//  main_server.cpp
//  CPPSockets
//
//  This main is used to create a server that will wait for a connection and then print received messages and send a response.
//  Used for demonstrative purposes
//
//  Created by Dmitry Sokolov on 7/4/16.
//

#include <iostream>
#include <string>
#include <memory>

#include "TCPServer.hpp"
#include "TCPStream.hpp"



const uint PORT = 2045;         // port on which start the server
const int BUFFER_SIZE = 256;    // buffer size when receiving messages

/* error(const std::string& msg) function
 *
 * @param = msg: std::string& - error message
 *
 * Print the error message and last error received by system
 */
void error(const std::string& msg)
{
    perror(msg.c_str());
}



int main(int argc, const char * argv[]) {
    
    std::cout << "Starting server...\n";
    
    TCPServer server(PORT); // create a server on specified port
    std::shared_ptr<TCPStream> stream = server.acceptConnection(); // get the stream
    char buffer[BUFFER_SIZE];                    // store received messages
    
    char answer[] = "Received your message!";
    
    
    while (stream != NULL && stream->isOpen()) { // while the stream is open
        stream->receive(buffer, sizeof(buffer));      // get the message
        std::cout << "Received msg: " << buffer << "\n";
        stream->send(answer, sizeof(answer)); // send a message
    }
    
    return 0;
}
