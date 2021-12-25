#include <Arduino.h>
#include <Wifi.h>
#include <WebSocketsClient.h>

#define USE_SERIAL Serial

const char* ssid = "Home";
const char* password = "genesiswifi";

/** WEBSOCKETS CONNECTION PARAMETERS **/
const char* path = "/control";
const char* host = "192.168.0.2";
const int port = 80;

// WEBSOCKETS CLIENT
WebSocketsClient webSocket;

void webSocket_event(WStype_t type, uint8_t * payload, size_t length) {

	switch(type) {
		case WStype_DISCONNECTED:
			USE_SERIAL.printf("[WSc] Disconnected!\n");
			break;
		case WStype_CONNECTED:
			USE_SERIAL.printf("[WSc] Connected to url: %s\n", payload);

			// send message to server when Connected
			webSocket.sendTXT("Connected from ESP32");
			break;
		case WStype_TEXT:
			USE_SERIAL.printf("[WSc] get text: %s\n", payload);

			// webSocket.sendTXT("message here");
			break;
		case WStype_BIN:
			USE_SERIAL.printf("[WSc] get binary length: %u\n", length);
			// hexdump(payload, length);

			// send data to server
			// webSocket.sendBIN(payload, length);
			break;
		case WStype_ERROR:			
		case WStype_FRAGMENT_TEXT_START:
		case WStype_FRAGMENT_BIN_START:
		case WStype_FRAGMENT:
		case WStype_FRAGMENT_FIN:
			break;
    default:
        break;
	}

}

void setup() {
  
  USE_SERIAL.begin(115200);
  delay(10);

  // we start by connecting to a WiFi network
  USE_SERIAL.print("Connecting to ");
  USE_SERIAL.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  USE_SERIAL.println("");
  USE_SERIAL.println("WiFi connected");
  USE_SERIAL.println("IP address: ");
  USE_SERIAL.println(WiFi.localIP());

 // connection begin
  webSocket.begin(host, port, path);

  // event handler
  webSocket.onEvent(webSocket_event);

  // try ever 2000 again if connection has failed
  webSocket.setReconnectInterval(2000);
}

void loop() {
  webSocket.loop();
}



// DFRobot HR8833 - MOTOR DRIVER
// GPIO23 - IA1
// GPIO22 - IA2
// GPIO21 - IB1
// GPIO19 - IB2
//////////////////


// HC-SR04 
// GPIO25 - ECHO
// GPIO26 - TRIG
//////////////////


// SERVO MG 90S MICRO
// GPIO33 - PWN
///////////////////


// DHT11 - IDUINO SE052
// GPI015 - DOUT(S)
////////////////////


// TRANSISTOR BC639
// GPIO32 - BASE
///////////////////