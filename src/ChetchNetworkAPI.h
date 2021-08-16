#ifndef CHETCH_NETWORK_API_H
#define CHETCH_NETWORK_API_H

#include <ESP8266HTTPClient.h>

namespace Chetch{

class NetworkAPI{
    public:
        static bool trace;
        static bool registerService(const char *networkServiceURL, const char *serviceName, int port, int timeout = -1);
};

} //end namespace

#endif