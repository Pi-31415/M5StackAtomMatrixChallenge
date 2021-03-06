/*
   M5StackAtomMatrixChallenge.ino

   By: Umer Bin Liaqat, Omar Elkammah, Sherifa Yakubu, Pi Ko
   Date: 28 May 2021

   Assignment 2 of ENGR-UH 1021J: Design & Innovation Summer 2021
*/

#include "M5Atom.h"

//Define Colors
//GRB not RGB
int GRB_COLOR_WHITE = 0xffffff;
int GRB_COLOR_BLACK = 0x000000;
int GRB_COLOR_RED = 0x00ff00;

//Define Patterns
int full_screen[25] =
{
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1
};


//Array of patterns for display
int *display[1] = { full_screen };


void setup()
{
  M5.begin(true, false, true);
  delay(50);
  M5.dis.drawpix(0, 0xf00000);
}

int STEP = 0;
bool BLINK_MODE_ON = false;

void loop()
{

  if (M5.Btn.wasPressed())
  {
    //Increases the STEP everytime the button is pressed, and changes modes
    STEP++;
    Serial.println("isPressed");
  }

  if (STEP == 0)
  {
    //Nothing on screen, blank (Step 1)
    BLINK_MODE_ON = false;
    M5.dis.clear();
  }
  else if (STEP == 1)
  {
    //Flash Red (Step 2)
    BLINK_MODE_ON = true;
    M5.dis.clear();
    turn_on_lights(display[0], GRB_COLOR_RED);
  }
  else if (STEP == 2)
  {
    //Flash Red (Step 2)
    BLINK_MODE_ON = true;
    M5.dis.clear();
    turn_on_lights(display[0], GRB_COLOR_WHITE);
  }

  //This is for debugging purpose, listens to serial at 115200 baud
  Serial.println(STEP);
  
  if (BLINK_MODE_ON)
  {
    delay(100);
    M5.dis.clear();
    delay(100);
  }
  
  delay(50);
  M5.update();
}


void turn_on_lights(int arr[], int color)
{
  for (int i = 0; i < 25; i++)
  {
    M5.dis.drawpix(i, color);
  }
}
