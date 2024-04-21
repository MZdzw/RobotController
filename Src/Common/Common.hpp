#ifndef __COMMON_HPP__
#define __COMMON_HPP__
#include <mutex>
#include <condition_variable>

extern std::mutex g_Mutex;
extern std::condition_variable g_Cv;
extern bool g_Flag;
extern char g_Buffer[256];


#endif
