/*Created by Ajay Kumar (ajaybnl@gmail.com) Youtube: Ajay Sudhera
   
   Check My Yourtube Video for How to View UDP Graph :
  https://www.youtube.com/watch?v=ssz-ebdW3ss

   This example shows how to connect and send data to you PC (To TelemetryViewer)
*/

#include <ESP8266WiFi.h>
#include <WiFiudp.h>


const char* ssid = "FILL_HERE";
const char* password = "FILL_HERE";

//UDP

//SET YOUR PC IP ADDRESS (YOU GOT FROM MODEM)
IPAddress udpip(192, 168, 100, 2);

//SET PORTS TO CONNECT
int printport = 8080;

int chartport = 8081;

int udplocalport = 3424; //no use


WiFiUDP Udp;


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

       Serial.printf("Client IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), udplocalport);
  } else {
    Serial.println("Cannot Connect To WIfi");
  }
}




void loop()
{
  //UDP
/*
How to send debug and measurements to UDP based server on Windows/Mac/Linux PC

Solution:

udpprint("something"); 
--------------------
This will print a line on ScriptCommunicator or Udp text programs.
You can use udpprint with Int, Float, Double, Long, Unsigned Long

udpchart(value1); 
--------------------
Or
udpchart(value1,value2); 
--------------------
This will appear on a chart on TelemetryViewer or Text in a UDP Text Program.

You can use udpprint with Int, Float, Double, Long, Unsigned Long

You can use udpprint and udpchart both simultainously (open TelemetryViewer with UDP port 8081 & Open ScriptCommunicator with Port 8080 UDP)

For more Info view my videos: https://www.youtube.com/channel/UCd39IeKZOUHnexE4m2iBnhg

*/

bool udpprint("Success!");

delay(1000);

}

//UDP
String ipToString(IPAddress ip) {
  String s = "";
  for (int i = 0; i < 4; i++)
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  return s;
}


//UDP Chart
bool udpchart(int a, int b) {
  String str = String(a) + "," + String(b);
  return (udpchart(str));
}

bool udpchart(float a, float b) {
  String str = String(a) + "," + String(b);
  return (udpchart(str));
}

bool udpchart(long a, long b) {
  String str = String(a) + "," + String(b);
  return (udpchart(str));
}


bool udpchart(float a) {
  String str = String(a);
  return (udpchart(str));
}

bool udpchart(int a) {
  String str = String(a);
  return (udpchart(str));
}

bool udpchart(double a) {
  String str = String(a);
  return (udpchart(str));
}

bool udpchart(unsigned long a) {
  String str = String(a);
  return (udpchart(str));
}

//UDP Print
bool udpprint(float a) {
  String str = String(a); 
  return (udpprint(str));
}
bool udpprint(int a) {
  String str = String(a);
  return (udpprint(str));
}

bool udpprint(double a) {
  String str = String(a);
  return (udpprint(str));
}

bool udpprint(long a) {
  String str = String(a);
  return (udpprint(str));
}

bool udpprint(unsigned long a) {
  String str = String(a);
  return (udpprint(str));
}


bool udpprint(String text1) {
   bool result=false;
  String str = text1;
//Construct Char* from String    
  str += "\n";
  int n = str.length(); 
  char text[n + 1];     
  strcpy(text, str.c_str()); 
  result = udp_write(text,printport);
  return (result);
}

bool udpchart(String text1) {
  bool result=false;
  String str = text1;
//Construct Char* from String    
  str += "\n";
  int n = str.length(); 
  char text[n + 1];     
  strcpy(text, str.c_str()); 
  result = udp_write(text, chartport);
  return (result);
}

bool udp_write(char* text, int port) {
  //UDP Write

  if (WiFi.status() == WL_CONNECTED) {
    Udp.stop();
    Udp.begin(udplocalport);
    delay(10); //Tweak this
    if (Udp.beginPacket(udpip, port)) {
      Udp.write(text);
      Udp.endPacket();
      return (true);
    } else {
      Udp.stop();
      return (false);
    }
  } else {
    return (false);
  }
}
