#include <M5Stack.h>
int RawValue = 0;
double volatge = 0;
double tempC = 0;
double Sum;
double minTemp = 200;
double maxTemp = 0;

void setup()
{
    serial.begin(9600);
    M5.begin();
    M5.Power.begin();
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(40, 10);
    M5.Lcd.printf("M5stack Thermometer");
    M5.Lcd.fillCircle(65, 180, 30, RED);
    M5.Lcd.fillRect(55, 60, 20, 150, RED);
    M5.Lcd.fillCircle(65, 60, 10, RED);
}