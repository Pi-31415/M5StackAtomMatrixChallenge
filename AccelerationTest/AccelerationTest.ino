#include "M5Atom.h"

void setup()
{
    M5.begin(true, false, true);
    delay(50);
    M5.dis.drawpix(0, 0xf00000);
}

void loop()
{
    // put your main code here, to run repeatedly:

    // get the acceleration data
    // accX = right pointing vector
    //      tilt to the right: > 0
    //      tilt to the left:  < 0
    // accy = backward pointing vector
    //      tilt forward:  < 0
    //      tilt backward: > 0
    // accZ = upward pointing vector
    //      flat orientation: -1g

    float accX = 0, accY = 0, accZ = 0;
    M5.IMU.getAccelData(&accX, &accY, &accZ);

    //This is for debugging purpose, listens to serial at 115200 baud
    Serial.println(accY);
}