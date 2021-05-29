/*
   M5StackAtomMatrixChallenge.ino

   By: Umer Bin Liaqat, Omar Elkammah, Sherifa Yakubu, Pi Ko
   Date: 29 May 2021

   Assignment 2 of ENGR-UH 1021J: Design & Innovation Summer 2021
   This is for Part I - the First
*/

#include <Arduino.h>

#include "M5Atom.h"

float accX_avg = 0, accY_avg = 0, accZ_avg = 0;
int n_average = 15;
bool IMU_ready = false;

void setup()
{
    // start the ATOM device with serial and Display
    // begin(SerialEnable, I2CEnable, DisplayEnable)
    M5.begin(true, false, true);
    delay(50);
    // check if IMU is ready
    if (M5.IMU.Init() == 0)
    {
        IMU_ready = true;
        Serial.println("[OK] INIT ready");
        
    }
    else
    {
        IMU_ready = false;
        Serial.println("[ERR] IMU INIT failed!");
        
    }
    
}

void loop()
{

    float accX = 0, accY = 0, accZ = 0;
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    // Average the acceleration data
    // simple "running average" method without storing the data in an array
    accX_avg = ((accX_avg * (n_average - 1)) + accX) / n_average;
    accY_avg = ((accY_avg * (n_average - 1)) + accY) / n_average;
    accZ_avg = ((accZ_avg * (n_average - 1)) + accZ) / n_average;

    //Serial.println(accX_avg);

    // Serial.println(accY_avg*10.0);

    //Z is the forward motion
    Serial.println(accZ_avg * 10.0);

    delay(5);
    M5.update();
}
