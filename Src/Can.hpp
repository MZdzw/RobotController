#ifndef __CAN_HPP__
#define __CAN_HPP__
#include <linux/can.h>
#include <linux/can/raw.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <cstring>

#include <unistd.h> // for write

class Can
{
private:
    int m_CanSocketfd;
    sockaddr_can m_CanAddr;
    ifreq m_Ifr;
    can_frame m_CanFrame;

    int m_Bytes;

public:
    Can()
    : m_CanSocketfd(-1), m_Bytes(0)
    {
        m_CanSocketfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
        strcpy(m_Ifr.ifr_name, "can0");
        ioctl(m_CanSocketfd, SIOCGIFINDEX, &m_Ifr);
        memset(&m_CanAddr, 0, sizeof(m_CanAddr));
        m_CanAddr.can_family = AF_CAN;
        m_CanAddr.can_ifindex = m_Ifr.ifr_ifindex;
        bind(m_CanSocketfd, reinterpret_cast<sockaddr*>(&m_CanAddr), sizeof(m_CanAddr));
    }

    static void CanHandlerThread();
    void CanReceiverThread();
    void CanSenderThread();

};

#endif
