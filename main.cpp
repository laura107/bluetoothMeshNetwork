#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEMesh.h>

// Define callback function for handling received mesh messages
void onMeshReceive(uint32_t from, uint32_t to, uint8_t ttl, uint8_t* data, size_t len) {
    Serial.print("Received mesh message from node ");
    Serial.print(from);
    Serial.print(": ");
    for (size_t i = 0; i < len; i++) {
        Serial.print(data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);

    BLEDevice::init("MyMeshDevice");
    BLEMesh::init();

    BLEMesh::setNodeAddress(1);
    BLEMesh::setNetKeyIndex(0);
    BLEMesh::setAppKeyIndex(0);

    BLEMesh::onReceive(onMeshReceive);

    BLEMesh::startAdvertising();
    BLEMesh::joinMesh();
}

void loop() {
    uint8_t data[] = {0x01, 0x02, 0x03};
    BLEMesh::sendMessage(2, data, sizeof(data));

    delay(1000);
}
