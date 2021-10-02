#include <ChetchWifiManager.h>

namespace Chetch{

bool WifiManager::trace = false;
WiFiEventHandler WifiManager::connectEventHandler;
WiFiEventHandler WifiManager::gotIPEventHandler;
WiFiEventHandler WifiManager::disconnectEventHandler;
void (*WifiManager::eventHandler)(WifiEvent) = NULL;
bool WifiManager::connected = false;
bool WifiManager::ip = false;


void WifiManager::onConnect(const WiFiEventStationModeConnected& event){
  connected = true;
  ip = false;
  if(trace){
        Serial.println("Connected to wifi");
  }

  if(eventHandler != NULL){
        eventHandler(WifiEvent::CONNECTED);
  }
}

void WifiManager::onGotIP(const WiFiEventStationModeGotIP& event){
    ip = true;
    
    if(trace){
        Serial.print("Obtained IP: ");
        Serial.println(WiFi.localIP());
    }
    if(eventHandler != NULL){
        eventHandler(WifiEvent::GOT_IP);
    }
}

void WifiManager::onDisconnect(const WiFiEventStationModeDisconnected& event){
  connected = false;
  ip = false;
  if(trace){
       Serial.println("Disconnected");
  }
  if(eventHandler != NULL){
        eventHandler(WifiEvent::DISCONNECTED);
  }
}

bool WifiManager::connect(const char *hostname, const char *ssid, const char *password, void (*handler)(WifiEvent), int timeout){
    WiFi.hostname(hostname);
    WiFi.mode(WIFI_STA);
    connectEventHandler = WiFi.onStationModeConnected(WifiManager::onConnect);
    gotIPEventHandler = WiFi.onStationModeGotIP(WifiManager::onGotIP);
    disconnectEventHandler = WiFi.onStationModeDisconnected(WifiManager::onDisconnect);
    eventHandler = handler;

    unsigned long started = millis();

    if(trace){
        Serial.print("Attempting to connect to Wifi ");
        Serial.println(ssid);
    }

    WiFi.begin(ssid, password); //Connect to wifi

    // Wait for connection  
    //TODO: implement timeout
    if(trace)Serial.println("Waiting for connection...");
        while (WiFi.status() != WL_CONNECTED) {   
        delay(500);
        if(trace){
            Serial.print(".");
            delay(500);
        }
        if(timeout > 0 && started - millis() > timeout){
            break;
        }
    }

    if(trace){
        if(!connected){
            Serial.println("Failed to connect!");
        }
    }

    return connected;
}

bool WifiManager::isConnected(){
    return connected;
}

bool WifiManager::hasIP(){
    return ip;
}

} //end namespace