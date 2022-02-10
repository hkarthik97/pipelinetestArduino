#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


class mqtt_log {
  private:

  public:
    void Mqtt_Begin();
    void Mqtt_log(String logData);
};
