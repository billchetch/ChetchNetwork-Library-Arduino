#ifndef CHETCH_WIFIMANAGER_H
#define CHETCH_WIFIMANAGER_H

#include <ESP8266WiFi.h>

namespace Chetch{

class WifiManager{
    public:
        static bool trace;
        static bool connect(const char *hostname, const char *ssid, const char *password, int timeout = -1);
};

} //end namespace

#endif