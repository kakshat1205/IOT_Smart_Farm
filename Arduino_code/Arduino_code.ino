#include <Wire.h>


int sensor_pin = A0;

int output_value ;

byte output;


void setup() {
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);           /* start serial for debug */
  Serial.println("Reading From the Sensor ...");

  delay(2000);
}

void loop() {
  output_value = analogRead(sensor_pin);

  output_value = map(output_value, 550, 0, 0, 100);

  output = output_value;

  

  //Serial.print(output);

  //Serial.print(output_value);

  //Serial.println("%");

  delay(1000);

  //delay(100);
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
  Wire.write(output);  /*send string on request */
}
