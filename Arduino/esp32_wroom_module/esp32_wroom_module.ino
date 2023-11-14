#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <esp_gap_ble_api.h>

#define SERVICE_UUID           "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID    "beb5483e-36e1-4688-b7f5-ea07361b26a8"


BLEServer *pServer = nullptr;
BLEService *pService = nullptr;
BLECharacteristic *pCharacteristic = nullptr;
bool deviceConnected = false;
esp_bd_addr_t deviceAddress; // This will hold the address of the connected device

// Define the BLE frequency in Hertz (2400 MHz for BLE)
const double frequency = 2400e6; // 2.4 GHz in Hz
const double distanceMeters = 1;

// Function to calculate FSPL in dB, given the distance in meters
double calculateFSPL() {
  // Convert frequency to GHz for the FSPL formula
  double frequencyGHz = frequency / 1e9;
  // FSPL formula
  double distanceKilometers = distanceMeters / 1000.0; // Convert meters to kilometers

  double fspl = 20 * log10(distanceKilometers) + 20 * log10(frequencyGHz) + 92.45;

  return fspl;
}



class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer, esp_ble_gatts_cb_param_t *param) {
      Serial.println("Client connected");
      deviceConnected = true;
      memcpy(deviceAddress, param->connect.remote_bda, sizeof(esp_bd_addr_t));
      // Call the ESP-IDF API to read the RSSI
      esp_ble_gap_read_rssi(deviceAddress);
    };

    void onDisconnect(BLEServer* pServer) {
      Serial.println("Client disconnected");
      deviceConnected = false;
      pServer->startAdvertising(); // Restart advertising
    }
};

// Register the GAP event handler with a static member function
static void my_gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t* param) {
  if (event == ESP_GAP_BLE_READ_RSSI_COMPLETE_EVT) {
    if (param->read_rssi_cmpl.status == ESP_BT_STATUS_SUCCESS) {
      int rssi = param->read_rssi_cmpl.rssi;
      Serial.printf("RSSI of connected device: %d dBm\n", rssi);

      // Calculate FSPL
      double fspl = calculateFSPL();
      Serial.printf("Theoretical FSPL: %f dB\n", fspl);

    }
  }
}

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32_BLE_Test");

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
                    );

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06); 
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");

  esp_ble_gap_register_callback(my_gap_event_handler);
}

void loop() {
}