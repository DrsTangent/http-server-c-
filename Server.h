#ifndef SERVER_H
#define SERVER_H

#include "Router.h"

class Server {
private:
    Router router;  // Instance of Router
    int serverSocket;
    int port;
public:
    Server();
    Server(int port);
    void start();  // Function to start the server
};

#endif
