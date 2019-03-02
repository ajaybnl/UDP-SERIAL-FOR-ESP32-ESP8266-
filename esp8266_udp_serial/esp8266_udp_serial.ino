/*Created by Ajay Kumar (ajaybnl@gmail.com) Youtube: Ajay Sudhera
   Download Free App Script Communicator for UDP Serial
   Check My Yourtube Video for How to View UDP Serial :
   https://www.youtube.com/watch?v=AWLJwVyLJ7k

   This example shows how to connect and send data to you PC (To Script Communicator)
*/

#include <ESP8266WiFi.h>
#include <WiFiudp.h>

const char* ssid = "FILL_HERE";
const char* password = "FILL_HERE";

WiFiUDP udp;


//(Set your Static IP ADDRESS in your PC for Ease)

// Your PC IP ADDRESS
IPAddress udpAddress(10, 0, 0, 30); // Either 192.168.1.2 or anthing (Check Wifi Status)

unsigned int udpPort = 8080;  // port to connect


unsigned int udplocalport = 3424; //not needed to change


//Change to enable/disable serial
#define DEBUG 1   //0 for disabling


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.printf("Connecting to %s ", ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("connected");

    udp.begin(udplocalport); //8080 port

    Serial.printf("Client IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), udplocalport);
  } else {
    Serial.println("Cannot Connect To WIfi");
  }
}




void loop()
{
  char text[50];
  
//Check Wifi Status
  if (WiFi.status() == WL_CONNECTED) {


    udp.begin(udplocalport);
    delay(10);

    //Connect To IP
    if (udp.beginPacket(udpAddress, udpPort) == 0) {
      udp.stop();
      Serial.println("UDP Connection Failed");
    } else {

      //Send
      snprintf(text, 50, " ESP8266 Data %d\n", analogRead(A0)); // For Multiple Variables just add like this : snprintf(udptext, 40, "%d,%d,%d\n",d,b,c);

udp.println(text);

      /* OR
        udp.write(text);
            udp.write("\n");

            //Or 
            udp.println(text);
            
      */


      udp.endPacket();

      Serial.println("UDP Connection Sucessful");
    }
    delay(1000);
  }

}
