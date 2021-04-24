# IOT_Smart_Farm - Overview
This smart agriculture using IOT system is powered by Arduino, it consists of Temperature sensor, Moisture sensor, water level sensor, DC motor and GPRS module. When the IOT based agriculture monitoring system starts it checks the water level, humidity and moisture level.  Sensors sense the level of water if it goes down, it automatically starts the water pump. If the temperature goes above the level, fan starts. This all is displayed on the LCD display module. This all is also seen in IOT where it shows information of Humidity, Moisture and water level with date and time, based on per minute. Temperature can be set on a particular level, it is based on the type crops cultivated. If we want to close the water forcefully on IOT there is button given from where water pump can be forcefully stopped.


## Components required:
- Arduino Uno - Atmega328p
- ESP 8266
- 4 Channel 5V Optical Isolated Relay Module 
- Humidity/Temp Sensor - DHT11
- Moisture Sensor
- Water Motor
- GPRS module
- Water level sensor
- Fans/Leds


![image](https://user-images.githubusercontent.com/49076977/115974276-2f697b80-a579-11eb-8d6a-b91f37f17cca.png)

### Lets setup ESP with arduino IDE
Refer This link : instructables.com/Setting-Up-the-Arduino-IDE-to-Program-ESP8266/

![image](https://user-images.githubusercontent.com/49076977/115974328-6d669f80-a579-11eb-982e-fa5de02410ff.png)

## Pin Diagram

### About MQTT
With the advent of the 5G era, connecting everything is becoming a reality. Accessing a large number of devices and devices management brings a huge challenge to network broadband, communication protocol and platform service architecture.


MQTT protocol is an IoT messaging protocol based on the publish-subscribe model. It has occupied half of the IoT protocol because of its simple and easy to implement, supporting QoS and small packet.

## How to setup EMQX broker(Pretty descent for small projects)
https://cloud.emqx.io/console/deployments/ja700e90/overview - Link to my broker

![image](https://user-images.githubusercontent.com/49076977/115974323-62137400-a579-11eb-9fe7-37e046882f54.png)

![image](https://user-images.githubusercontent.com/49076977/115974383-fe3d7b00-a579-11eb-8837-8aad70fcd60c.png)



### Client Info
Cllient can be any device. Laptop can be used with mqttx and phone can be used with apps on play store.

## Topics
- Humidity - Basically publish data of humidity from DTH11 Sensor
- Temp - Publishes Temperaure
- Moisture - Publishes soil moisture
- Water_level - Publishes water level in tank

## Android Application Buliding

## Bill Of Materials

| Component Name | Quantity | Approx Price |
| --- | --- | --- |
| Arduino Uno | | |
| ESP 8266 | | |
| Relay Module | | |
| Humidity/Temp Sensor - DHT11 | | |
| Moisture Sensor | | |
| Water Motor | | |
| GPRS module | | |
| Water level sensor | | |
| Fans/Leds | | |

## Further mods
Same solution is being implemented using cc3200 IOT launchpad from TI. Its a state of the art Processor with lower power requirements.

![image](https://user-images.githubusercontent.com/49076977/115974346-91c27c00-a579-11eb-98de-ddf043d654ad.png)


