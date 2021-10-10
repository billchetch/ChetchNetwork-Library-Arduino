#ifndef CHETCH_ETHERNETMANAGER_H
#define CHETCH_ETHERNETMANAGER_H

#include <SPI.h>
//#include <Ethernet.h>
#include <EthernetENC.h>

namespace Chetch{

class EthernetManager{
    public:
        static bool trace;
        static bool begin(byte* mac, int timeout = -1);        ;
};

} //end namespace

#endif