#include <iostream>
#include <thread>
#include "server.hpp"
#include "Common.hpp"
#include <cstring>

void ServerTCP::ListenConnections()
{
    listen(m_Socketfd, 5);
    m_ClientSocketfd = accept(m_Socketfd, nullptr, nullptr);
    m_IsConnected = true;
}


void ServerTCP::TcpHandlerThread()
{
    ServerTCP server(54321);
    for (;;)
    {
        server.ListenConnections();
        std::thread receiveTcpThread(&ServerTCP::ReceiverThread, &server);

        receiveTcpThread.join();
    }
}

void ServerTCP::ReceiverThread()
{
    char buffer[256] = { 0 };
    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        if (recv(m_ClientSocketfd, buffer, sizeof(buffer), 0) <= 0)
        {
            m_IsConnected = false;
            // notify SenderThread to end
            break;
        }
        // Thread ready
        {
            std::lock_guard<std::mutex> lg(g_Mutex);
            g_Flag = true;
        }
        std::cout << "Message from client: " << buffer << std::endl;
        memset(g_Buffer, 0, sizeof(g_Buffer));
        memcpy(g_Buffer, buffer, sizeof(buffer));
        g_Cv.notify_one(); // Notify Can sender
    }
}

void ServerTCP::SenderThread()
{

    while(1)
    {

    }

}


