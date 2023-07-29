#ifndef CHETCH_NETWORK_API_H
#define CHETCH_NETWORK_API_H

#include <Ethernet.h>
//#include <Ethernet2.h>

namespace Chetch{

class NetworkAPI{
    public:
        static bool trace;
        static int registerService(Client& client, IPAddress networkServiceIP, int networkServicePort, const char *serviceName, int port, int timeout = -1);
        static int registerService(Client& client, byte *networkServiceIP, int networkServicePort, const char *serviceName, int port, int timeout = -1);
        static int registerService(Client& client, const char *networkServiceIP, int networkServicePort, const char *serviceName, int port, int timeout = -1);
};

} //end namespace

#endif