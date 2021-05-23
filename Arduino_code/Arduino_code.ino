#include <Wire.h>
#include <dht.h>


int sensor_pin = A0; // Moisture sensor
//int sensor_pin1 = A3; //Water level sensor
//int sensor_pin3 = A1; //LDR sensor

// DHT Sensor
#define dht_apin A2 // DTH sensor
dht DHT;
int output_value ;
int output_humidity;
int output_temp;

// Water level
#define sensorPower 7
#define sensorPin A3
int val_waterlevel = 0;

//LDR
const int ledPin = 13;
const int ldrPin = A1;

byte output;

byte out_M ;
byte out_H ;
byte out_T ;
byte out_L ;
byte out_W ;



void setup() {
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);           /* start serial for debug */
  Serial.println("Reading From the Sensor ...");

  //Water Level
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);

  //LDR
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);

  delay(2000);
}

void loop() {
  // Mosture Sensor data
  output_value = analogRead(sensor_pin);
  output_value = map(output_value, 550, 0, 0, 100);

  // DHT Senosor PIN A2 humidity and Temp
  DHT.read11(dht_apin);
  output_humidity = DHT.humidity;
  output_temp = DHT.temperature;

  //LDR
  int ldrStatus = analogRead(ldrPin);

  //Water level sensor
  int level = readSensor();

  //Serial.print(output);
  //Serial.print(output_value);
  //Serial.println("%");


  // DATA to be transfered       Moisture       humidity       temp       ldr_status      water_level

  output = output_value;


  out_M = (output_value);
  out_H = (output_humidity);
  out_T = (output_temp);
  out_L = (ldrStatus);
  out_W = (level);

  delay(1000);

  //delay(100);
}

int readSensor() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val_waterlevel = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return val_waterlevel;
}


// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (0 < Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    //Serial.print(c);           /* print the character */
  }
  Serial.println();
  Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
  //int i = 0;
  Wire.write(out_M);
  Wire.write(out_H);
  Wire.write(out_T);
  Wire.write(out_L);
  Wire.write(out_W);

}
