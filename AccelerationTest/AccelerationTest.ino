/**************************************************************************
 * M5Stack ATOM Matrix Tilt Game
 * 
 * A simple game for the matrix version of the M5Stack ATOM. 
 * Red and green LEDs are shown on the display. 
 * If more red LEDs are shown, the device must be tilted to the right. 
 * If more green LEDs are shown, to the left.
 * There are twelve difficulty levels in which the number of red and green 
 * LEDs differs less and less and the display time becomes shorter and shorter. 
 * If a level is completed with more than 75% correct answers (>18 of 25), 
 * the next level is unlocked.
 * 
 * Hague Nusseck @ electricidea
 * v1.2 | 02.April.2020
 * https://github.com/electricidea/xxx
 * 
 * 
 * 
 * Distributed as-is; no warranty is given.
**************************************************************************/

#include <Arduino.h>

#include "M5Atom.h"
// install the library:
// pio lib install "M5Atom"

// You also need the FastLED library
// https://platformio.org/lib/show/126/FastLED
// FastLED is a library for programming addressable rgb led strips
// (APA102/Dotstar, WS2812/Neopixel, LPD8806, and a dozen others)
// acting both as a driver and as a library for color management and fast math.
// install the library:
// pio lib install "FastLED"

float accX_avg = 0, accY_avg = 0, accZ_avg = 0;
int n_average = 15;
bool IMU_ready = false;

// Display Buffer for the 5x5 RGB LED Matrix
// the first two elements are the size (5 rows and 5 coulums)
// then for every pixel three bytes for red, green and blue
uint8_t Display_Buffer[2 + 5 * 5 * 3];

// predefined display buffers to display some characters and numbers
#include "characters.c"

// Define own colors
// NOTE: The brightness of RGB LED is limited to 20 (global brightness scaling).
// DO NOT set it higher to avoid damaging the LED and acrylic screen.
#define cBLACK 0
#define cRED 1
#define cGREEN 2
#define cBLUE 3
#define cWHITE 4
#define cCYAN 5
#define cYELLOW 6
#define cMAGENTA 7
const uint8_t RGB_colors[8][3] = {{0x00, 0x00, 0x00},
                                  {0xF0, 0x00, 0x00},
                                  {0x00, 0xF0, 0x00},
                                  {0x00, 0x00, 0xF0},
                                  {0x70, 0x70, 0x70},
                                  {0x00, 0x70, 0x70},
                                  {0x70, 0x70, 0x00},
                                  {0x70, 0x00, 0x70}};
uint8_t display_color = cBLACK;
uint8_t goal_color = cBLACK;
uint8_t false_color = cBLACK;

// timer to switch the display to black
unsigned long display_off_millis;

// timer for the reaction time
unsigned long response_until_time;

// timer for wait a while
unsigned long wait_millis;

// game state machine states
#define s_START 1
#define s_WAIT_FLAT 2
#define s_SHOW_COLOR 3
#define s_WAIT_TILT 4
#define s_SHOW_RESULT 5
#define s_WAIT 6
#define s_SHOW_FINAL 7
#define s_GAME_FINISH 8
int game_state = s_START;

#define CENTER 0
#define LEFT 1
#define RIGHT 2
// if the device was tilted to the left or to the right
int tilt_move = CENTER;
// score reached within each level
int score = 0;
// game difficulty level
int game_level = 1;

// the difficulty of each level is coded in an array:
// 1 = correct color
// 2 = false color
// 3 = black pixel
// 4 = white pixel
const int board_levels[13][25] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, // 0 (L1a)
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 1 (L1b)
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}, // L2
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, // L3
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, // L4
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, // L5
    {3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}, // L6
    {3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3}, // L7
    {3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3}, // L8
    {3, 3, 3, 3, 3, 4, 4, 4, 1, 1, 1, 1, 1, 2, 2, 2, 2, 4, 4, 4, 3, 3, 3, 3, 3}, // L9
    {3, 3, 3, 3, 3, 4, 4, 4, 4, 1, 1, 1, 1, 2, 2, 2, 4, 4, 4, 4, 3, 3, 3, 3, 3}, // L10
    {4, 4, 4, 4, 4, 3, 3, 3, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4}, // L11
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4}, // L12
};
// the board for the actual move is filed with the data corresponding to the level
int board[25];
int board_index;
// For each level, the time, how long the board is visible (in ms)
int level_display_time[13] = {-1, 350, 300, 250, 200, 200, 150, 100, 50, 40, 30, 20, 10};
// For each level there is a separate reaction time requirement (in ms)
int level_reaction_time[13] = {-1, 1500, 1250, 1000, 900, 800, 700, 600, 500, 400, 350, 350, 350};

