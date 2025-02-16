#pragma once

#include <netinet/in.h>

#include "socket_common.h"
#include "header.pb.h"

class Server{
public:
    Server();
    ~Server();
    void listenToClient();
    std::string processHeader(const Header& header);
    
private:
    int server_fd_, socket_handle_;
    int opt_{TRUE};
    struct sockaddr_in address_;
    socklen_t addrlen_;
    char buffer_[BUFFER_SIZE];
};