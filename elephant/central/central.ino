/*
  Elephant Central.ino Find the Bread Demo
  
  Acts as the 'central' (loaf)
  [Victor Hung](vhung@mit.edu)
*/

#include <ArduinoBLE.h>


// A larger window length means a more stable value,
// but the value will take longer to get there.
const int windowLength = 15;

// A higher resolution means you'll get more granularity,
// but too high of a resolution means there will be noise
int resolution = 5;

int windowPointer = 0;
int window[windowLength];


void setup() {
  Serial.begin(9600);
  delay(2000);

  BLE.begin();
  BLE.setEventHandler(BLEDiscovered, discovered);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
  Serial.println("setup complete");
}

void logDevice(BLEDevice dev) {
  Serial.print("BLE device found: ");
  Serial.print("address=");
  Serial.print(dev.address());
  Serial.print(", rssi=");
  Serial.print(dev.rssi());
  if (!dev.hasLocalName()) {
    Serial.println("");
    return;
  }
  Serial.print(", name=");
  Serial.print(dev.localName());
  Serial.println("");
}

void discovered(BLEDevice dev) {
  BLE.stopScan();
  logDevice(dev);
  Serial.println("Discovered, attempting to connect...");
  if (dev.connect()) {
    Serial.println("Connected!");
    while (dev.connected()) {
      // If connected, constantly run the 'bluetoothLoop'
      BLE.poll();
      bluetoothLoop(dev.rssi());
      delay(20);
    }
  } else {
    Serial.println("Failed to connect!");
    return;
  }
  BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
}

// This loop helps with the connection, but is then no longer used
void loop() {
  BLE.poll();
}

// This loop is used once the device is connected
void bluetoothLoop(int signalStrength) {
  window[windowPointer] = signalStrength;
  windowPointer = (windowPointer + 1) % windowLength;
  int sum = 0;
  for (int i = 0; i < windowLength; i++) {
    sum += window[i];
  }
  Serial.println(sum / windowLength / resolution * -1);
}
