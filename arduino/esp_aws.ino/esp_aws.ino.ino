#include <Arduino_BuiltIn.h>   // 引入 Arduino 內建庫
#include "utils.h"             // 引入自定義的 utils.h 標頭檔
#include <PubSubClient.h>      // 引入 MQTT 客戶端庫

void setup() {
    Serial.begin(115200);     // 初始化串行通訊，設定傳輸速率為 115200 bits per second
    connectAWS();             // 呼叫自定義函式 connectAWS()，用於建立到 AWS 服務的連接
}

void loop() {
    int metricsValue = random(1, 100);  // 產生一個介於 1 到 99 之間的隨機整數，並將其指派給 metricsValue 變數
    Serial.print(F("metrics: "));        // 使用串行通訊輸出文字 "metrics: "
    Serial.println(metricsValue);        // 將 metricsValue 的值輸出到串行通訊

    publishMessage(metricsValue);        // 呼叫一個自定義函式 publishMessage()，將 metricsValue 的值發布到 MQTT 主題
    client.loop();                       // 處理 MQTT 客戶端的事件循環
    delay(3000);                         // 延遲 3000 毫秒，也就是 3秒
}
