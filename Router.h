#ifndef ROUTER_H
#define ROUTER_H

#include <string>

class Router {
public:
    Router();
    void route(const std::string& path);  // Function to handle routes
};

#endif
