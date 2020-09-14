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

void loop()
{
  int aqi = GetAqi();
  Serial.println(aqi);

  if(aqi < 50){
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 255);
  }
  else if(aqi < 100){
    analogWrite(REDPIN, 0);
    analogWrite(GREENPIN, 255);
    analogWrite(BLUEPIN, 0);
  }
  else if(aqi < 200){
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 215);
    analogWrite(BLUEPIN, 0);
  }
  else if(aqi < 250){
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 70);
    analogWrite(BLUEPIN, 0);
  }
  else if(aqi < 300){
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 0);
    analogWrite(BLUEPIN, 0);
  }
  else{
    analogWrite(REDPIN, 255);
    analogWrite(GREENPIN, 255);
    analogWrite(BLUEPIN, 255);
  }
  delay(60 * 60 * 5);
}
