#ifndef localBroadcast_h
#define localBroadcast_h

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

class localBroadcast
{
public:
    localBroadcast(UDP *udp, uint16_t port = 12345, uint16_t maxPacketSize = 256);
    void begin();
    uint8_t loop(void (*receivedInterruptFunction)(char *receivedData, uint16_t receivedDataLength));
    void send(char *data, uint16_t dataLength);

private:
    UDP *Udp;
    uint16_t localPort;
    uint16_t packetSizeLimit;
};

#endif