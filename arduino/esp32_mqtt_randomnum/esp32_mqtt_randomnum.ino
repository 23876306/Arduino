#include <WiFi.h>
#include <PubSubClient.h>

// CODING: 更新這些值以適應您的網絡。
const char *ssid = "iphone 16"; // 您的 WiFi 網絡名稱
const char *password = "0933559613"; // 您的 WiFi 密碼

// CODING: 在 EMQX 上定義您的客戶端ID
String mqtt_ClientID = "tank_IOT_Station_";

// CODING: 定義要發布的主題
const char *pub_topic = "tank/random";

// CODING: EMQX broker 參數
const char *mqtt_server = "broker.emqx.io"; // EMQX broker 地址
const char *mqtt_userName = "emqx"; // EMQX 使用者名稱
const char *mqtt_password = "public"; // EMQX 密碼

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
char msg[50]; // 動態分配緩衝區大小
int value = 0;

void setup_wifi()
{
    delay(10);
    // 首先連接到 WiFi 網絡
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
    // 循環直到重新連接成功
    while (!client.connected())
    {
        // 嘗試連接
        if (client.connect((mqtt_ClientID, mqtt_userName, mqtt_password)))
        {
            Serial.print("連接成功，客戶端 ID: ");
            Serial.println(mqtt_ClientID);
            // 連接成功後，發布一個公告...
            client.publish(pub_topic, "嗨，我上線了！");
        }
        else
        {
            Serial.print("連接失敗，狀態碼=");
            Serial.print(client.state());
            Serial.println(" 5 秒後重試");
            // 等待 5 秒後重試
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
}

void loop()
{

    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastMsg > 2000) //間隔2秒
    {
        lastMsg = now;
        ++value;
        snprintf(msg, sizeof(msg), "%d", random(100)); // 生成 0 到 100 的隨機值
        Serial.println(msg);
        client.publish(pub_topic, msg);
    }
}
