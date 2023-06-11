#include <ChetchEthernetManager.h>

namespace Chetch{

bool EthernetManager::trace = false;

//TODO: implement timeout
bool EthernetManager::begin(byte* mac, byte* ip, byte* dns, byte* gateway, byte* subnet, int timeout){
    
    unsigned long started = millis();

    if(trace){
        Serial.print("Starting ethernet with mac");
        char macAddr[18];
        sprintf(macAddr, "%2X:%2X:%2X:%2X:%2X:%2X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        Serial.println(macAddr);
    }
    Ethernet.begin(mac, ip, dns, gateway, subnet);

  	// Check for Ethernet hardware present
    if (hardwareError()) {
        if(trace)Serial.println("No hardware found.  Sorry, can't run without hardware. :(");
        return false;
    } else {
        if(trace)Serial.println("Hardware connection ok");
    }

    if(trace){
        Serial.print("Local IP: ");
        Serial.println(Ethernet.localIP());
    }
    return true;
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

} //end namespace