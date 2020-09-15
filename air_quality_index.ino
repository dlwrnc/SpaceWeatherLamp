#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

HTTPClient http;

const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(6) + 2*JSON_ARRAY_SIZE(7) + JSON_ARRAY_SIZE(8) + 8*JSON_OBJECT_SIZE(1) + 3*JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + 30*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(9) + 940;
DynamicJsonDocument doc(capacity);

const char* ssid      = "SSID";
const char* password  = "PASSWORD";

const int GREENPIN = 12;
const int REDPIN = 14;
const int BLUEPIN = 13;
const String token = "YOUR_TOKEN";
const String host = "http://api.waqi.info/feed/kirkland/?token=";


void setup()
{
  // set pin modes
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  analogWrite(GREENPIN, 100);

  // begin serial and connect to WiFi
  Serial.begin(115200);
  delay(100);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    analogWrite(BLUEPIN, 100);
    delay(500);
    Serial.print(".");
  }
  
  analogWrite(BLUEPIN, 0);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}


int GetAqi() {
  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  Serial.print("full url query: ");
  Serial.println(host + token);
  http.begin(host + token);
  int httpCode = http.GET();
  if (httpCode > 0) { //Check for the returning code

    String payload = http.getString();
    Serial.print("OUTPUT CODE: ");
    Serial.println(httpCode);
    Serial.print("PAYLOAD: ");
    Serial.println(payload);
    deserializeJson(doc, payload); 
    const char* status = doc["status"];
    JsonObject data = doc["data"];
    int data_aqi = data["aqi"];
    Serial.print("AQI: ");
    Serial.println(data_aqi);
    return data_aqi; 
  }
  else {
    Serial.print("Error on HTTP request: ");
    Serial.print(httpCode);
    return httpCode;
  }
  http.end();
}


int calculate_red(int aqi) {
  int red = (aqi - 100) * 2.5;
  if (red <= 255) {
    if(red <= 0){
      return 0;
    }
    return red;
  }
  return 255;
}

int calculate_green(int aqi) {
  int green = 0;
  if (aqi <= 200) {
    green = aqi * 1.2;
  } else {
    green = (200 - (aqi - 200)) * 1.2;
  }
  if (green <= 255) {
    if (green < 0) {
      return 0;
    }
    return green;
  }
  return 255;
}

int calculate_blue(int aqi) {
  int blue = (100 - aqi) * 2.5;
  if (blue <= 255) {
    if(blue <= 0){
      return 0;
    }
    return blue;
  }
  return 255;
}

void loop()
{
  int aqi = GetAqi();
  Serial.println(aqi);

  int r = calculate_red(aqi);
  int g = calculate_green(aqi);
  int b = calculate_blue(aqi);

  Serial.print("RED: ");
  Serial.println(r);
  Serial.print("GREEN: ");
  Serial.println(g);
  Serial.print("BLUE: ");
  Serial.println(b);


  analogWrite(REDPIN, r);
  analogWrite(GREENPIN, g);
  analogWrite(BLUEPIN, b);
  delay(1000 * 60 * 1); // poll every minute
}
