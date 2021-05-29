#include "M5Atom.h"

int GRB_COLOR_WHITE = 0xffffff;
int GRB_COLOR_BLACK = 0x000000;
int GRB_COLOR_RED = 0x00ff00;
int GRB_COLOR_ORANGE = 0xa5ff00;
int GRB_COLOR_YELLOW = 0xffff00;
int GRB_COLOR_GREEN = 0xff0000;
int GRB_COLOR_BLUE = 0x0000ff;
int GRB_COLOR_PURPLE = 0x008080;

int activeColor = GRB_COLOR_WHITE;

float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;

bool IMU6886Flag = false;

int currentBrightness = 20;

void setup()
{
    M5.begin(true, false, true);
    delay(20);

    IMU6886Flag = M5.IMU.Init() == 0;

    // Initialize display
    M5.dis.clear();
    M5.dis.setBrightness(currentBrightness);

    if (!IMU6886Flag)
    {
        Serial.println("Error initializing the IMU! 🙁");
    }
}

bool moves_left = false;
float UPPER_THRESHOLD = 250;
float LOWER_THERESHOLD = -250;

int ID = 0;

void loop()
{
    if (IMU6886Flag) // Continue if the IMU is working
    {
        M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);

        float trackedQuantity = gyroY;

        if (trackedQuantity >= UPPER_THRESHOLD)
        {
            moves_left = true;
            ID++;
            delay(100);
        }
        else if (trackedQuantity <= LOWER_THERESHOLD)
        {
            moves_left = false;
            ID--;
            delay(100);
        }

        Serial.println(ID);

        if (moves_left)
        {
            activeColor = GRB_COLOR_RED;
        }
        else
        {
            activeColor = GRB_COLOR_BLUE;
        }

        for (int i = 0; i < 25; i++)
        {
            M5.dis.drawpix(i, activeColor);
        }
    }

    delay(20);
    M5.update();
}