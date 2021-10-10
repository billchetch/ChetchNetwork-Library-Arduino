#ifndef CHETCH_WIFIMANAGER_H
#define CHETCH_WIFIMANAGER_H

#if defined(ESP8266)

#include <ESP8266WiFi.h>

namespace Chetch{

class WifiManager{
    public:
        enum WifiEvent{
            CONNECTED = 1,
            GOT_IP = 2,
            DISCONNECTED = 3,
            DHCP_TIMEOUT = 4, //to do
        };

    private:
        static bool connected;
        static bool ip;
        static WiFiEventHandler connectEventHandler;
        static WiFiEventHandler gotIPEventHandler;
        static WiFiEventHandler disconnectEventHandler;
        static void onConnect(const WiFiEventStationModeConnected& event);
        static void onGotIP(const WiFiEventStationModeGotIP& event);
        static void onDisconnect(const WiFiEventStationModeDisconnected& event);

        static void (*eventHandler)(WifiEvent);
        
    public:
        static bool trace;
        static bool connect(const char *hostname, const char *ssid, const char *password, void (*handler)(WifiEvent) = NULL, int timeout = -1);
        static bool isConnected();
        static bool hasIP();
};

} //end namespace
#endif

#endif