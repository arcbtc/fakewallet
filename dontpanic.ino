#include <WiFiClientSecure.h>
#include <WiFi.h>

char wifiSSID[] = "your wifi";
char wifiPASS[] = "your password";

const char* host = "api.telegram.org";
const int httpsPort = 443;


void setup() {
  Serial.begin(115200);

  WiFi.begin(wifiSSID, wifiPASS);
  while (WiFi.status() != WL_CONNECTED){
    Serial.println("connecting");
    delay(500);
  }
  Serial.println("connected");

}

void loop() {
  delay(10000);
  WiFiClientSecure client;

  if(!client.connect(host, httpsPort)){
    return;
  }

  String url = "/bot[BOT_API_KEY]/sendMessage?chat_id=[MY_CHANNEL_NAME]&text=[MY_MESSAGE_TEXT]";
  

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
               
   while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
   }
   
   String line = client.readStringUntil('\n');
   Serial.println(line);

}
