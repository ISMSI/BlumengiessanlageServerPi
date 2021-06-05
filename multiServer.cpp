#include "multiServer.h"


MultiServer::MultiServer(std::string address, uint16_t port, Warehouse& warehouse_ext)
:warehouse(warehouse_ext), threadData{&serverFd, &communicationList[0], &communications, &serv_addr, warehouse_ext}
{
    this->address = address;
    this->port = port;

    std::cout << threadData.communicationList << std::endl;
    std::cout << threadData.communications << std::endl;
    std::cout << threadData.serverFd << std::endl;
    std::cout << threadData.serv_addr << std::endl;


    threadData.communicationList = &communicationList[0];
    threadData.communications = &communications;
    threadData.serverFd = &serverFd;
    threadData.serv_addr = &serv_addr;

    std::cout << threadData.communicationList << std::endl;
    std::cout << threadData.communications << std::endl;
    std::cout << threadData.serverFd << std::endl;
    std::cout << threadData.serv_addr << std::endl;

    communications = 0;

    for (int i = 0; i < MAX_CONNECTIONS; i++)
   {
       communicationList[i].fd = -1;
   } 
    

    if (open())
   { 
        pthread_create(&act_thread, NULL, act, static_cast<void*>(&threadData) ); 
   }  
}

MultiServer::~MultiServer()
{
    stop();
}

bool MultiServer::open()
{
        serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd < 0) { 
        std::cout << "Error on open socket" << std::endl;
        return false;
    } 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (bind(serverFd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
    {
        std::cout << "Error on bind" << std::endl;
        return false;
    } 

    listen(serverFd, MAX_CLIENTS);

    communicationList[0].fd = serverFd;
    communicationList[0].events = EVENTS;
    communications++;

    return true;         
}

void MultiServer::stop()
{
    pthread_join(act_thread, NULL);
    close(serverFd);
}


void MultiServer::addClient(int16_t* serverFd, sockaddr_in* serv_addr, pollfd* communicationList, uint8_t* communications)
{
    int32_t clientFd;
    sockaddr_in client_addr;
    socklen_t clilen = sizeof(client_addr);
    std::string message = "Welcome to SMS server";

    clientFd = accept( *serverFd, (struct sockaddr *) &client_addr, &clilen );

    if (clientFd < 0 )
    {   
        perror("accept");   
        exit(EXIT_FAILURE);   
    }   

    //inform user of socket number - used in send and receive commands  
    printf("New connection , socket fd is %d \n" , clientFd);

    //receiveWare(clientFd);
    
    //send new connection greeting message  
    /*if( send(clientFd, message.c_str(), message.size(), 0) < 0 ) 
    {   
        perror("send ");   
    } else {
        puts("Welcome message sent successfully");  
    } */
             
            
    //add new socket to array of sockets  
    for (int i = 0; i < MAX_CONNECTIONS; i++)   
    {   
        //if position is empty  
        if( communicationList[i].fd == -1 )   
        {   
            communicationList[i].fd = clientFd;
            communicationList[i].events = EVENTS;
            (*communications)++; 
            std::cout << "Adding to list of sockets as " << i << " communications: " 
            << (int)*communications  << std::endl;  
                    
            break;   
        }   
    } 
}

void MultiServer::closeClient(struct pollfd* client, uint8_t* communications)
{
    close(client->fd);
    client->fd = -1;
    (*communications)--;
}

void MultiServer::sendWare(int16_t clientFd)
{   
    char16_t ware;
    std::string send_buffer = "Got your message";
    ware = 8;

    //send(clientFd , send_buffer.c_str() , send_buffer.size()  , 0 );
    write(clientFd, &ware, sizeof(ware));

}

void MultiServer::receiveWare(int16_t clientFd)
{
    char recv_buffer[256];
    int8_t ret;

    do
    {
        ret =read( clientFd , recv_buffer, 1024);
        
        for( int i = 0; i<255; i++)
        {
            if (recv_buffer[i] != '\0')
            { 
                std::cout << recv_buffer[i];
            }
            else
            {
                break;
            }  
        } 
    } while (ret==0);
    
 
   std::cout << std::endl;

}

void MultiServer::receiveRequest(int16_t clientFd/*, Warehouse& warehouse*/)
{
    char recv_buffer[1];
    int8_t ret;


    ret =read( clientFd , recv_buffer, 1);
    
    if (recv_buffer[0] == 0b01010011)
    {
        std::cout << "Water now!!!" <<std::endl;
        //warehouse.waterNow.store(true);
    }
    else{
        std::cout << "Reeived crap!!!" <<std::endl;
    }

    sendWare(clientFd);
}



void MultiServer::handleWare(int16_t clientFd/*, Warehouse& warehouse*/)
{
    receiveRequest(clientFd/*, warehouse*/);
    //receiveWare(clientFd);
    //sendWare(clientFd);
}

void* MultiServer::act(void* data)
{
    uint32_t ret;
    ThreadData* threadData = static_cast<ThreadData*>(data);
    //Warehouse warehouse;// = threadData->warehouse;
    

    while (true)
   {

       pollfd test[MAX_CONNECTIONS] ={};
       uint8_t testcnd = *threadData->communications;
       for(int i = 0; i < MAX_CONNECTIONS; i++)
      {
        test[i] = threadData->communicationList[i];
        
      } 
        
        do
        {
            ret = poll(threadData->communicationList, *threadData->communications, TIMEOUT_MS);
        } while ( ret < 0 && ret == EINTR );
        
        if ( ret == 0 ) {
        /*Timeout*/
        std::cout << "The poll timed out!";
        } else if (ret < 0) {
            /*Error*/
            std::cout << "An error occourt: " << errno;
        } 
        
        /*Event occoured*/

        for (int i = 0; i < *threadData->communications; i++)
        {
            if (threadData->communicationList[i].fd == -1)
            {
                break;
            } 
            short int  revent = threadData->communicationList[i].revents;

            if (revent & POLLIN)
            {
                std::cout << "POLLIN" << std::endl;
                if (threadData->communicationList[i].fd == *threadData->serverFd)
                {
                    /*Add client*/
                    std::cout << "addClientFunc" << std::endl;
                    addClient(threadData->serverFd, threadData->serv_addr, threadData->communicationList, threadData->communications);
                } else {
                    /*Handle communication*/
                    std::cout << "Handle Comm" << std::endl;
                    handleWare(threadData->communicationList[i].fd/*, warehouse*/);
                } 
            }

            if (revent & POLLHUP)
            {
                if (threadData->communicationList[i].fd == *threadData->serverFd)
                {
                    exit(EXIT_FAILURE);
                } else {
                    std::cout << "POLLHUP" << std::endl;
                    closeClient(&threadData->communicationList[i], threadData->communications);
                } 
            }
            else
           {
               std::cout << "Event: " << (int)revent << std::endl;
           } 
        }
   } 
}


