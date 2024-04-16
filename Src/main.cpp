#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <fstream>
#include "server.hpp"
#include "Can.hpp"

#define LED_PATH "/sys/class/gpio/gpio60"

std::mutex g_Mutex;
std::condition_variable g_Cv;
bool g_Flag = false;
char g_Buffer[256] = { 0 };

typedef enum State_e
{
    LOW, HIGH
}State_e;

void writeLED(State_e state)
{
    FILE* fptr;
    char filePath[30];
    strcpy(filePath, LED_PATH);
    strcat(filePath, "/value");
    std::fstream file;
    file.open(filePath, std::ios::out);
    if (state == HIGH) 
    {
       file << "1";
    }
    else 
    {
       file << "0";
    }
    file.flush();
    file.close();
}

void foo(int cnt)
{
    using namespace std::chrono_literals;
    std::cout << "Beginning of foo thread\n";

    for(int i = 0; i < cnt; ++i)
    {
        writeLED(HIGH);
        std::this_thread::sleep_for(1000ms);
        writeLED(LOW);
        std::this_thread::sleep_for(1000ms);
    }

}

int main(void)
{
    std::thread gpioThread(foo, 10);
    std::thread tcpThreadsHandler(&ServerTCP::TcpHandlerThread);
    std::thread canThread(&Can::CanHandlerThread);

    gpioThread.join();
    tcpThreadsHandler.join();
    canThread.join();

    return 0;
}
