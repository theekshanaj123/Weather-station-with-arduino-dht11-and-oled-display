#include "DHT.h"
#define DHT11Pin 2
#define DHTType DHT11

DHT HT(DHT11Pin, DHTType);
float humi;
float tempC;
float tempF;

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Pins for the OLED display (change these according to your wiring)
#define OLED_DC     9
#define OLED_CS     10
#define OLED_RESET  11

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  Serial.begin(9600);

  HT.begin();

  // For OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  delay(1000);

  humi = HT.readHumidity();
  tempC = HT.readTemperature();
  tempF = HT.readTemperature(true);

  Serial.print("Humidity:");
  Serial.print(humi, 0);
  Serial.print("%");
  Serial.print(" Temperature:");
  Serial.print(tempC, 1);
  Serial.print("C   ~ ");
  Serial.print(tempF, 1);
  Serial.println("F");

  display.clearDisplay();
  oledDisplayHeader();

  oledDisplay(3, 5, 28, humi, "%");
  oledDisplay(2, 70, 16, tempC, "C");
  oledDisplay(2, 70, 44, tempF, "F");

  display.display();
}

void oledDisplayHeader() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Humidity");
  display.setCursor(60, 0);
  display.print("Temperature");
}

void oledDisplay(int size, int x, int y, float value, String unit) {
  int charLen = 12;
  int xo = x + charLen * 3.2;
  int xunit = x + charLen * 3.6;
  int xval = x;
  display.setTextSize(size);
  display.setTextColor(WHITE);

  if (unit == "%") {
    display.setCursor(x, y);
    display.print(value, 0);
    display.print(unit);
  } else {
    if (value > 99) {
      xval = x;
    } else {
      xval = x + charLen;
    }
    display.setCursor(xval, y);
    display.print(value, 0);
    display.drawCircle(xo, y + 2, 2, WHITE);
    display.setCursor(xunit, y);
    display.print(unit);
  }
}
