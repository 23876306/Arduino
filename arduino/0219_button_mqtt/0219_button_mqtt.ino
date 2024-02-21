#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "iphone 16"; // 您的 WiFi 網絡名稱
const char *password = "0933559613"; // 您的 WiFi 密碼

String mqtt_ClientID = "tank_IOT_Station_";

const char* pub_topic = "tank/button";

const char *mqtt_server = "broker.emqx.io";
const char *mqtt_userName = "emqx";
const char *mqtt_password = "public";

WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];
int value = 0;
const byte butPin = 27;
const byte ledpin = 13;
int number = 0; 

void setup_wifi()
{
    delay(10);
    Serial.println();
    Serial.print("正在連接到 ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi 連接成功");
    Serial.println("IP 地址: ");
    Serial.println(WiFi.localIP());

}

void reconnect()
{
    while (!client.connected())
    {
        if (client.connect((mqtt_ClientID, mqtt_userName, mqtt_password)))
        {
            Serial.print("連接成功，客戶端 ID: ");
            Serial.println(mqtt_ClientID);
            client.publish(pub_topic, "嗨，我上線了！");
        }
        else
        {
            Serial.print("連接失敗，狀態碼=");
            Serial.print(client.state());
            Serial.println(" 5 秒後重試");
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    pinMode(butPin, INPUT_PULLUP);  
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();


    bool val = digitalRead(butPin); 

    // 如果按下按钮，数字加1
    if (val == LOW)
    {
        while (digitalRead(butPin) == LOW); // 等待按钮释放
        number++; 
        snprintf(msg, sizeof(msg), "%d", number); // 數字轉為字符串發布
        client.publish(pub_topic, msg);
        Serial.println("目前按鈕數值為:");
        Serial.println(number);
        delay(200); // 延遲200毫秒防止按键重复增加
    }
}
