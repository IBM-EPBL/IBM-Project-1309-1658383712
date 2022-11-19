#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

void callback(char* subscribetopic, byte* payload, unsigned int payloadLength);

#define ORG "92rnyd"
#define DEVICE_TYPE "TempSensor"
#define DEVICE_ID "12345"
#define TOKEN "123456789"
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

const int trigPin = 5;
const int echoPin = 18;
long duration;
float distanceCm;
float distanceInch;
String data;

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char publishTopic[] = "iot-2/evt/event_1/fmt/json";
char subscribeTopic[] = "iot-2/cmd/home/fmt/String";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;

char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  wificonnect();
  mqttconnect();
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;
  distanceInch = distanceCm * CM_TO_INCH;

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  delay(1000);
  PublishData(distanceCm);
  delay(1000);
  if (!client.loop())
  {
    mqttconnect();
  }
}

void PublishData(float distanceCm)
{
  mqttconnect ();
  String payload;

  if (distanceCm < 100.0)
  {
    payload = "{\"Alert\":";
    payload += distanceCm;
    payload += "}";
  }
  else
  {
    payload = "{\"distanceCm\":";
    payload += distanceCm;
    payload += "}";
  }

  Serial.print("Sending payload: ");
  Serial.print(payload);

  if (client.publish(publishTopic, (char*) payload.c_str()))
  {
    Serial.println("Publish ok");
  }
  else
  {
    Serial.println("Publish failed");
  }
}

void mqttconnect()
{
  if (!client.connected())
  {
    Serial.print("Reconnecting client to");
    Serial.println(server);
    while (!!!client.connect(clientId, authMethod, token))
    {
      Serial.print(",");
      delay(500);
    }
    initManagedDevice();
    Serial.println();
  }
}

void wificonnect()
{
  Serial.println();
  Serial.print("Connecting to");
  WiFi.begin("Wokwi-GUEST", "", 6);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP ADDRESS");
  Serial.println(WiFi.localIP());
}

void initManagedDevice()
{
  if (client.subscribe(subscribeTopic))
  {
    Serial.println((subscribeTopic));
    Serial.println("subscribe to cmd OK");
  }
  else
  {
    Serial.println("subscribe to cmd Failed");
  }
}

void callback(char* subscribetopic, byte* payload, unsigned int payloadLength)
{
  Serial.print("callback invoked for topic:");
  Serial.println(subscribetopic);
}