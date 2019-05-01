#include <ESP8266WiFi.h>
#include <DHT.h>


const char*  ssid="casita";
const char* password= "casita4847";
const char* host= "192.168.43.242";

#define DHTTYPE DHT11 //DHT21, DHT22

#define DHTPIN 2 // GPIO2
DHT dht(DHTPIN, DHTTYPE, 27);


float temperature;

float humidity;
void setup()
{ 
    Serial.begin(115200);
    Serial.println () ;
    dht.begin();
    Serial.printf ("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
    delay(500);
    Serial.print(".");
    }
    Serial.println(" connected");
}

void loop()
{
    WiFiClient client;
    Serial.printf ("nn[Connecting to %s ... ", host);
    if ( client .connect(host, 80))
    {
      Serial.println("connected]");
      temperature = dht.readTemperature();
      humidity = dht.readHumidity();
      Serial.println("[Sending a request]");
      client.print(String("GET /esp8266/?Temp=") + temperature + "&Hum=" + humidity + "HTTP/1.1nrnn" +
      "Host: " + host + "nrnn" +
      "Connection: closenrnn" +
      "nrnn"
      ) ;
      Serial.println("[Response:]");
      while ( client.connected())
      {
        if ( client.available ())
        {
        String line = client.readStringUntil('nn');
        Serial.println( line ) ;
        }
     }
        client.stop() ;
        Serial.println("nn[Disconnected]");
    }
      else
      {
      Serial.println("connection failed !] ");
      client.stop() ;
      }
    delay(5000);
}
