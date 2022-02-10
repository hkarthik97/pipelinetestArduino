#include"mqtt_log.h"

WiFiClient espClient;
PubSubClient client(espClient);

void mqtt_log::Mqtt_Begin() {
  client.setServer("mqtt.zig-web.com", 1883);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", "Android", "Polgara12ZED2122")) {

      Serial.println("connected");
      delay(2000);
      StaticJsonBuffer<300> JSONbuffer;
      JsonObject& JSONencoder = JSONbuffer.createObject();

      JSONencoder["DeviceId"] = WiFi.macAddress();
      JSONencoder["Log"] = "Connected to MQTT / WEB";

      char JSONmessageBuffer[100];
      JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      Serial.println("Sending message to MQTT topic..");
      Serial.println(JSONmessageBuffer);
      if (client.publish("/zed/snifferlog", JSONmessageBuffer) == true) {
        Serial.println("Success sending message");
      } else {
        Serial.println("Error sending message");
      }

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }
}

void mqtt_log::Mqtt_log(String logData) {
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();

  JSONencoder["DeviceId"] = WiFi.macAddress();
  JSONencoder["Log"] = logData;

  char JSONmessageBuffer[100];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONmessageBuffer);

  if (client.publish("/zed/snifferlog", JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
  } else {
    Serial.println("Error sending message");
  }
  Serial.println("-------------");
  delay(10000);
}
