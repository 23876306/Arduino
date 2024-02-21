const byte butPin = 27;
//const byte ledPin = 13;
int number = 0; // 用于存储数字的变量

void setup() {
  //pinMode(ledPin, OUTPUT);
  pinMode(butPin, INPUT_PULLUP);
  Serial.begin(9600); // 初始化串口通信
}

void loop() {
  bool val = digitalRead(butPin);

  // 如果按下按鈕，進行加1操作
  if (val == LOW) {
    // 只在按下時執行一次增加
    while (digitalRead(butPin) == LOW);
    number++; // 將數字加1
    Serial.println(number); // 在串口監視器中顯示數字
    delay(200); // 延遲200毫秒以防止按鈕彈跳
  }
}
