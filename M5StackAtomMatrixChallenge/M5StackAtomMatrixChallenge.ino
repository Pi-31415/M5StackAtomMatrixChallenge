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
int GRB_COLOR_PURPLE = 0x0095B3;

//Define Patterns
int full_screen[25] =
{
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1,
  1, 1, 1, 1, 1
};

int char_A[25] =
{
  0, 0, 1, 0, 0,
  0, 1, 0, 1, 0,
  1, 0, 0, 0, 1,
  1, 1, 1, 1, 1,
  1, 0, 0, 0, 1
};

//Array of patterns for display
int *display[6] = { full_screen, char_A };


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
<<<<<<< Updated upstream
    drawArray2(display[0], GRB_COLOR_PURPLE);
=======
    drawArray2(display[1], GRB_COLOR_RED);
>>>>>>> Stashed changes
  }
  else if (STEP == 2)
  {
    //Flash Red (Step 2)
    BLINK_MODE_ON = true;
    M5.dis.clear();
    drawArray2(display[1], GRB_COLOR_WHITE);
  }

  //This is for debugging purpose
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


void drawArray2(int arr[], int color)
{
  for (int i = 0; i < 25; i++)
  {
    M5.dis.drawpix(i, color);
  }
}
