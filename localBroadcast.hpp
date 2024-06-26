#ifndef localBroadcast_h
#define localBroadcast_h

#include <Arduino.h>

class localBroadcast
{
public:
    localBroadcast(UDP *udp, uint16_t port = 12345, uint16_t maxPacketSize = 256);
    void begin();
    void setLoopFunction(void (*receivedInterruptFunction)(char *receivedData, uint16_t receivedDataLength));
    uint8_t loop(void (*receivedInterruptFunction)(char *receivedData, uint16_t receivedDataLength) = nullptr);
    void send(char *data, uint16_t dataLength);

private:
    UDP *Udp;
    uint16_t localPort;
    uint16_t packetSizeLimit;
    void (*receivedInterruptFunction)(char *receivedData, uint16_t receivedDataLength) = nullptr;
};

#endif