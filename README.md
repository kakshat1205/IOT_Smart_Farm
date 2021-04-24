# IOT_Smart_Farm
Agriculture is done in every country from ages. Agriculture is the science and art of cultivating plants. Agriculture was the key development in the rise of sedentary human civilization. Agriculture is done manually from ages. As the world is trending into new technologies and implementations it is a necessary goal to trend up with agriculture also. IOT plays a very important role in smart agriculture. IOT sensors are capable of providing information about agriculture fields. we have proposed an IOT and smart agriculture system using automation. This IOT based Agriculture monitoring system makes use of wireless sensor networks that collects data from different sensors deployed at various nodes and sends it through the wireless protocol. This smart agriculture using IOT system is powered by Arduino, it consists of Temperature sensor, Moisture sensor, water level sensor, DC motor and GPRS module. When the IOT based agriculture monitoring system starts it checks the water level, humidity and moisture level.  Sensors sense the level of water if it goes down, it automatically starts the water pump. If the temperature goes above the level, fan starts. This all is displayed on the LCD display module. This all is also seen in IOT where it shows information of Humidity, Moisture and water level with date and time, based on per minute. Temperature can be set on a particular level, it is based on the type crops cultivated. If we want to close the water forcefully on IOT there is button given from where water pump can be forcefully stopped.


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

### Lets setup ESP with arduino IDE
Refer This link : instructables.com/Setting-Up-the-Arduino-IDE-to-Program-ESP8266/

### About MQTT
With the advent of the 5G era, connecting everything is becoming a reality. Accessing a large number of devices and devices management brings a huge challenge to network broadband, communication protocol and platform service architecture.


MQTT protocol is an IoT messaging protocol based on the publish-subscribe model. It has occupied half of the IoT protocol because of its simple and easy to implement, supporting QoS and small packet.

## How to setup EMQX broker(Pretty descent for small projects)
https://cloud.emqx.io/console/deployments/ja700e90/overview - Link to my broker

### Client Info
Cllient can be any device. Laptop can be used with mqttx and phone can be used with apps on play store.

## Topics
- Humidity - Basically publish data of humidity from DTH11 Sensor
- Temp - Publishes Temperaure
- Moisture - Publishes soil moisture
- Water_level - Publishes water level in tank
