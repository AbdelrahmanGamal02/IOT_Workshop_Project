/*  IoT Workshop
 * Author: Abdelrahman Gamal
 * LinkedIn: https://www.linkedin.com/in/abdelrahman-gamal-a5b3a1244
 * Date: Apr, 2025
 * Board: ESP8266 NodeMCU 1
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define IR_LED   5
#define LED_PIN  4


#define SECONDS_BETWEEN_PUBLISHING 200

char ssid[] = "Abdelrahman Gamal";
char pass[] = "abdo2002gamal";

const char broker[] = "broker.emqx.io";
int port = 1883;

WiFiClient Espclient; // Wifi instance
PubSubClient client(Espclient);// PubSubClient instance

long long duration = 0;
// Callback Function for subscribtion
void Subscribe_CallBack(char *topic , byte *payload , unsigned int length);
int IR_State = 0;
int LED_State = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // establish WiFi connection
  WiFi.begin(ssid , pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("connecting.....");
    Serial.println(WiFi.status());

  }

  Serial.println("WiFi Connected !!");
  Serial.println(WiFi.status());
  Serial.println(WiFi.localIP());

  // Set MQTT broker connection
  client.setServer(broker , port);
  client.setCallback(Subscribe_CallBack);
  // establish connection
  while(!client.connect("Abdo_2002_3221"))
  {
    Serial.print("Connecting to broker : ");Serial.println(broker);
  }

  Serial.println("Connected");
  // client.connected() check if it is connected or not
  // for all topics /sector/#
  // for specific topic /sector/abdo
  if(!client.subscribe("/sector/abdo/led"))
  {
    Serial.println("Subscription Failed");
  }
  Serial.println("Subscription Done");
  pinMode(IR_LED, INPUT);
  pinMode(LED_PIN , OUTPUT);

  duration = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();

  IR_State = digitalRead(IR_LED);
  // publish data
  if((millis() - duration) >= SECONDS_BETWEEN_PUBLISHING)
  {
    client.publish("/sector/abdo/ir",(IR_State? "NO_OBJECT_DETECTED" : "OBJECT_DETECTED"));
    Serial.println("data published to topic /sector/abdo/ir");
    duration = millis();
  }

  if(1 == LED_State)
  {
    digitalWrite(LED_PIN , HIGH);
  }
  else
  {
    digitalWrite(LED_PIN , LOW);
  }
}
// function implementation
void Subscribe_CallBack(char *topic , byte *payload , unsigned int length)
{
  char arr_char[length];
  Serial.print("Recieved MSG on Topic: ");
  Serial.println(topic);
  Serial.println("Recieved MSG on Topic");
  for(int i = 0; i < length; i++)
  {
    arr_char[i] = (char)payload[i];
  }
  arr_char[length] = '\0';

  if(strcmp(arr_char , "LED_ON") == 0)
  {
    LED_State = 1;
  }
  else if(strcmp(arr_char , "LED_OFF") == 0)
  {
    LED_State = 0;
  }
  else{}
  Serial.print(arr_char);
  Serial.println();
}
