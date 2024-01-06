# localBroadcast library for Arduino

**Easily send and receive broadcast messages on your local network with this Arduino library.**

**Features:**

- Sends broadcast messages to all devices on the network
- Receives broadcast messages from other devices
- Handles variable-length packet sizes
- Includes error handling

**Usage:**

**1. Include the library:**

   ```c++
   #include "localBroadcast.hpp"
   ```

**2. Create a localBroadcast object:**

   ```c++
   WiFiUDP udp;  // Assuming you have a Wifi UDP object defined
   // or
   ethernetUDP udp;  // Assuming you have an Ethernet UDP object defined
   localBroadcast broadcast(&udp);  // Default port is 12345 and maxPacketSize is 255
    // or
    localBroadcast broadcast(&udp, 4210, 512);  // Custom port and maxPacketSize
   ```

**3. Start listening for messages:**

   ```c++
   broadcast.begin();
   ```

**4. In your main loop, check for incoming messages:**

   ```c++
   void handleReceivedData(char *data, uint16_t length) {
       // Process the received data here
       Serial.println(data); // Print the received data to the serial monitor
       Serial.println(length); // Print the length of the received data
   }

   void loop() {
       broadcast.loop(handleReceivedData); // Call the loop function if a message is received
       //  returns 1 if the received packet size is greater than maxPacketSize and 0 if not

       // ... other code
   }
   ```

**5. Send a broadcast message:**

   ```c++
   char message[] = "Hello, network!";
   broadcast.send(message, sizeof(message));
   ```
