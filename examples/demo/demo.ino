#include "mqtt_log.h"
mqtt_log MQ;
void setup()
{
  Serial.begin(115200);
  WiFi.begin("Z U S A N 4G", "12345678");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  MQ.Mqtt_Begin();
}
void loop()
{
  MQ.Mqtt_log("Working");
  delay(5000);
}
