# CPPSockets

## Overview

This is a demo of using socket api (on C++). Example illustrates how to create a server/host and a client that communicate with each other.

This project has several classes:

```C++
TCPServer \\ class that acts as a server and will wait for a connection.
TCPClient \\ class that acts as a client and will connect to given host/server.
TCPStream \\ a created stream through which the client can send and receive messages.
```

These classes are fully documented and have all necessary information.


## Requirements

* C++ 11

## Installation

To create the server and client applications, you can build them using xCode configuration.

Alternatively, you can use 'make' command in command line:

```ruby
make server # to create a server application; Output file is server
make client # to create a client application; Output file is client
```

To start the server on MacOS (after executing mentioned make commands):
```ruby
./server
```
This will start a server on given local machine

To start a client application, run the following command on separate terminal window:
```ruby
./client
```

## Usage

To create a server:

```C++
#include "TCPServer.hpp"
#include "TCPStream.hpp"


const uint PORT = 2045;         // port on which start the server
const int BUFFER_SIZE = 256;    // buffer size when receiving messages

int main(int argc, const char * argv[]) {

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

```

To create a client:

```C++
#include "TCPClient.hpp"
#include "TCPStream.hpp"


const uint PORT = 2045;                 // port on which start the server
const std::string HOST = "127.0.0.1";   // host/server address

int main(int argc, const char * argv[]) {

    TCPClient client(PORT, HOST);          // create client that will connect to given host:port
    std::shared_ptr<TCPStream> stream = client.connectToHost(); // get the stream

    
    if (stream.get() != NULL && stream->isOpen()) {      // make sure the stream is open
        char buffer[] = "Hello from client!";

        stream->send(buffer, sizeof(buffer)); // send message to the server
        stream->receive(buffer, sizeof(buffer));  // wait for the response
        std::cout << "Response from server: " << buffer  << "\n";
    }   
    
    return 0;
}

```

These are just examples on how to use the objects.

## Author

Dmitry Sokolov

## License

CPPSockets is available under the MIT license. See the LICENSE file for more info.
