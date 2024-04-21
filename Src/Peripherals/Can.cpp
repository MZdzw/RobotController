#include <thread>
#include <iostream>
#include "Can.hpp"
#include "Common.hpp"

void Can::CanHandlerThread()
{
    Can canObject;
    std::cout << "CanHandlerThread\n";
    std::thread canReceiverThread(&Can::CanReceiverThread, &canObject);
    std::thread canSenderThread(&Can::CanSenderThread, &canObject);

    canReceiverThread.join();
    canSenderThread.join();
}

void Can::CanReceiverThread()
{

    while (1)
    {
        std::cout << "Before Can receiver\n";
        m_Bytes = recv(m_CanSocketfd, &m_CanFrame, sizeof(can_frame), 0);
        std::cout << m_CanFrame.can_id << " [" << m_CanFrame.can_dlc;
        for (int i = 0; i < m_CanFrame.can_dlc; ++i)
        {
            std::cout << " " << m_CanFrame.data[i];
        }
        std::cout << std::endl;

    }
    
}

void Can::CanSenderThread()
{
    int number = 0;
    m_CanFrame.can_id = 0x101;
    m_CanFrame.can_dlc = 2;
    
    while (1)
    {
        {
            std::unique_lock<std::mutex> ul(g_Mutex);
            g_Cv.wait(ul, [] { return g_Flag; });       // will unlock the g_Mutex as well if cond is not meet
                                                        // if condition true will lock the mutex and go on
            g_Flag = false;
        }
        // printf("Can: %s\n", g_Buffer);
        number = atoi(g_Buffer);
        printf("Can number: %d\n", number);
        m_CanFrame.data[1] = (number & 0xFF00) >> 8; 
        m_CanFrame.data[0] = (number & 0xFF); 

        printf("Sending...%d - %d\n", m_CanFrame.data[1], m_CanFrame.data[0]);
        write(m_CanSocketfd, &m_CanFrame, sizeof(can_frame));

    }
    
}

