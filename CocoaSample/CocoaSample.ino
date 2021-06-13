#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define COCOA_ID    "fd6f"

BLEScan *pBLEScan;
static uint8_t cocoa_count_ = 0;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      //サービスuuidをもっているなら
      if (advertisedDevice.haveServiceUUID())
        if (advertisedDevice.getServiceUUID().toString().find(COCOA_ID) == 4) {
          cocoa_count_++;
          Serial.printf("service: %s\n", advertisedDevice.getServiceUUID().toString().c_str());
        }
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

void initBLE_Scan()
{
    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan(); //create new scan
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99); // less or equal setInterval value
}

void scan(uint8_t sec_scan_time)
{
    BLEScanResults foundDevices = pBLEScan->start(sec_scan_time, false);
}

void clearCocoaCount()
{
    cocoa_count_ = 0;
    pBLEScan->clearResults();
}

void setup()
{
    initBLE_Scan();
    Serial.begin(115200);
    delay(1000);
}

void loop()
{
    scan(5);
    Serial.print("Cocoa count:");
    Serial.println(cocoa_count_);
    clearCocoaCount();
    delay(1000);
}
