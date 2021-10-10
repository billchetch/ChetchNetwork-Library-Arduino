#include <ChetchEthernetManager.h>

namespace Chetch{

bool EthernetManager::trace = false;

//TODO: implement timeout
bool EthernetManager::begin(byte* mac, int timeout){
    
    unsigned long started = millis();

    if(trace)Serial.println("Starting ethernet...");
    Ethernet.begin(mac); //, ip, myDns, gateway, subnet);

  	// Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        if(trace)Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        return false;
    } else {
        if(trace)Serial.println("Hardware connection ok");
    }

    if (Ethernet.linkStatus() == LinkOFF) {
        if(trace)Serial.println("Ethernet cable is not connected.");
        return false;
    } else {
        if(trace){
            Serial.println("Link status on");
            Serial.println("Local IP: ");
            Serial.println(Ethernet.localIP());
        }
        return true;
    }
}

} //end namespace