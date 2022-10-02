#include <Arduino.h>
/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-async-web-server-espasyncwebserver-library/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/
// #define ESP32
// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define ss 5
#define rst 14
#define dio0 2

// const char* ssid = "WIDYA ROBOTIC";
// const char* password = "011118WidyaWII";
// const char* ssid = "WIDYA ROBOTICS";
// const char* password = "011118widya";
// const char *ssid = "Awang";
// const char *password = "011118widya";
// const char* ssid = "KAMEKATRON";
// const char* password = "terserahkamu";
const char* ssid = "WIDYA ROBOT";
const char* password = "011118widya";

// const char* mqtt_server = "192.168.111.86"; // mqtt broker ip
// const char* mqtt_server = "192.168.18.85"; //mekatron
// const char *mqtt_server = "192.168.18.52"; // widya robotics
const char* mqtt_server = "192.168.144.33";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long waktuPesan = 0;
char msg[50];
String hostname = "ESP32D";
// define the pins used by the transceiver module
String deviceRX = "SensDev", sens1 = "S1 = ", sens2 = "S2 = ";
String LoRaData, sen1, sen2;
int sensor1, sensor2;

void callback(char* topic, byte* message, unsigned int length) { //receive data
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("state : ");
    if(messageTemp == "on"){
      Serial.println("on");
      LoRa.beginPacket();
      LoRa.printf("sendPub");
      LoRa.endPacket();
      // digitalWrite(ledPin, HIGH);
    }
    // else if(messageTemp == "off"){
    //   Serial.println("off");
    //   // digitalWrite(ledPin, LOW);
    // }
  }
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("esp32Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

String waitingData()
{
  // return ("31,22");
  while (true)
  {

    int packetSize = LoRa.parsePacket();
    if (packetSize)
    {
      // received a packet
      Serial.print("Lora: ");

      // read packet
      while (LoRa.available())
      {
        char strSen[7];
        LoRaData = LoRa.readString();
        Serial.print(LoRaData);
        int indexS1 = LoRaData.indexOf(sens1);
        int indexS2 = LoRaData.indexOf(sens2);
        int indexComma = LoRaData.indexOf(",");

        sen1 = LoRaData.substring(indexS1 + sens1.length(), indexComma);
        sen2 = LoRaData.substring(indexS2 + sens2.length(), indexS2 + sens2.length() + 3);
        Serial.printf("sensor1 = %s , sensor2 = %s \n", sen1, sen2);

        const char *strSen1 = sen1.c_str();
        const char *strSen2 = sen2.c_str();
        Serial.println(client.publish("esp32/sensor1", strSen1));
        Serial.println(client.publish("esp32/sensor2", strSen2));

        Serial.print("sensor2 :");
        Serial.print(strSen1);
        Serial.print("| sensor2 : ");
        Serial.println(strSen2);
        sprintf(strSen,"%s,%s",strSen1,strSen2);
        
        if (strSen1 != 0 && strSen2 != 0)
        {
          return (strSen);
        } 
        if(!client.connected()){
          reconnect();
        }
      }

      // print RSSI of packet
      // Serial.print("' with RSSI ");
      // Serial.println(LoRa.packetRssi());
    }
  }
}

String sendData()
{
  Serial.println("sending data");
  LoRa.beginPacket();
  LoRa.printf("sendPub");
  LoRa.endPacket();

  return waitingData();
}
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA); 
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(hostname.c_str()); //define hostname  
  WiFi.begin(ssid, password);
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("ip :");
  Serial.println(WiFi.localIP());
  
  client.setServer(mqtt_server, 1883);   
  client.setCallback(callback);
 
}


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 600px;
    margin: 0 auto;
  }

  .card {
    background-color: #F8F7F9;;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    padding-top:10px;
    padding-bottom:20px;
  }
  
  .button {
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .state {
     font-size: 1.5rem;
     color:#8c8c8c;
     font-weight: bold;
   }
  </style>
<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="topnav">
    <h1>ESP WebSocket Server</h1>
  </div>
  <div class="content">
    <div class="card">
      <h2>Sensor 1</h2>
      <p class="value">value: <span id="sens1">%VALUE1%</span></p>      
      <h2>Sensor 2</h2>
      <p class="value">value: <span id="sens2">%VALUE2%</span></p>
      <p><button id="button" onClick="handleButton()" class="button">Request Data</button></p>
    </div>
    
  </div>

  <script>
    const handleButton = () => {
        const baseUrl = window.location
        
        console.log('Fetching data...')
        return fetch(`${baseUrl}get-data`)
            .then((response) => {
                console.log('Data fetching')
                return response.text()
            })
            .catch(err => {
              alert('error fetching sensor value! read console for err details')
              console.log(err)
            })
            .then((value) => {
                const value1Element = document.getElementById('sens1')
                const value2Element = document.getElementById('sens2')
                
                const [value1, value2] = value.split(',')
                value1Element.innerHTML = value1
                value2Element.innerHTML = value2

                console.log(`Response: `, value1, value2)
            })
    }
  </script>

</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
// String processor(const String& var){
//   //Serial.println(var);
//   if(var == "VALUE1"){
//     return readDHTTemperature();
//   }
//   else if(var == "VALUE2"){
//     return readDHTHumidity();
//   }
//   return String();
// }

String outputState(int output)
{
  if (digitalRead(output))
  {
    return "checked";
  }
  else
  {
    return "";
  }
}

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  setup_wifi();

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(915E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get-data", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              // const String value1 = sense->s1;
              // const String value2 = sense->s2;
              Serial.println("getting data...");
              // Serial.print(sendData());
    request->send(200, "text/plain", sendData()); }); // ganti  dengan value dari const String value1

  server.begin();
}

void loop()
{
   if(!client.connected()){
    reconnect();
  }
  client.loop();
}