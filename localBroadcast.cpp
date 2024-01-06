#include "localBroadcast.hpp"

localBroadcast::localBroadcast(UDP *udp, uint16_t port, uint16_t maxPacketSize)
{
    this->localPort = port;
    this->Udp = udp;
    this->packetSizeLimit = maxPacketSize;
}

void localBroadcast::begin()
{
    this->Udp->begin(this->localPort);
}

uint8_t localBroadcast::loop(void (*receivedInterruptFunction)(char *receivedData, uint16_t receivedDataLength))
{
    int packetSize = Udp->parsePacket();
    if (packetSize)
    {
        if (packetSize + 1 > packetSizeLimit)
            return 1; // Error: Packet size is bigger than packet size limit

        char *incomingPacket = (char *)malloc(packetSize + 1);

        int len = Udp->read(incomingPacket, packetSize);
        if (len > 0)
            incomingPacket[len] = 0;

        receivedInterruptFunction(incomingPacket, packetSize);

        free(incomingPacket);
    }
    return 0; // No error
}

void localBroadcast::send(char *data, uint16_t dataLength)
{
    Udp->beginPacket(IPAddress(255, 255, 255, 255), this->localPort);
    Udp->write((uint8_t *)data, dataLength);
    Udp->endPacket();
}