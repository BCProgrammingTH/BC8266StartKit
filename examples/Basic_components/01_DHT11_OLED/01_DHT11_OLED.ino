/*
Library Source
 - https://github.com/adafruit/DHT-sensor-library.git
 - https://github.com/adafruit/Adafruit_Sensor.git
 - https://github.com/adafruit/Adafruit_SSD1306.git
 - https://github.com/adafruit/Adafruit-GFX-Library.git
 - https://github.com/adafruit/Adafruit_BusIO.git
*/

#include <SPI.h>               // เรียกใช้ไลบรารี SPI สำหรับการสื่อสาร
#include <Wire.h>              // เรียกใช้ไลบรารี Wire สำหรับการสื่อสาร I2C
#include <Adafruit_GFX.h>      // ไลบรารีสำหรับการสร้างกราฟิกพื้นฐาน
#include <Adafruit_SSD1306.h>  // ไลบรารีสำหรับหน้าจอ OLED SSD1306

// กำหนดขนาดหน้าจอ OLED
#define SCREEN_WIDTH 128     // ความกว้างของหน้าจอ OLED (พิกเซล)
#define SCREEN_HEIGHT 32     // ความสูงของหน้าจอ OLED (พิกเซล)
#define OLED_RESET -1        // พิน RESET ของหน้าจอ OLED (ไม่ใช้)
#define SCREEN_ADDRESS 0x3C  // ที่อยู่ I2C ของหน้าจอ OLED
//#define SCREEN_ADDRESS 0x3D              // ที่อยู่ I2C ของหน้าจอ OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // สร้างอ็อบเจ็กต์หน้าจอ OLED

// เรียกใช้ไลบรารีสำหรับเซ็นเซอร์ DHT
#include "DHT.h"

// กำหนดพินที่เชื่อมต่อกับเซ็นเซอร์ DHT
#define DHTPIN D5      // พินเชื่อมต่อเซ็นเซอร์ DHT
#define DHTTYPE DHT11  // กำหนดประเภทของเซ็นเซอร์เป็น DHT11
//#define DHTTYPE DHT22                    // กำหนดประเภทของเซ็นเซอร์เป็น DHT22
//#define DHTTYPE DHT21   // กำหนดประเภทของเซ็นเซอร์เป็น DHT21
// สร้างอ็อบเจ็กต์เซ็นเซอร์ DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  // เริ่มต้นการสื่อสาร Serial สำหรับการดีบัก

  // ตรวจสอบการเริ่มต้นหน้าจอ OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));  // แสดงข้อความหากหน้าจอ OLED ทำงานล้มเหลว
    for (;;)
      ;  // วนลูปตลอดไป
  }

  dht.begin();  // เริ่มต้นเซ็นเซอร์ DHT
}

void loop() {
  delay(2000);  // รอเวลา 2 วินาทีระหว่างการอ่านค่าต่อครั้ง

  // อ่านค่าความชื้นและอุณหภูมิ
  float h = dht.readHumidity();         // อ่านค่าความชื้น
  float t = dht.readTemperature();      // อ่านค่าอุณหภูมิ (เซลเซียส)
  float f = dht.readTemperature(true);  // อ่านค่าอุณหภูมิ (ฟาเรนไฮต์)

  // ตรวจสอบว่าการอ่านค่าล้มเหลวหรือไม่
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));  // แสดงข้อความหากการอ่านค่าล้มเหลว
    return;
  }

  // แสดงค่าความชื้นและอุณหภูมิใน Serial Monitor
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.println("°F");

  // แสดงผลข้อมูลบนหน้าจอ OLED
  display.clearDisplay();                       // ลบข้อมูลบนหน้าจอ
  display.setTextSize(1);                       // กำหนดขนาดข้อความ
  display.setTextColor(SSD1306_WHITE);          // ตั้งค่าสีข้อความเป็นสีขาว
  display.setCursor(0, 0);                      // ตั้งตำแหน่งเริ่มต้นของข้อความ
  display.println("Temp");                      // แสดงข้อความ "Temp"
  display.println(" - " + String(t) + " C");    // แสดงค่าอุณหภูมิในหน่วยเซลเซียส
  display.println(" - " + String(f) + " F");    // แสดงค่าอุณหภูมิในหน่วยฟาเรนไฮต์
  display.println("Humi " + String(h) + " %");  // แสดงค่าความชื้น
  display.display();                            // อัปเดตหน้าจอ OLED เพื่อแสดงผล
}
