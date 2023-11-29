# Enhanced-Autonomous-Mushroom-Growing-System
Cultivating mushrooms has traditionally relied on constant human attention to maintain optimal environmental conditions for growth. The process demands a careful balance of humidity, temperature, CO2 level and soil moisture to ensure a healthy mushroom harvest. However, as mushroom cultivation scales up to meet growing demands, the need for increased human labor and time becomes a limiting factor. Recognizing this challenge, the development of an Internet of Things (IoT)-based system emerges as a solution to achieve efficient and large-scale mushroom production with minimal human supervision. This prototype integrates sensors and automation to monitor and control the crucial factors affecting mushroom growth. By leveraging IoT technology, the system can adjust environmental parameters in real-time, ensuring an ideal habitat for mushrooms. This not only reduces the reliance on manual intervention but also enhances the precision and consistency of the cultivation process, ultimately leading to a more reliable and sustainable mushroom production.

## Sensors used
1. [MQ-135](https://tronic.lk/product/mq-135-air-quality-benzene-alcohol-smoke-hazardous-gas-) - To detect CO2 Level of the air
2. [DHT 11](https://tronic.lk/product/dht11-temperature-and-relative-humidity-sensor-module-f) - To detect humidity and temperature
3. [Soil Hygrometer Humidity Detection Module](https://www.duino.lk/product/soil-hygrometer-humidity-detection-module/) - To detect moisture of the growth medium

## Actuators used
1. [Exhaust fan](https://www.duino.lk/product/50x50x10mm-dc-12v-brushless-7-blade-cooling-fan-5010/) - To control CO2 level 
2. [Ultrasonic Mist Maker Fogger Atomizer Humidifier](https://tronic.lk/product/ultrasonic-mist-maker-fogger-atomizer-humidifier-113khz) - To control Humidity
3. [Mini Micro Submersible Water Pump](https://www.duino.lk/product/mini-micro-submersible-pumps-amphibious-type/) - To control moisture of the growth medium

## Other hardware used
1. [ESP32 Wireless WiFi Bluetooth Development Board 30 Pin](https://www.duino.lk/product/esp32-wireless-wifi-bluetooth-2-4ghz-cp2102/) - As the development board
2. [5V 1Ch Relay Module Board with Optocoupler](https://www.duino.lk/product/5v-1ch-relay-module-board-with-optocoupler/) - To control the water pump
3. [5VDC 2 Way 2 Channel Relay Module](https://tronic.lk/product/5vdc-2-way-2-channel-relay-module-with-coupling-protect) - To control the fan and the humidifier
