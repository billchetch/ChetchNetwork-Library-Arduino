#ifndef CHETCH_ETHERNETMANAGER_H
#define CHETCH_ETHERNETMANAGER_H

#include <SPI.h>
//#include <Ethernet.h>
#include <EthernetENC.h>

namespace Chetch{

class EthernetManager{
    public:
        static bool trace;
        static bool begin(byte* mac, byte* ip, byte* dns, byte* gateway, byte* subnet, int timeout = -1);
	    static bool begin(byte* mac, byte* ip, byte* router, byte* subnet, int timeout = -1);
        static bool isLinked();
};

} //end namespace

#endif