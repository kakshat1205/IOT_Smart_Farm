#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

const char* ssid = "Redmi_Smart"; // Enter your WiFi name
const char* password =  "kakshat1205"; // Enter WiFi password
const char* mqttServer = "ja700e90.en.emqx.cloud";
const int mqttPort = 12342;
const char* mqttUser = "kakshat1205";
const char* mqttPassword = "kakshat1205";

const char *topic2 = "temp";
const char *topic = "humidity";
const char *topic3 = "motor";

WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  pinMode(D4, OUTPUT);
  Serial.begin(115200);
  Wire.begin(D1, D2);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected");
    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  client.publish(topic, "humidity emqx");
  client.subscribe(topic);
  client.publish(topic2, "temp emqx");
  client.subscribe(topic2);
  client.publish(topic3, "motor emqx");
  client.subscribe(topic3);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected");
    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {

  client.loop();
  Wire.beginTransmission(8); /* begin with device address 8 */
  Wire.write("Hello Arduino");  /* sends hello string */
  Wire.endTransmission();    /* stop transmitting */

  Wire.requestFrom(8, 1); /* request & read data of size 13 from slave */
  while (Wire.available()) {
    int c = Wire.read();
    char ptr[10];
    char str[10];
    //Serial.print(c);
    itoa(c, ptr, 10);
    //Serial.println(ptr);
    client.publish(topic, ptr);
    //Serial.println(s);
  }
  Serial.println();
  delay(1000);



}

/*
  void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived in topic: ");
  //Serial.println(topic);
  //  Serial.print("Message arrived in topic2: ");
  //Serial.println(topic2);
  //  Serial.print("Message arrived in topic3: ");
  //Serial.println(topic3);

  //Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print(client.subscribe(topic3));
  }
  }
*/

void callback(char* topic, byte* payload, unsigned int length) {
  String response;

  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(response);
  Serial.println("HI");
  //digitalWrite(D4, LOW);
  if (response == "on") // Turn the light on
  {
    digitalWrite(D4, HIGH);
    //client.publish(STATE_TOPIC, "on");
  }
  else if (response == "off") // Turn the light off
  {
    digitalWrite(D4, LOW);
    //client.publish(STATE_TOPIC, "off");

  }
}
