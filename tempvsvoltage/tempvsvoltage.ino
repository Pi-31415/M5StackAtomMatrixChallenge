#include "M5Atom.h"

int GRB_COLOR_WHITE = 0xffffff;
int GRB_COLOR_BLACK = 0x000000;
int GRB_COLOR_RED = 0x00ff00;
int GRB_COLOR_ORANGE = 0xa5ff00;
int GRB_COLOR_YELLOW = 0xffff00;
int GRB_COLOR_GREEN = 0xff0000;
int GRB_COLOR_BLUE = 0x0000ff;
int GRB_COLOR_PURPLE = 0x008080;

float lowTempF = 103;
float highTempF = 105;

float tempC = 0;
bool IMU6886Flag = false;

void setup()
{
    M5.begin(true, false, true);
    delay(20);

    IMU6886Flag = M5.IMU.Init() == 0;

    if (!IMU6886Flag)
    {
        Serial.println("Error initializing the IMU! :-(");
    }
}

void loop()
{
    if (IMU6886Flag)
    {
        M5.IMU.getTempData(&tempC);
        Serial.printf(" Temp : %.2f C \r\n", tempC);
        float tempF = tempC * 9 / 5 + 32;
        Serial.printf(" Temp : %.2f F \r\n", tempF);

        if (tempF < lowTempF)
        {
            fillDisplay(GRB_COLOR_BLUE);
        }
        else if (tempF > highTempF)
        {
            fillDisplay(GRB_COLOR_RED);
        }
        else
        {
            fillDisplay(GRB_COLOR_GREEN);
        }

        delay(500);
        M5.update();
    }
}

void fillDisplay(int fillColor)
{
    for (int i = 0; i < 25; i++)
    {
        M5.dis.drawpix(i, fillColor);
    }
}