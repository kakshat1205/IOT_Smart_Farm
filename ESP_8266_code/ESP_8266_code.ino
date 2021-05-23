#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

const char* ssid = "Redmi_Smart"; // Enter your WiFi name
const char* password =  "kakshat1205"; // Enter WiFi password
const char* mqttServer = "ja700e90.en.emqx.cloud";
const int mqttPort = 12342;
const char* mqttUser = "kakshat1205";
const char* mqttPassword = "kakshat1205";

const char *moisture = "moisture";
const char *humidity = "humidity";
const char *temp= "temp";
const char *motor = "motor";
const char *level = "level";
const char *LDR = "LDR";
const char *LED_RED = "LED_RED";
const char *LED_BLUE = "LED_BLUE";
const char *LED_GREEN = "LED_GREEN";


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long previousMillis = 0;
int ledState = LOW;
const long interval = 1000;
/*
  ICACHE_RAM_ATTR void detectsMovement() {
  Serial.println("MOTION DETECTED!!!");
  digitalWrite(led, HIGH);
  startTimer = true;
  lastTrigger = millis();
  }
*/
void setup() {
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D0 , OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

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
      delay(1000);
    }
  }
  digitalWrite(D4, HIGH);
  digitalWrite(D0, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D7, HIGH);
  client.subscribe(moisture);
  client.publish(moisture, "moisture");
  client.subscribe(humidity);
  client.publish(humidity, "humidity");
  client.subscribe(temp);
  client.publish(temp, "temp");
  client.subscribe(LDR);
  client.publish(LDR, "LDR");
  client.subscribe(level);
  client.publish(level, "level");
  client.subscribe(LED_RED);
  client.publish(LED_RED, "on");
  client.subscribe(LED_BLUE);
  client.publish(LED_BLUE, "on");
  client.subscribe(motor);
  client.publish(motor, "on");
  client.subscribe(LED_GREEN);
  client.publish(LED_GREEN, "on");

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
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      Wire.beginTransmission(8); /* begin with device address 8 */
      //Wire.write("Hello Arduino");  /* sends hello string */
      //Wire.endTransmission();    /* stop transmitting */

      Wire.requestFrom(8, 5); /* request & read data of size 13 from slave */
      while (Wire.available()) {
        int M = Wire.read();
        Serial.println(M);
        char ptr[10];
        itoa(M, ptr, 10);
        client.publish(moisture, ptr);
        
        int H = Wire.read();
        Serial.println(H);
        char ptr2[10];
        itoa(H, ptr2, 10);
        client.publish(humidity, ptr2);
        
        int T = Wire.read();
        Serial.println(T);
        char ptr3[10];
        itoa(T, ptr3, 10);
        client.publish(temp, ptr3);
        
        int L = Wire.read();
        Serial.println(L);
        char ptr4[10];
        itoa(L, ptr4, 10);
        client.publish(LDR, ptr4);
        
        int W = Wire.read();
        Serial.println(W);
        char ptr5[10];
        itoa(W, ptr5, 10);
        client.publish(level, ptr5);
        
        //Serial.println(T);
        

        /*
        //Serial.println("hi");
        int c = 0;
        /*if(c <= 25)
          digitalWrite(D4, LOW);
          else
          digitalWrite(D4, HIGH);
        
        int c2 = 34;
        char ptr2[10];
        char str[10];
        char ptr[10];
        char str2[10];
        //Serial.print(c);

        itoa(c, ptr, 10);
        itoa(c2, ptr2, 10);
        //Serial.println(ptr);
        client.publish(topic, ptr);
        client.publish(topic2, ptr2);
        //Serial.println(s);*/
        ledState = HIGH;
      }
    }
    else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    //digitalWrite(ledPin, ledState);
  }


}
//Serial.println();
//delay(1000);




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

void callback(char* topic, byte * payload, unsigned int length) {
  String response;

  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(response);
  //Serial.println("HI");
  //digitalWrite(D4, LOW);
  /*  switch (topic) {
      case "motor":
        D4 = D4;
        break;

      case "LED_RED":
        D4 = D8;
        break;

      case "LED_GREEN":
        D4 = D7;
        break;

      case "LED_BLUE":
        D4 = D6;
        break;

    }
  */
  if (strcmp(topic, "motor") == 0)
  {
    if (response == "on") // Turn the light on
    {
      digitalWrite(D4, HIGH);
      //client.publish(STATE_TOPIC, "on");
    }
    else if (response == "off") // Turn the light off
    {
      digitalWrite(D4, LOW);
    }
  }
  else if (strcmp(topic, "LED_RED") == 0)
  {
    if (response == "on") // Turn the light on
    {
      Serial.println("RED");
      digitalWrite(D3, HIGH);
      //client.publish(STATE_TOPIC, "on");
    }
    else if (response == "off") // Turn the light off
    {
      digitalWrite(D3, LOW);
    }
  }
  else if (strcmp(topic, "LED_BLUE") == 0)
  {
    if (response == "on") // Turn the light on
    {

      Serial.println("BLUE");
      digitalWrite(D7, HIGH);
      //client.publish(STATE_TOPIC, "on");
    }
    else if (response == "off") // Turn the light off
    {
      digitalWrite(D7, LOW);
    }
  }
  else if (strcmp(topic, "LED_GREEN") == 0)
  {
    if (response == "on") // Turn the light on
    {
      Serial.println("GREEN");
      digitalWrite(D0, HIGH);
      //client.publish(STATE_TOPIC, "on");
    }
    else if (response == "off") // Turn the light off
    {
      digitalWrite(D0, LOW);
    }
  }
}
