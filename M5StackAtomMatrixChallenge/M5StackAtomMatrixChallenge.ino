/**
 * M5StackAtomMatrixChallenge.ino
 *
 * By: Umer Bin Liaqat, Omar Elkammah, Sherifa Yakubu, Pi Ko
 * Date: 28 May 2021
 *
 * Assignment 2 of ENGR-UH 1021J: Design & Innovation Summer 2021
 */

#include "M5Atom.h"

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
    //Nothing on screen
    BLINK_MODE_ON = false;
    M5.dis.clear();
    M5.dis.drawpix(0, 0x00f000);
  }
  else if (STEP == 1)
  {
    //Only 1 red LED
    BLINK_MODE_ON = false;
    M5.dis.clear();
    M5.dis.drawpix(2, 0x00f000);
  }
  else if (STEP == 2)
  {
    //Should paint the whole screen red
    BLINK_MODE_ON = true;
    M5.dis.clear();
    M5.dis.drawpix(0, 0x00f000);
    M5.dis.drawpix(1, 0x00f000);
    M5.dis.drawpix(2, 0x00f000);
    M5.dis.drawpix(3, 0x00f000);
    M5.dis.drawpix(4, 0x00f000);
    M5.dis.drawpix(5, 0x00f000);
    M5.dis.drawpix(6, 0x00f000);
    M5.dis.drawpix(7, 0x00f000);
    M5.dis.drawpix(8, 0x00f000);
    M5.dis.drawpix(9, 0x00f000);
    M5.dis.drawpix(10, 0x00f000);
    M5.dis.drawpix(11, 0x00f000);
    M5.dis.drawpix(12, 0x00f000);
    M5.dis.drawpix(13, 0x00f000);
    M5.dis.drawpix(14, 0x00f000);
    M5.dis.drawpix(15, 0x00f000);
    M5.dis.drawpix(16, 0x00f000);
    M5.dis.drawpix(17, 0x00f000);
    M5.dis.drawpix(18, 0x00f000);
    M5.dis.drawpix(19, 0x00f000);
    M5.dis.drawpix(20, 0x00f000);
    M5.dis.drawpix(21, 0x00f000);
    M5.dis.drawpix(22, 0x00f000);
    M5.dis.drawpix(23, 0x00f000);
    M5.dis.drawpix(24, 0x00f000);
    M5.dis.drawpix(25, 0x00f000);
  }
  else if (STEP == 3)
  {
    //Only 1 red LED
    BLINK_MODE_ON = false;
    M5.dis.clear();
    M5.dis.drawpix(3, 0x00f000);
  }
  else if (STEP == 4)
  {
    //Only 1 red LED
    BLINK_MODE_ON = false;
    M5.dis.clear();
    M5.dis.drawpix(4, 0x00f000);
  }
  else if (STEP == 5)
  {
    //Only 1 red LED
    BLINK_MODE_ON = false;
    M5.dis.clear();
    M5.dis.drawpix(5, 0x00f000);
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
