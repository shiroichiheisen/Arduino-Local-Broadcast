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

void localBroadcast::setLoopFunction(void (*receivedInterruptFunction)(char *receivedData, uint16_t receivedDataLength))
{
    this->receivedInterruptFunction = receivedInterruptFunction;
}

uint8_t localBroadcast::loop(void (*receivedInterruptFunction)(char *receivedData, uint16_t receivedDataLength))
{
    if (receivedInterruptFunction != nullptr)
        this->receivedInterruptFunction = receivedInterruptFunction;

    if (this->receivedInterruptFunction == nullptr)
        return 3; // Error: No interrupt function set

    uint32_t packetSize = Udp->parsePacket();
    if (!packetSize)
        return 0; // No packet received

    if (packetSize + 1 > packetSizeLimit)
        return 1; // Error: Packet size is bigger than packet size limit

    char *incomingPacket = (char *)malloc(packetSize + 1);

    if (incomingPacket == NULL)
        return 2; // Error: Memory allocation failed

    uint16_t len = Udp->read(incomingPacket, packetSize);
    if (len > 0)
        incomingPacket[len] = 0;

    this->receivedInterruptFunction(incomingPacket, packetSize);

    free(incomingPacket);

    return 0; // No error
}

void localBroadcast::send(char *data, uint16_t dataLength)
{
    Udp->beginPacket(IPAddress(255, 255, 255, 255), this->localPort);
    Udp->write((uint8_t *)data, dataLength);
    Udp->endPacket();
}