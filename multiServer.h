#ifndef MULTISERVER_H
#define MULTISERVER_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <thread>         // std::thread
#include <iostream>       // std::cout


 
constexpr uint8_t MAX_CONNECTIONS = 32;
constexpr uint8_t SERVER_CONNECTION = 1;
constexpr uint8_t MAX_CLIENTS = MAX_CONNECTIONS - SERVER_CONNECTION;
constexpr uint16_t EVENTS =  POLLIN || POLLERR || POLLHUP || POLLNVAL;
constexpr int32_t TIMEOUT_MS = -1;





class MultiServer
{
private:
    struct ThreadData 
    {
        int16_t* serverFd;
        struct pollfd* communicationList;
        uint8_t* communications;
        struct sockaddr_in* serv_addr; 
        /*Warehouse* warehouse;*/
    };

    bool open();
    void stop();
    
    static void sendWare(int16_t clientFd);
    static void receiveWare(int16_t clientFd);
    static void act(void* data);
    static void addClient(int16_t* serverFd, sockaddr_in* serv_addr, pollfd* communicationList, uint8_t* communications);
    static void handleWare(int16_t clientFd);
    static void closeClient(struct pollfd*, uint8_t* communications);

    ThreadData threadData;

    int16_t serverFd;
    struct pollfd communicationList[MAX_CONNECTIONS];
    uint8_t communications = 0;
    struct sockaddr_in serv_addr{}; 
    std::string address;
    uint16_t port;
    //Warehouse& warehouse;
    std::thread act_thread;
    


 
public:
    MultiServer(std::string address, uint16_t port/*, Warehouse& warehouse*/);
    ~MultiServer();
 
};
 
#endif //MULTISERVER