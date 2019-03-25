// ESP Library
#include <ESP8266WiFi.h>
// MQTT Library
#include <PubSubClient.h>

#define LED1 5
#define LED2 4
#define LED3 15

// Tune Connection

const char* wifiSSID = "testMosquitto";
const char* wifiPassword = "12345678";


// MQTT Define
 const char* mqttServerIP = "192.168.43.114";
//const char* mqttServerIP = "192.168.1.2";
const int mqttPort = 1883;

// Define topic MQTT
 char* topicLED1 = "jarkomLAN/zeroDevice-1/led1"; // pub & syv
 char* topicLED2 = "jarkomLAN/zeroDevice-1/led2"; // pub & sub
 char* topicLED3 = "jarkomLAN/zeroDevice-1/led3"; // pub & sub
 char* topicRunLED = "jarkomLAN/zeroDevice-1/runLED"; //pub & sub

WiFiClient myESP; // myESP become WIFI
PubSubClient client(myESP);

int timeDelay = 100;
bool statRunLED = false;
void wifiSetup(){
  WiFi.begin(wifiSSID,wifiPassword);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Waiting, connection to Wifi..");
    Serial.print("SSID : "); Serial.println(wifiSSID);
    
    // give notification LED
    notifLED(LED2,200);
  }
  Serial.println("Connected to the WiFI Network "); 
  Serial.print("Connected Network "); Serial.println(wifiSSID);
  Serial.print("IP Local "); Serial.println(WiFi.localIP());
}

char dataPublish[50];
void publishMQTT(char* topics, String data){
   
   data.toCharArray(dataPublish, data.length() + 1);
    
   client.publish(topics, dataPublish);
}

void reconnect(){
  // MQTT Begin
  while(!client.connected()){
    Serial.println("Connecting to MQTT Server..");
    Serial.print("IP MQTT Server : "); Serial.println(mqttServerIP);
    notifLED(LED3,300);
    bool hasConnection = client.connect("ZeroESP-1"); // connect(id,username,password) -> true if connect
    if(hasConnection){
      Serial.println("Success connected to MQTT Broker");
    } else {
      Serial.print("Failed connected");
      Serial.println(client.state());
      delay(2000);
      Serial.println("Try to connect...");
    }
  }
  client.publish(topicLED1, "Reconnecting"); // acc
  client.publish(topicLED2, "Reconnecting"); //  ypr
  client.publish(topicLED3, "Reconnecting"); //  ypr
  client.publish(topicRunLED, "Reconnecting");
  client.subscribe(topicLED1);  
  client.subscribe(topicLED2);  
  client.subscribe(topicLED3);  
  client.subscribe(topicRunLED);


}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.println("--------");
  Serial.println("Message Arrived");
  Serial.print("Topic :"); Serial.println(topic);
  Serial.print("Message : ");
  String pesan = "";
  for(int i=0; i < length; i++){
    Serial.print((char)payload[i]);

    pesan += (char)payload[i];

  }
  Serial.println();

// FOR TOPIC 1
 if (strcmp(topic,topicLED1) == 0) {
   if(pesan == "true" ){
      Serial.println("LED 1 ON");
      digitalWrite(LED1, HIGH);

   } else if(pesan == "false"){
      Serial.println("LED 1 OFF");
      digitalWrite(LED1,LOW);
   }
   Serial.print("Masuk : " );
   Serial.println(pesan);
 } else
 // FOR TOPIC 2
 if (strcmp(topic,topicLED2) == 0) {
   if(pesan == "true" ){
      Serial.println("LED 2 ON");
      digitalWrite(LED2, HIGH);

   } else if(pesan == "false"){
      Serial.println("LED 2 OFF");
      digitalWrite(LED2,LOW);
   }
   Serial.print("Masuk : " );
   Serial.println(pesan);
 }else
 // FOR TOPIC 3
 if (strcmp(topic,topicLED3) == 0) {
   if(pesan == "true" ){
      Serial.println("LED 3 ON");
      digitalWrite(LED3, HIGH);

   } else if(pesan == "false"){
      Serial.println("LED 3 OFF");
      digitalWrite(LED3,LOW);
   }
   Serial.print("Masuk : " );
   Serial.println(pesan);
 }else
 // topic run led
 if (strcmp(topic,topicRunLED) == 0) {
   if(pesan == "true" ){
      Serial.println("Running LED Start");
      statRunLED = true;
      
   } else if(pesan == "false"){
      Serial.println("Running LED Stop");
      statRunLED = false;
      //stopAllLED();
   }
   Serial.print("Masuk : " );
   Serial.println(pesan);
 }

  Serial.print("Pesan masuk :");
  Serial.println(pesan);
  Serial.println("--------");
}

void notifLED(int LED, int timeDelay){
  digitalWrite(LED,HIGH);
  delay(timeDelay);
  digitalWrite(LED,LOW);
}

void runningLED(int timeDelay){
  notifLED(LED1, timeDelay);
  notifLED(LED2, timeDelay);
  notifLED(LED3, timeDelay);
}

void stopAllLED(){
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
}

void checkLED() {
  Serial.println("checked");
}

void setup(){
	Serial.begin(57600);
  wifiSetup();

  Serial.print(F("WiFi connected! IP address: "));
 	//Initialize MQTT Connection
  client.setServer(mqttServerIP, mqttPort);
  client.setCallback(callback); // callback for incoming message

	// SETUP LED MODE
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);

  // Attach Interrupt
  attachInterrupt(digitalPinToInterrupt(LED1), checkLED, CHANGE);
}

void loop(){
	if (!client.connected()){
    	reconnect();
  	}
  	client.loop(); // looping forever the client

  	//notifLED(LED1);
  	//notifLED(LED2);
  	//notifLED(LED3);
  	//Serial.println("run");

    if (statRunLED){
      notifLED(LED1,100);
      notifLED(LED2,100);
      notifLED(LED3,100);
    }
  	delay(5);
}


