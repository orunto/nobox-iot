/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
// const char* ssid     = "MTN_4G_2B4331";
// const char* password = "B87BB6FF";

const char* ssid     = "Enny's Galaxy A04";
const char* password = "jvcc8692";

String temperature = "unavailable";

String humidity = "unavailable";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;

// Sensor constants
const int AirValue = 790;   //you need to replace this value with Value_1
const int WaterValue = 390;  //you need to replace this value with Value_2
const int SensorPin = A0;
int soilMoistureValue = 0;
int soilmoisturepercent=0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  soilMoistureValue = analogRead(SensorPin);  //put Sensor insert into soil
  Serial.println(soilMoistureValue);
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  Serial.println(soilmoisturepercent);

  WiFiClient client = server.available();   // Listen for incoming clients

  int moisture = soilmoisturepercent;
  delay(5000);

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);   
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>iostream Board Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            // client.println("<p>Soil moisture content"+moisture+"</p>");
            client.println(moisture);
            // client.println("<p>Humidity: " + humidity + "</p>");
            // client.println("<p>GPIO 5 - State " + temperature + "</p>");
            // client.println("<p><a href=\"/5/on\"><button class=\"button\">REFRESH</button></a></p>");

            client.println("</body></html>");
            client.println("<script>");
            client.println("const soilMoistureStructure = {\"name\": \"Moisture Sensor\",\"description\": \"\",\"slug\": \"moisturesensor\",\"projectSlug\":\"iostream\",\"webhooks\": null,\"recordFieldStructures\": [{\"required\": false,\"unique\": false,\"description\": \"\",\"comment\": \"\",\"hashed\": false,\"name\": \"value\",\"slug\": \"value\",\"type\": \"NUMBER\"},{\"required\": true,\"unique\": false,\"description\": \"\",\"comment\": \"\",\"hashed\": false,\"name\": \"unit\",\"slug\": \"unit\",\"type\": \"TEXT\",\"defaultValue\":\"percent\"}]}");
            // Place your auth token here
            client.println("const token = \"here\"");
            client.println("const addMoistureUrl = \"https://api.nobox.cloud/iostream/soilmoisture/_single_\";");
            client.println("const requestHeader = new Headers();");
            client.println("requestHeader.append(\"structure\", JSON.stringify(soilMoistureStructure));");
            client.println("requestHeader.append(\"auto-create-project\", \"true\");");
            client.println("requestHeader.append(\"auto-create-record-space\", \"true\");");
            client.println("requestHeader.append(\"clear-all-spaces\", \"false\");");
            client.println("requestHeader.append(\"mutate\", \"true\");");
            client.println("requestHeader.append(\"Content-Type\", \"application/json\");");
            client.println("requestHeader.append(\"Authorization\", \"Bearer \" + token);");

            client.println("let previousValue = null;");
            client.println("setInterval(()=>{");
            
            client.print("let value = ");
            client.println(moisture);

            client.println("if (value == previousValue) return;");

            client.println("previousValue = value;");

            client.println("const data = { value }");

            client.println("const requestOptions = {method: 'POST',headers: requestHeader,body: JSON.stringify(data),};");
            client.println("fetch(addMoistureUrl, requestOptions)");
            client.println(".then(response => response.text())");
            client.println(".then(result => console.log(\"Updated cloud!\"))");
            client.println(".catch(error => console.log('error', error));");
            client.println("}, 5000);");

            client.println("</script>");

            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}