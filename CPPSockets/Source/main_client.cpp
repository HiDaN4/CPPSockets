//
//  mainClient.cpp
//  CPPSockets
//
//  This main is used to create a client that will connect to given host and port and then send messages that user inputs to the server
//  Used for demonstrative purposes
//
//  Created by Dmitry Sokolov on 7/5/16.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>
#include <cstring>

#include "TCPClient.hpp"
#include "TCPStream.hpp"





const uint PORT = 2045;                 // port on which start the server
const std::string HOST = "127.0.0.1";   // host/server address
const int BUFFER_SIZE = 256;            // buffer size when receiving messages


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




/* getInput(std::string& input) function
 *
 * @param = input: std::string& - buffer where put input
 *
 * Get input from user and put into given std::string
 */
void getInput(std::string& input)
{
    std::cout << "Enter the message ('quit' to exit): ";
    std::getline(std::cin, input);
    
}







int main(int argc, const char * argv[]) {
    
    std::cout << "Client is running\n";
    
    
    TCPClient client(PORT, HOST);          // create client that will connect to given host:port
    std::shared_ptr<TCPStream> stream = client.connectToHost(); // get the stream
    
    std::string msg("");
    std::string input("");
    
    if (stream.get() != NULL && stream->isOpen()) {      // make sure the stream is open
        char buffer[BUFFER_SIZE];
        
        while (true) {          // forever while user types
            getInput(input);    // get the input
            if (input == "quit")
                break;
            strlcpy(buffer, input.c_str(), sizeof(buffer));
            stream->send(buffer, sizeof(buffer)); // send message to the server
            stream->receive(buffer, sizeof(buffer));  // wait for the response
            std::cout << "Response from server: " << buffer  << "\n";
        }
    }
    
    
    return 0;
}
