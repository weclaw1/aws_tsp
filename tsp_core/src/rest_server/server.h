#ifndef SERVER_H
#define SERVER_H

#include<cstdint>

#include "server_http.hpp"

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

class Server
{
public:
    Server() : Server(8080, 1) {}
    Server(uint16_t port, uint8_t threads) : server(port, threads) { }
    void registerHandlers();
    void start();
private:
    static void getHandler();
    static void postHandler();
    HttpServer server;
};

#endif // SERVER_H
