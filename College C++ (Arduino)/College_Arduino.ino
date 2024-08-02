// Thing Speak API : CHM4LLFP12Z6DTSP
#include <DHT.h>


#define DHTTYPE DHT11  // DHT 11

// Initialize DHT sensor for normal 16mhz Arduino

#define THRESHOLD_WATER 35  // Water level threshold for flood detection
#define THRESHOLD_SMOKE 1000

#define WATER_SENSOR_PIN A1  // Analog pin connected to the water level sensor BROWN
#define SMOKE_SENSOR_PIN A2  // Analog pin connected to the MQ-135 smoke sensor WHITE
#define BUZZER_PIN 3         // Pin connected to the buzzer
#define DHTPIN 4             // Pin connected to the DHT11 sensorl

DHT dht(DHTPIN, DHTTYPE);

// Code for Thing Speak Starts

#include <SoftwareSerial.h>
#define RX 8                        // TX of esp8266 in connected with Arduino pin 2
#define TX 9                        // RX of esp8266 in connected with Arduino pin 3
String WIFI_SSID = "Tenda_7AD760";  // WIFI NAME
String WIFI_PASS = "optiplex1745";  // WIFI PASSWORD
String API = "CHM4LLFP12Z6DTSP";    // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
int countTrueCommand;
int countTimeCommand;
boolean found = false;
SoftwareSerial esp8266(RX, TX);

// Code for Thing Speak Ends



void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(WATER_SENSOR_PIN, INPUT);
  pinMode(SMOKE_SENSOR_PIN, INPUT);
  Serial.begin(9600);

  dht.begin();

  // For Thing Speak
  esp8266.begin(115200);
  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\"" + WIFI_SSID + "\",\"" + WIFI_PASS + "\"", 20, "OK");
}

void loop() {
  // put your main code here, to run repeatedly:
  int water_level = analogRead(WATER_SENSOR_PIN);
  int smoke_level = analogRead(SMOKE_SENSOR_PIN);

  // Check for flood
  if (water_level > THRESHOLD_WATER) {
    // Flood detected, sound the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Check for smoke
  if (smoke_level > THRESHOLD_SMOKE) {
    // Smoke detected, sound the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");

  Serial.print("Water level: ");
  Serial.println(water_level);
  Serial.print("Smoke level: ");
  Serial.println(smoke_level);

  int smoke_level_p = map(smoke_level, 0, 1023, 0, 99);
  int water_level_p = map(water_level, 0, 1023, 0, 99);

  // For Thing Speak
  String getData = "GET /update?api_key=" + API + "&field1=" + smoke_level_p + "&field2=" + t + "&field3=" + h + "&field4=" + water_level_p;
  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
  sendCommand("AT+CIPSEND=0," + String(getData.length() + 4), 4, ">");
  esp8266.println(getData);
  countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0", 5, "OK");

  delay(300);
}


// For Thing Speak

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
    countTimeCommand++;
  } 
  if(found == true)
  {
    Serial.println("OK");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  } 
  found = false;
 }
