
/*Created by Ajay Kumar (ajaybnl@gmail.com) Youtube: Ajay Sudhera
   Download Free App Script Communicator for UDP Serial
   Check My Yourtube Video for How to View UDP Serial :
   https://www.youtube.com/watch?v=AWLJwVyLJ7k

   This example shows how to connect and send data to you PC via UDP
*/

#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi network name and password:

const char* ssid = "FILL_HERE";
const char* password = "FILL_HERE";



//(Set A Static IP ADDRESS in your PC for Ease (in Future))

// Your PC IP ADDRESS
IPAddress udpAddress(10, 0, 0, 30); // Either 192.168.1.2 or anthing (Check Wifi Status)

const int udpPort = 8080; // port to connect



//The udp library class
WiFiUDP udp;


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

  
}
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED) {

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


      //Data to Send
      int var1 = analogRead(0);
      int var2 = sin(var1)*100;


      //       Data,size
      snprintf(text, 50, "%d,%d\n", var1, var2);
      //You can add as many variables by putting a comma and \n at end of line



      //Send
      udp.printf(text);
      udp.endPacket();
      udp.stop();



      Serial.println("UDP Connection Sucessful");

    }
    delay(1000);
  }
}
