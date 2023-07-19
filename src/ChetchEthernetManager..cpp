#include <ChetchEthernetManager.h>

namespace Chetch{

bool EthernetManager::trace = false;

//TODO: implement timeout
bool EthernetManager::begin(byte* mac, byte* ip, byte* dns, byte* gateway, byte* subnet, int timeout){
    
    unsigned long started = millis();
    bool begun = false;
    bool timedOut = false;
    do{
        if(trace){
            Serial.print("Beginning Ethernet with mac: ");
            char macAddr[18];
            sprintf(macAddr, "%2X:%2X:%2X:%2X:%2X:%2X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            Serial.println(macAddr);
        }
        Ethernet.begin(mac, ip, dns, gateway, subnet);


        delay(100);

        // Check for Ethernet hardware present
        if (hardwareError()) {
            if(trace)Serial.println("No hardware found.  Sorry, can't run without hardware. :(");
            begun = false;
        } else {
            if(trace)Serial.println("Hardware connection ok");
        }

        delay(100);

        //check or link error
        if(!isLinked()) {
            if(trace)Serial.println("Ethernet not linked");
            begun = false;
        } else {
            if(trace)Serial.println("Ethernet is linked");
            begun = true;
        }

        if(!begun && timeout > 0){
            timedOut = millis() - started > timeout;
            if(timedOut && trace)Serial.println("Ethernet begin process timed out");
        }

        if(!begun)delay(500);
    } while(!begun && !timedOut);

  	if(begun){
        if(trace){
            Serial.print("Ethernet has begun with IP: ");
            Serial.println(Ethernet.localIP());
        }
        return true;
    } else {
        if(trace){
            Serial.println("Ethernet failed to begin!");
        }
        return false;
    }
}

bool EthernetManager::begin(byte* mac, byte* ip, byte* router, byte* subnet, int timeout){
    return EthernetManager::begin(mac, ip, router, router, subnet, timeout);
}

bool EthernetManager::isLinked(){
    return Ethernet.linkStatus() == EthernetLinkStatus::LinkON;
}

bool EthernetManager::hardwareError(){
    Ethernet.hardwareStatus() == EthernetNoHardware;
}

void EthernetManager::resetHardware(byte resetPin){
    if(trace)Serial.println("Perform hardware reset...");
    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, LOW);
    delay(100);
    pinMode(resetPin, INPUT);
    delay(2000); //allow time to return high
    if(trace)Serial.println("Reset complete attempting to begin ethernet again...");
}

} //end namespace