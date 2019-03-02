/*Created by Ajay Kumar (ajaybnl@gmail.com) Youtube: Ajay Sudhera
 * Download Free App Script Communicator for UDP Serial
 * Check My Yourtube Video for How to View UDP Serial : 
 * https://www.youtube.com/watch?v=AWLJwVyLJ7k
 * 
 * This example shows how to connect and send data to you PC (To Script Communicator)
 */

#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi network name and password:
const char * networkName = "FILL_HERE";
const char * networkPswd = "FILL_HERE";


//(Set A Static IP ADDRESS in your PC for Ease (in Future))

// Your PC IP ADDRESS
IPAddress udpAddress(10, 0, 0, 30); // Either 192.168.1.2 or anthing (Check Wifi Status)

const int udpPort = 8080; // port to connect


boolean connected = false;

//The udp library class
WiFiUDP udp;


void setup()
{
  pinMode(led, OUTPUT);
  
  
  Serial.begin(115200);

  connectToWiFi(networkName, networkPswd);

  
  //Wait till wifi connection
  while (!connected) {
    yield();
  }

  
digitalWrite(led,HIGH);
}


void loop()
{

  if (connected) {

    udp.begin(WiFi.localIP(), 3332);
    delay(10); //Tweak this

    long d = 0;
    
// Change 50 to 255 for Large String
char text[50];


//Connect To IP
    if (udp.beginPacket(udpAddress, udpPort) == 0) {
      udp.stop();
      Serial.println("UDP Connection Failed");
      
    } else {

		//Data
      snprintf(text, 50, "ESP32 Data %d\n", analogRead(0));


/* OR
 Udp.write(text);
      Udp.write("\n");
    */
    
    
	  //Send
      udp.printf(text);
      udp.endPacket();      
      udp.stop();



      Serial.println("UDP Connection Sucessful");
      
    }
delay(1000);
  }
}






void connectToWiFi(const char * ssid, const char * pwd) {
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);

  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}



//wifi event handler
void WiFiEvent(WiFiEvent_t event) {
  Serial.print("...");
  switch (event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      //When connected set
      Serial.print("WiFi connected! IP address: ");
      Serial.println(WiFi.localIP());
      //initializes the UDP state
      //This initializes the transfer buffer

      connected = true;
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      connected = false;
      break;
  }
}
