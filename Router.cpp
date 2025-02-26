#include <iostream>
#include "Router.h"

Router::Router() {
    // Constructor
}

void Router::route(const std::string& path) {
    if (path == "/home") {
        std::cout << "Routing to Home Page" << std::endl;
    } else {
        std::cout << "404 Not Found" << std::endl;
    }
}
