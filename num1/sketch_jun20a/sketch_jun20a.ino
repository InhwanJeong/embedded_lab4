#include <WiFi.h>
#include <WiFiClient.h>
const char* ssid = "lab919";
const char* password = "software@2019";
WiFiClient client;
const char* host = "192.168.0.75";
unsigned int port = 8080;
char wbuf[20];
void setup() {
Serial.begin(115200);
delay(10);
// We start by connecting to a WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
if (!client.connect(host, port)) {
Serial.println("connection failed");
return;
}
}
void loop() {
if (Serial.available() > 0) {
Serial.readBytes(wbuf, 20);
Serial.print(wbuf);
client.print(wbuf);
Serial.println("send ok");
}
delay(1000);
}
