
#include "M5Atom.h"

int GRB_COLOR_WHITE = 0xffffff;
int GRB_COLOR_BLACK = 0x000000;
int GRB_COLOR_RED = 0x00ff00;
int GRB_COLOR_ORANGE = 0xa5ff00;
int GRB_COLOR_YELLOW = 0xffff00;
int GRB_COLOR_GREEN = 0xff0000;
int GRB_COLOR_BLUE = 0x0000ff;
int GRB_COLOR_PURPLE = 0x008080;

int activeColor = GRB_COLOR_PURPLE;

const int TOLERANCE = 2;
const int SCALING_DIVISOR = 20;
const int MAX_BRIGHTNESS = 60;

float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;

bool IMU6886Flag = false;

int currentBrightness = 0;

void setup() 
{
    M5.begin(true, false, true);
    delay(20);
    
    IMU6886Flag = M5.IMU.Init() == 0;
  
    // Initialize display
    M5.dis.clear();
    M5.dis.setBrightness(currentBrightness);
    
    for(int i = 0; i < 25; i++)
    {
        M5.dis.drawpix(i, activeColor);
    }

    if(!IMU6886Flag)
    {
        Serial.println("Error initializing the IMU! :-(");
    }
}

void loop() 
{
    if(IMU6886Flag)
    {
        M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
    
        float trackedQuantity = gyroZ;
    
        if(abs(trackedQuantity) > TOLERANCE)
        {
            currentBrightness += trackedQuantity / SCALING_DIVISOR;
             
            if(currentBrightness > MAX_BRIGHTNESS)
                currentBrightness = MAX_BRIGHTNESS;
      
            if(currentBrightness < 0)
                currentBrightness = 0;

            M5.dis.setBrightness(currentBrightness);
        }
    }
      
    if(M5.Btn.wasReleased())
    {
        Serial.println("wasReleased");
        currentBrightness = 0;
        M5.dis.setBrightness(currentBrightness);
    }
    
    delay(20);
    M5.update();
}