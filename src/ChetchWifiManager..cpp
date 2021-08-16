#include <ChetchWifiManager.h>

namespace Chetch{

bool WifiManager::trace = false;

bool WifiManager::connect(const char *hostname, const char *ssid, const char *password, int timeout){
    WiFi.hostname(hostname);
    WiFi.mode(WIFI_STA);

    if(trace){
        Serial.print("Attempting to connect to Wifi ");
        Serial.println(ssid);
    }
    WiFi.begin(ssid, password); //Connect to wifi

    // Wait for connection  
    if(trace)Serial.println("Waiting for connection...");
        while (WiFi.status() != WL_CONNECTED) {   
        delay(500);
        if(trace){
            Serial.print(".");
            delay(500);
        }
    }

    bool connected = WiFi.status() == WL_CONNECTED;
    if(trace){
        if(connected){
            Serial.println("");
            Serial.print("Connected to ");
            Serial.println(ssid);
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
        } else {
            Serial.println("Failed to connect!");
        }
    }
    return connected;
}

} //end namespace