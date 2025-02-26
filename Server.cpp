#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Server.h"

Server::Server(int port) {
    this->port = port;

    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(this->port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;  // Enable SO_REUSEADDR

    // Set SO_REUSEADDR to reuse the port immediately
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    if (bind(this->serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding to port " << this->port << "\n";
        exit(EXIT_FAILURE);
    }

    // Constructor
}

void Server::start() {

    if (listen(this->serverSocket, 3) < 0) {
        std::cerr << "Error in listen()\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Server started on port " << this->port << "\n";

    while(true){
        std::cout<<"After Listening" <<std::endl;
        sockaddr_in clientAddress;
        int clientAddressLen;
        int new_socket = accept(this->serverSocket, (struct sockaddr*)&clientAddress,
                                (socklen_t*)&clientAddressLen);

        if(new_socket<0){
            std::cout<<"Error: " <<new_socket<<std::endl;
            std::cout<<"And error occured";
        }

        else{
            std::cout<<"newsocket: "<<new_socket<<std::endl;
        }
        char buffer[1024] = { 0 };
        int valread = read(new_socket, buffer, 1024);
        if(valread < 0){
            std::cout << "Error: " << valread << std::endl;
            std::cout<<"And error occured while reading data";
        }
        else{
            std::cout<<"Valread: "<<valread<<std::endl;
        }
        printf("\nSomething: %s\n", buffer);

        char* response = "HTTP/1.1 200 OK\r\n"
            "Content Length: 10\r\n"
            "Content-Type: application/json\r\n"
            "Connection: Closed\r\n"
            "\r\n"
            "{\"message\": \"hello\"}";

        send(new_socket, response, strlen(response), 0);
        printf("Hello message sent\n");

        close(new_socket);
    }

    std::cout<<"Ended";
    shutdown(this->serverSocket, SHUT_RDWR);
}
