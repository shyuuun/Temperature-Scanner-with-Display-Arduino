// kokutaro
// DHT 11 libs
#include <DHT.h>
#include <DHT_U.h>

// i2c display libs
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  delay(2000);
  display.clearDisplay();

  showTemp();

}

void loop() {
    showTemp();
}

void showTemp(void){
  float h = dht.readHumidity(); // humid
  float t = dht.readTemperature(); // temp
  int result = dht.computeHeatIndex(t, h, false);


  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.print(t);
  display.println();
  display.print("Humidity: ");
  display.print(h);
  display.println();
  display.print("Heat Index: \t"); 
  display.print(result);
  display.display();

  // debug purpose

  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°F  Heat index: "));
  Serial.print(F("°C "));
  Serial.print(result);

}
