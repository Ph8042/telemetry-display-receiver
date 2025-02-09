#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin (if not used, set -1)

const char *ssid = "";
const char *password = "";
const char *mqtt_server = "";
const char *mqtt_user = "";
const char *mqtt_password = "";
const int mqtt_port = ;
const char *mqtt_topic = "";

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup_display()
{
  // display init
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // check your i2c address first!
    Serial.println(F("init error SSD1306"));
    for(;;);
  }
  display.clearDisplay(); // clear buffer
  display.setTextColor(SSD1306_WHITE);  // text color
  display.setTextSize(1);  // text size
  display.println("display: initialized");  
  display.display();
}

void setup_wifi()
{
  Serial.println("");
  Serial.println("connecting with wifi...");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }

  Serial.println("Succesfully connected with Wi-Fi");
  display.println("wifi: initialized");
  display.display();
}

void setup_mqtt()
{
  client.setServer(mqtt_server, mqtt_port);

  while (!client.connected())
  {
    Serial.print("connecting with MQTT...");

    if (client.connect("ESPDisplayClient", mqtt_user, mqtt_password))
    {
      Serial.println("succesfully connected with mqtt...");
      client.subscribe(mqtt_topic);
    }
    else
    {
      Serial.print("Error, rc=");
      Serial.print(client.state());
      Serial.println(" retry in 5 second...");
      delay(5000);
    }
  }

  Serial.println("Succesfully connected with mqtt");
  display.println("mqtt: initialized");
  display.display();
}

void callback(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  snprintf(message, sizeof(message), "%.*s", length, payload);
  
  if (String(topic) == mqtt_topic) {
    float temperature = atof(message);
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Value: ");
    display.println(temperature, 2); // display with 2 decimal places
    display.display();
  }
}

void setup() {
  Serial.begin(115200);
  setup_display();
  setup_wifi();
  setup_mqtt();
  display.clearDisplay();
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected()) {
    setup_mqtt();
  }
  client.loop();
}