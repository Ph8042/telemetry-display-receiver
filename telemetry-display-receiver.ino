#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin (if not used, set -1)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // display init
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // check your i2c address first!
    Serial.println(F("init error SSD1306"));
    for(;;);
  }

  // clear buffer
  display.clearDisplay();

  // text color
  display.setTextColor(SSD1306_WHITE);

  // text size
  display.setTextSize(1);
}

// my display is 21 characters wide and 7 characters tall
void loop()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(" ");
  display.println(" ");
  display.println(" ");
  display.println("hello");
  display.println(" ");
  display.println(" ");
  display.println(" ");
  display.display();
  delay(2000);
}