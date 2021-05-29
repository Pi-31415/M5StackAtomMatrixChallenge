#include <M5StickC.h>

float temp;

void setup() {
  M5.begin();
  M5.IMU.Init();
}
void loop() {
  M5.IMU.getTempData(&temp);
  M5.Lcd.setCursor(0, 45);
  M5.Lcd.printf("Temperature : %.2f C", temp);
  delay(500);
}