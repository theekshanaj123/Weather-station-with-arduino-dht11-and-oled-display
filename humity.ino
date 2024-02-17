#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>


#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define DHTPIN 2       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT 11

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

DHT dht(DHTPIN, DHTTYPE);

float humidity;
float temperature;


void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  dht.begin();
}

void loop() {
  checkHu();
  printtext();
}

void printtext(void) {
  display.clearDisplay();
  display.setTextSize(1.9);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 1);
  display.print("Humidity:");
  display.setTextSize(2);
  display.println(humidity);
  display.setTextSize(1.9);
  display.setCursor(0, 25);
  display.print("Temper:  ");
  display.setTextSize(2);
  display.println(temperature);
  display.display();
  delay(2000);
}

void checkHu(void) {
  delay(100);  // Wait for 2 seconds between measurements

  humidity = dht.readHumidity();              // Read humidity
  temperature = dht.readTemperature();  // Read temperature in Celsius (the default)

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
}