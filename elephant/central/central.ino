
#include <ArduinoBLE.h>

int windowPointer = 0;
const int windowLength = 15;
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
  Serial.println("ATTEMPTING CONNECT");
    if (dev.connect()) {
      Serial.println("Connected");
      while(dev.connected()) {
        BLE.poll();
        bluetoothLoop(dev.rssi());
        delay(20);
      }
    } else {
      Serial.println("Failed to connect!");
      return;
    }
      BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
//    
//  digitalWrite(LED_BUILTIN, HIGH);
//  delay(250); // ms
//  digitalWrite(LED_BUILTIN, LOW);
//  BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
}

void bluetoothLoop(int signalStrength) {
  window[windowPointer] = signalStrength;
  windowPointer = (windowPointer + 1) % windowLength;
  int sum = 0;
  for (int i = 0; i < windowLength; i ++) {
    sum += window[i];
  }
  Serial.println(sum/windowLength/5 * -1);
}

void loop() {
  BLE.poll();
}
