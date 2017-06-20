#include <ESP8266WiFi.h>
#include <PubSubClient.h> 
#include<DHT.h>

const char* ssid = "Paradise";
const char* password = "mukesh9980813506";

#define ORG "5z4xqx"
#define DEVICE_TYPE "ESP8266"
#define DEVICE_ID "HDK"
#define TOKEN "9632333088"

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/DHT/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);

void setup() {
 Serial.begin(115200);
 Serial.println();

 Serial.print("Connecting to "); Serial.print(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 } 
 Serial.println("");

 Serial.print("WiFi connected, IP address: "); Serial.println(WiFi.localIP());
}

int counter = 0;

void loop() {

 if (!client.connected()) {
 Serial.print("Reconnecting client to ");
 Serial.println(server);
 while (!client.connect(clientId, authMethod, token)) {
 Serial.print(".");
 delay(500);
 }
 Serial.println();
 }

 String payload = "{\"d\":{\"Name\":\"18FE34D81E46\"";
 payload += ",\"counter\":";
 payload += counter++;
 payload += "}}";
 
 Serial.print("Sending payload: ");
 Serial.println(payload);
 
 if (client.publish(topic, (char*) payload.c_str())) {
 Serial.println("Publish ok");
 } else {
 Serial.println("Publish failed");
 }

 delay(5000);
}
