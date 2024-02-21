#include <WiFi.h>

const char* ssid = "iphone 16";
const char* password = "0933559613";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  } 

  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // 读取IP地址
  Serial.print("WiFi RSSI: ");
  Serial.println(WiFi.RSSI()); // 读取WiFi强度
  Serial.print("WiFi 網路名稱: ");
  Serial.println(ssid);
}

void loop() {
  int randomNumber = random(0, 101);
  
  Serial.print("Random Number: ");
  Serial.println(randomNumber);

  delay(10000); // 等待一秒钟
}
