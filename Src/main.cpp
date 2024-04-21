#include <thread>
#include "Peripherals/Gpio.hpp"
#include "Network/server.hpp"
#include "Peripherals/Can.hpp"

#define LED_PATH "/sys/class/gpio/gpio60"

std::mutex g_Mutex;
std::condition_variable g_Cv;
bool g_Flag = false;
char g_Buffer[256] = { 0 };


int main(void)
{
    std::thread gpioThread(&BlinkingLEDThread);
    std::thread tcpThreadsHandler(&ServerTCP::TcpHandlerThread);
    std::thread canThread(&Can::CanHandlerThread);

    gpioThread.join();
    tcpThreadsHandler.join();
    canThread.join();

    return 0;
}
