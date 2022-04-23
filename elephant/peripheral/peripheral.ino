#include <ArduinoBLE.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  
  delay(2000);
  Serial.println("Started Serial");
  
  //initialize BLE
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  
  BLE.debug(Serial);
  BLE.setLocalName("LL0"); // set advertised local name
  BLE.setAdvertisedServiceUuid("19B10000-E8F2-537E-4F6C-D104768A1214");

  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  
  BLE.advertise(); // start advertising
  Serial.println("BLE Peripheral advertising initiated. Minimac");
}

void blePeripheralConnectHandler(BLEDevice central) {
    Serial.println("Connected central: ");
    Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
    Serial.println("hm central: ");
    Serial.println(central.address());
}

void loop() {
  BLE.poll();
}