// A buffer to hold the result of each game
// withing one level (each level contains 25 turns)
uint8_t Result_Buffer[25];
int move_count = 0;

//==============================================================
// fill the display buffer with a solid color and diplay the buffer
// "color" is the index to the RGB_colors array
void fillScreen(uint8_t color)
{
    Display_Buffer[0] = 0x05;
    Display_Buffer[1] = 0x05;
    for (int i = 0; i < 25; i++)
    {
        Display_Buffer[2 + i * 3 + 0] = RGB_colors[color][0];
        Display_Buffer[2 + i * 3 + 1] = RGB_colors[color][1];
        Display_Buffer[2 + i * 3 + 2] = RGB_colors[color][2];
    }
    M5.dis.displaybuff(Display_Buffer);
}

//==============================================================
// function to display a number on the LED Matrix screen
// the characters are defined in the fiel "characters.c"
void display_number(uint8_t number)
{
    // only single digit numbers between 0 and 9 are possible.
    if (number < 20)
    {
        M5.dis.displaybuff((uint8_t *)image_numbers[number]);
    }
    else
    {
        M5.dis.displaybuff((uint8_t *)image_dot);
    }
}

//==============================================================
// function to display an animated star on the LED Matrix screen
void display_star()
{
    for (int i = 0; i < 2; i++)
    {
        for (int n = 0; n < 10; n++)
        {
            M5.dis.displaybuff((uint8_t *)image_star[n]);
            delay(100);
        }
    }
}

//==============================================================
// function to display an animated line on the LED Matrix screen
void display_line()
{
    for (int i = 0; i < 2; i++)
    {
        M5.dis.displaybuff((uint8_t *)image_line);
        delay(500);
        M5.dis.displaybuff((uint8_t *)image_left);
        delay(500);
        M5.dis.displaybuff((uint8_t *)image_line);
        delay(500);
        M5.dis.displaybuff((uint8_t *)image_right);
        delay(500);
    }
    M5.dis.displaybuff((uint8_t *)image_line);
    delay(500);
}

void setup()
{
    // start the ATOM device with serial and Display
    // begin(SerialEnable, I2CEnable, DisplayEnable)
    M5.begin(true, false, true);
    delay(50);
    Serial.println("M5ATOM Tilt-Game");
    Serial.println("v1.2 | 02.04.2020");
    // Show startup animation
    display_line();
    Serial.println("");
    Serial.println("INIT IMU");
    // check if IMU is ready
    if (M5.IMU.Init() == 0)
    {
        IMU_ready = true;
        Serial.println("[OK] INIT ready");
        M5.dis.displaybuff((uint8_t *)image_CORRECT);
    }
    else
    {
        IMU_ready = false;
        Serial.println("[ERR] IMU INIT failed!");
        M5.dis.displaybuff((uint8_t *)image_WRONG);
    }
    delay(1000);
    display_off_millis = millis() + 1000;
}

void loop()
{

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
    // Average the acceleration data
    // simple "running average" method without storing the data in an array
    accX_avg = ((accX_avg * (n_average - 1)) + accX) / n_average;
    accY_avg = ((accY_avg * (n_average - 1)) + accY) / n_average;
    accZ_avg = ((accZ_avg * (n_average - 1)) + accZ) / n_average;

   // Serial.println("X: ");
    //Serial.println(accX_avg);

   // Serial.println("Y: ");
    Serial.println(accY_avg);

   // Serial.println("Z: ");
    //Serial.println(accZ_avg);
    
    delay(5);
    M5.update();
}
