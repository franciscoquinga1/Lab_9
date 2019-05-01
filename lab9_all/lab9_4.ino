// 'Include the libs '
#include <ESP8266WiFi.h>

//'Parameters WIFI'
const char* ssid = "<your network>";
const char* password = "<your password>";
const char* host = "www.example.com";
void setup()
{
  Serial.begin(115200);
  Serial.println () ;
  
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
  // 'Client that will connect to the Host'
  WiFiClient client;
  Serial.printf ("nn[Connecting to %s ... ", host);
  
  // 'Try to connect'
  if ( client.connect(host, 80))
  {
    Serial.println("connected]");
    Serial.println("[Sending a request]");
    client.print(String("GET /") + " HTTP/1.1nrnn" +
    "Host: " + host + "nrnn" +
    "Connection: closenrnn" +
    "nrnn"
    ) ;
    Serial . println("[Response:]");
    // 'While the connection lasts'
  while ( client .connected())
  {
  // If there are available data
  if ( client . available ())
  {
  String line = client.readStringUntil('nn');
  Serial.println( line ) ;
  }
  }
  // 'Once the server sends all the required data it is disconnected and the program continues'
  client.stop() ;
  Serial.println("\n[Disconnected]");
  }
  else
  {
  Serial.println("connection failed !] ");
  client.stop() ;
  }
  delay(5000);
}
