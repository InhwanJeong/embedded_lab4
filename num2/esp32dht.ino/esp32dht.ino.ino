#include <WiFi.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <DHT.h>
#define DHTTYPE DHT22
#define DHTPIN 4
const char* ssid = "lab919";
const char* password = "software@2019";
// Create an instance of the server
WiFiServer server(25525);
// Create an instance of DHT sensor
DHT dht(DHTPIN, DHTTYPE);
float temp, humi;
String webString = "";
unsigned long previousMillis = 0;
const long interval = 2000;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  // Start the server
  server.begin();
  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    String currentLine = ""; // for holding incoming data
    webString = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') { // if the byte is a newline character
          // if the current line is blank, you got two newlinecharacters in a row.
          // that's the end of the client HTTP request, so senda response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code(e.g. HTTP / 1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/json");
            client.println();

            // the content of the HTTP response follows theheader:
            client.print(webString);
            // The HTTP response ends with another blankline:
            client.println();
            // break out of the while loop:
            break;
          } else { // if you got a newline, then clearcurrentLine:
            currentLine = "";
          }
        } else if (c != '\r') { // if you got anything else buta carriage return character,
               currentLine += c; // add it to the end of thecurrentLine
        }
        // Check to see if the client request was "GET/events":
        if (currentLine.endsWith("GET /events")) {
        gettemphumi();
        webString=" {\"temperature\": \"" +
                     String(temp) + "\", \"humidity\": \"" + String(humi)
                     + "\" }";
                    }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
void gettemphumi() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    humi = dht.readHumidity();
    temp = dht.readTemperature(false);
    if (isnan(humi) || isnan(temp)) {
      Serial.println("Failed to read dht sensor.");
      return;
    }
  }
}
