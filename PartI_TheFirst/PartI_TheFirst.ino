/*
   M5StackAtomMatrixChallenge.ino

   By: Umer Bin Liaqat, Omar Elkammah, Sherifa Yakubu, Pi Ko
   Date: 29 May 2021

   Assignment 2 of ENGR-UH 1021J: Design & Innovation Summer 2021
   This is for Part I - the First
*/

#include <Arduino.h>
#include <math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "M5Atom.h"

#define PIN 27

//Variables for M5 Matrix Library

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
                                               NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                                                   NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                                               NEO_GRB + NEO_KHZ800);

const uint16_t colors[] = {
    matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)};

//Define Colors
//GRB not RGB
int GRB_COLOR_WHITE = 0xffffff;
int GRB_COLOR_RED = 0x00ff00;

// Define variables for instantaneous acceleration
// and sample size for calculating average
float accX_avg = 0, accY_avg = 0, accZ_avg = 0;
int n_average = 5;
bool IMU_ready = false;

//Define Patterns
int full_screen[25] =
    {
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1};

//Array of patterns for display
int *display[1] = {full_screen};

// STEP is for keeping track of the stages
int STEP = 0;
bool BLINK_MODE_ON = false;
float BRAKE_ACCELERATION_THRESHOLD = 10;

void setup()
{
    // Activate device with serial and Display, begin(SerialEnable, I2CEnable, DisplayEnable)
    M5.begin(true, false, true);
    delay(50);
    // check if IMU is ready
    if (M5.IMU.Init() == 0)
    {
        IMU_ready = true;
        Serial.println("[OK] IMU ready");
    }
    else
    {
        IMU_ready = false;
        Serial.println("[ERR] IMU failed!");
    }
    //Set up matrix for scrolling text
    matrix.begin();
    matrix.setTextWrap(false);
    matrix.setBrightness(40);
    matrix.setTextColor(colors[0]);
}

//Variables for scrolling the text from matrix library
int x = matrix.width();
int pass = 0;

void loop()
{

    if (M5.Btn.wasPressed())
    {
        //Increases the STEP everytime the button is pressed, and changes modes
        STEP++;
        //Serial.println("isPressed");
    }

    if (STEP == 0)
    {
        //Nothing on screen, blank (Step 1)
        BLINK_MODE_ON = false;
        M5.dis.clear();
    }
    else if (STEP == 1)
    {
        // Scroll Text to show stage
        matrix.fillScreen(0);
        matrix.setCursor(x, 0);
        matrix.print(F("Manual Rear strobe (RED) "));
        if (--x < -96)
        {
            x = matrix.width();
            if (++pass >= 3)
                pass = 0;
            matrix.setTextColor(colors[pass]);
        }
        matrix.show();
        delay(80);
    }
    else if (STEP == 2)
    {
        //Flash Red (Step 2)
        BLINK_MODE_ON = true;
        M5.dis.clear();
        turn_on_lights(display[0], GRB_COLOR_RED);
    }
    else if (STEP == 3)
    {
        // Scroll Text to show stage
        matrix.fillScreen(0);
        matrix.setCursor(x, 0);
        matrix.print(F("Manual Front strobe (WHITE) "));
        if (--x < -96)
        {
            x = matrix.width();
            if (++pass >= 3)
                pass = 0;
            matrix.setTextColor(colors[pass]);
        }
        matrix.show();
        delay(80);
    }
    else if (STEP == 4)
    {
        //Flash White (Step 3)
        BLINK_MODE_ON = true;
        M5.dis.clear();
        turn_on_lights(display[0], GRB_COLOR_WHITE);
    }
    else if (STEP == 5)
    {
        // Scroll Text to show stage
        matrix.fillScreen(0);
        matrix.setCursor(x, 0);
        matrix.print(F("Automatic Rear Mode Rear (RED) "));
        if (--x < -96)
        {
            x = matrix.width();
            if (++pass >= 3)
                pass = 0;
            matrix.setTextColor(colors[pass]);
        }
        matrix.show();
        delay(80);
    }
    else if (STEP == 6)
    {
        //Automatic Rear Mode Rear (RED) (Step 4)
        float accX = 0, accY = 0, accZ = 0;
        M5.IMU.getAccelData(&accX, &accY, &accZ);
        // Average the acceleration data
        // find the "running average"
        accX_avg = ((accX_avg * (n_average - 1)) + fabs(accX)) / n_average;
        accY_avg = ((accY_avg * (n_average - 1)) + fabs(accY)) / n_average;
        accZ_avg = ((accZ_avg * (n_average - 1)) + fabs(accZ)) / n_average;

        Serial.println(accZ_avg * 10.0);

        //Check if the Device is accelerating (i.e. braking), and adjust blink mode
        if (((accX_avg * 10.0) >= BRAKE_ACCELERATION_THRESHOLD) || ((accY_avg * 10.0) >= BRAKE_ACCELERATION_THRESHOLD) || ((accZ_avg * 10.0) >= BRAKE_ACCELERATION_THRESHOLD))
        {
            BLINK_MODE_ON = false;
        }
        else
        {
            BLINK_MODE_ON = true;
        }
        M5.dis.clear();
        turn_on_lights(display[0], GRB_COLOR_RED);
    }
    else if (STEP == 7)
    {
        // Scroll Text to show stage
        matrix.fillScreen(0);
        matrix.setCursor(x, 0);
        matrix.print(F("Automatic Rear Mode Rear (WHITE) "));
        if (--x < -96)
        {
            x = matrix.width();
            if (++pass >= 3)
                pass = 0;
            matrix.setTextColor(colors[pass]);
        }
        matrix.show();
        delay(80);
    }
    else if (STEP == 8)
    {
        //Automatic Rear Mode Rear (WHITE) (Step 5)
        float accX = 0, accY = 0, accZ = 0;
        M5.IMU.getAccelData(&accX, &accY, &accZ);
        // Average the acceleration data
        // find the "running average"
        accX_avg = ((accX_avg * (n_average - 1)) + fabs(accX)) / n_average;
        accY_avg = ((accY_avg * (n_average - 1)) + fabs(accY)) / n_average;
        accZ_avg = ((accZ_avg * (n_average - 1)) + fabs(accZ)) / n_average;

        Serial.println(accZ_avg * 10.0);

        //Check if the Device is accelerating (i.e. braking), and adjust blink mode
        if (((accX_avg * 10.0) >= BRAKE_ACCELERATION_THRESHOLD) || ((accY_avg * 10.0) >= BRAKE_ACCELERATION_THRESHOLD) || ((accZ_avg * 10.0) >= BRAKE_ACCELERATION_THRESHOLD))
        {
            BLINK_MODE_ON = false;
        }
        else
        {
            BLINK_MODE_ON = true;
        }

        M5.dis.clear();
        turn_on_lights(display[0], GRB_COLOR_WHITE);
    }
    else if (STEP >= 9)
    {
        //Reset the STEP
        STEP = 0;
    }

    //This is for debugging purpose, listens to serial at 115200 baud
    //Serial.println(STEP);

    if (BLINK_MODE_ON)
    {
        delay(50);
        M5.dis.clear();
        delay(50);
    }
    else
    {
        delay(100);
    }

    M5.update();
}

void turn_on_lights(int arr[], int color)
{
    for (int i = 0; i < 25; i++)
    {
        M5.dis.drawpix(i, color);
    }
}
