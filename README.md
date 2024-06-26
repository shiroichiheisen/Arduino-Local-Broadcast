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
   
   localBroadcast broadcast(&udp);  // Default port is 12345 and maxPacketSize to receive is 255
    // or
    localBroadcast broadcast(&udp, 4210, 512);  // Custom port and maxPacketSize to receive
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
      broadcast.setLoopFunction(handleReceivedData); // Set the function to call when a message is received, this is not mandatory if you have already set it with the loop function
      uint8_t error = broadcast.loop(handleReceivedData); // Call the loop function if a message is received, the function to call is not mandatory if you have already set it with setLoopFunction
      // Error handling
      if (error == 1) {
         Serial.println("Packet too large to receive");
      } else if (error == 2) {
         Serial.println("Error on allocating memory for packet, not enough memory");
      }

       // ... other code
   }
   ```

**5. Send a broadcast message:**

   ```c++
   char message[] = "Hello, network!";
   broadcast.send(message, sizeof(message));
   ```

**Additional notes:**

- The `handleReceivedData` function is called when a message is received. The function takes two arguments: a pointer to the received data and the length of the received data.
- The `send` function takes two arguments: a pointer to the data to send and the length of the data to send.
- The `loop` function takes one argument: a pointer to the function to call when a message is received.
- The `maxPacketSize` argument in the `localBroadcast` constructor is the maximum size of the packet to receive. If the received packet is larger than this size, the `handleReceivedData` function will not be called and the `loop` function will return 1.
- The `loop` function returns 0 if no message is received, 1 if the received packet is larger than the `maxPacketSize` argument in the `localBroadcast` constructor and 2 if there is an error on allocating memory for the packet to receive.