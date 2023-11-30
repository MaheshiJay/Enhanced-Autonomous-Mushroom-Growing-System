#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Insert your network credentials
#define ssid "Look ma_No Wires"
#define password "AmfWifiHot"

// Define pinout for soil moisture
const int moistureSensorPin  = 35; 
const int pumpPin = 32;  //water pump
char soilMAr[6];

// Define pinout for co2
const int co2SensorPin  = 36;
const int fanPin = 16;  //fan
char co2Ar[6];

// Define pinout for air moisture
const int dhtSensorPin  = 13;
const int humidifierPin = 22;  //humidifier relay
char HumidAr[6];

char TempAr[6];

DHT dht(dhtSensorPin,DHT11);

//MQTT topics
#define soilMoistureSens "mushroom/sensor/soilMoisture"
#define soilMoistureAcc "mushroom/actuator/waterpump"

#define co2Sens "mushroom/sensor/co2level"
#define co2Acc "mushroom/actuator/fan"

#define humiditySens "mushroom/sensor/humidity"
#define humidityAcc "mushroom/actuator/humidifier"                

#define tempSens "mushroom/sensor/temp"

WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
   Serial.begin(9600);
   setupWifi();
   setupMqtt();

   dht.begin();

   //soil moisture sensor & pump pins
   pinMode(moistureSensorPin, INPUT);
   pinMode(pumpPin, OUTPUT);
   digitalWrite(pumpPin, LOW);

    //co2 sensor & fan pins
   pinMode(co2SensorPin, INPUT);
   pinMode(fanPin, OUTPUT);
   digitalWrite(fanPin, LOW);
   
   //air moisture sensor & humidifier pins
   pinMode(dhtSensorPin, INPUT);
   pinMode(humidifierPin, OUTPUT);
   digitalWrite(humidifierPin, LOW);

  
}

void loop() {
   if (!client.connected()) {
      connectToBroker();
   }
   client.loop();


   //soil moisture sensor readings
   updateSoilMoisture();
   Serial.print("Soil Moisture : ");
   Serial.println(soilMAr);
   client.publish(soilMoistureSens , soilMAr);

   updateCo2Level();
   Serial.print("Co2 Level : ");
   Serial.println(co2Ar);
   client.publish(co2Sens , co2Ar);

   updateHumidityLevel();
   Serial.print("Humid Level : ");
   Serial.println(HumidAr);
   client.publish(humiditySens , HumidAr);

   updateTempLevel();
   Serial.print("Temp Level : ");
   Serial.println(TempAr);
   client.publish(tempSens , TempAr);



    
   delay(1000); // Delay for a second (adjust as needed)
}



//set up wifi connection
void setupWifi(){
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }
   Serial.println("WiFi connected");
}

//setup MQTT
void setupMqtt() {
  client.setServer("test.mosquitto.org", 1883);
  //water pump call back
  client.setCallback(waterPumpCallback);
  //Fan Callback
  //client.setCallback(FanCallback);

 
}

//connect MQTT broker
void connectToBroker(){
  while(!client.connected()){
    Serial.print("Attempting MQTT connection...");
    if(client.connect("ESP32-465466445")){
      Serial.println("connected");
      
      //water pump on off
      client.subscribe(soilMoistureAcc);
      client.subscribe(co2Acc);
      client.subscribe(humidityAcc);

      
      
    }else{
       Serial.println("failed");
        Serial.print(client.state());
        delay(5000);
    }
  }
}

//soil moisture sensor readings update
void updateSoilMoisture(){

    //const int DryValue = 4095;
    // const int WetValue = 2435;
    //int soilMoisturePercent;
    // Get soil mositure value
    int moistureLevel = ( 100 - ( (analogRead(moistureSensorPin) / 4095.00) * 100 ) )*2; 
    // Determine soil moisture percentage value
    //soilMoisturePercent = map(moistureLevel, DryValue, WetValue, 0, 100);
    // Keep values between 0 and 100
    //soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);
    // Pass soil moisture to cloud variable
    int current_Moisture = moistureLevel;
    String(current_Moisture).toCharArray(soilMAr, 6) ;
}
//read moisture
int readSoilMoisture(){
    return analogRead(moistureSensorPin);
}
//water pump controlling
void waterPumpCallback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("]");

    char payloadCharAr[length];
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
        payloadCharAr[i] = (char)payload[i];
    }
    Serial.println();

    if (strcmp(topic, soilMoistureAcc) == 0) {
        // Handle soil moisture topic
        Serial.println("soil");
        if (payloadCharAr[0] == '1') {
            digitalWrite(pumpPin, HIGH);
        } else {
            digitalWrite(pumpPin, LOW);
        }
    } else if (strcmp(topic, co2Acc) == 0) {
        Serial.println("co2");
        if (payloadCharAr[0] == '1') {
            digitalWrite(fanPin, HIGH);
        } else {
            digitalWrite(fanPin, LOW);
        }
    } else if (strcmp(topic, humidityAcc) == 0) {
        Serial.println("humid");
        if (payloadCharAr[0] == '1') {
            digitalWrite(humidifierPin, HIGH);
        } else {
            digitalWrite(humidifierPin, LOW);
        }
    } else {
        Serial.println("Unsubscribed Topic");
    }
}


//soil moisture sensor readings update
void updateCo2Level(){
  int airQuality = analogRead(co2SensorPin);
  int mappedAirQuality = map(airQuality, 800, 1600, 0, 100);
   String(mappedAirQuality).toCharArray(co2Ar, 6) ;
}

//Fan controlling
void FanCallback(char* topic,byte* payload, unsigned int length ){
        Serial.print("Message arrived [ ");
        Serial.print(topic);
        Serial.print(" ]");

        char payloadCharAr[length];
        for(int i=0; i<length; i++){
            Serial.print((char)payload[i]);
            payloadCharAr[i] = (char)payload[i];
        }
        Serial.println();

        if(strcmp(topic, co2Acc) == 0){
          if(payloadCharAr[0]=='1'){
            digitalWrite(fanPin, HIGH);
          }else{
             digitalWrite(fanPin, LOW);
          }
        }
}

void updateHumidityLevel(){
  int humidity=dht.readHumidity();
  String(humidity).toCharArray(HumidAr, 6);
}

void updateTempLevel(){
  int temperature=dht.readTemperature();
  String(temperature).toCharArray(TempAr, 6);
}

