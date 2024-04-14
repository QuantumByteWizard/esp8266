#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Define your WiFi credentials
const char* ssid = "Relax Residence_Plus";
const char* password = "Relax2021@8751";

// Initialize the web server on port 80
ESP8266WebServer server(80);

// Function to handle root URL
void handleRoot() {
  // Get Wi-Fi signal strength
  int32_t rssi = WiFi.RSSI();

  // Convert RSSI to percentage (0% to 100%)
  int strengthPercent = map(rssi, -100, -50, 0, 100);
  strengthPercent = constrain(strengthPercent, 0, 100);

  // Create HTML page with signal strength graph and auto-refresh
  String html = "<!DOCTYPE html><html><head><title>ESP8266 Signal Strength</title>";
  html += "<script>setTimeout(function() { window.location.reload(true); }, 1000);</script>"; // Auto-refresh every 1 seconds
  html += "</head><body>";
  html += "<h1>ESP8266 Signal Strength</h1>";
  html += "<h4>This webserver shows wifi strength its connected to Relax Residence_plus network for testing different spots of our WiFi.</h4>";
  html += "<p>Signal Strength: " + String(strengthPercent) + "%</p>";
  html += "<div style='background-color: lightgray; width: 200px; height: 20px; border: 1px solid black;'>";
  html += "<div style='background-color: green; width: " + String(strengthPercent) + "%; height: 100%;'></div>";
  html += "</div>";
  html += "</body></html>";

  // Send HTML page to client
  server.send(200, "text/html", html);
}

void setup() {
  // Initialize the onboard LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED

  // Set static IP address, gateway, and subnet mask
  IPAddress ip(192, 168, 31, 225); // Set your desired static IP address
  IPAddress gateway(192, 168, 31, 1); // Set your gateway IP address
  IPAddress subnet(255, 255, 255, 0); // Set your subnet mask

  // Set the WiFi configuration
  WiFi.config(ip, gateway, subnet);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to WiFi");

  // Define server route
  server.on("/", handleRoot);

  // Start the server
  server.begin();

  // Turn off the LED
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // Handle client requests
  server.handleClient();
}
