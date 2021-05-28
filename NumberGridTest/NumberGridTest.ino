#include "M5Atom.h"

int GRB_COLOR_WHITE = 0xffffff;
int GRB_COLOR_BLACK = 0x000000;
int GRB_COLOR_RED = 0x00ff00;
int GRB_COLOR_ORANGE = 0xa5ff00;
int GRB_COLOR_YELLOW = 0xffff00;
int GRB_COLOR_GREEN = 0xff0000;
int GRB_COLOR_BLUE = 0x0000ff;
int GRB_COLOR_PURPLE = 0x008080;

int activeColor = GRB_COLOR_RED;

int colorList[] = {GRB_COLOR_BLACK, activeColor};

int one[25] = 
{
  0,0,1,0,0,
  0,1,1,0,0,
  0,0,1,0,0,
  0,0,1,0,0,
  0,1,1,1,0
};

int two[25] = 
{
  0,1,1,1,0,
  0,0,0,0,1,
  0,0,1,1,0,
  0,1,0,0,0,
  0,1,1,1,1
};

int three[25] = 
{
  0,1,1,1,0,
  0,0,0,0,1,
  0,0,1,1,0,
  0,0,0,0,1,
  0,1,1,1,0
};

int four[25] = 
{
  0,0,0,1,0,
  0,1,0,1,0,
  0,1,1,1,1,
  0,0,0,1,0,
  0,0,0,1,0
};

int five[25] = 
{
  0,1,1,1,1,
  0,1,0,0,0,
  0,1,1,1,0,
  0,0,0,0,1,
  0,1,1,1,0
};

int six[25] = 
{
  0,0,1,1,0,
  0,1,0,0,0,
  0,1,1,1,0,
  0,1,0,0,1,
  0,0,1,1,0
};

int *displayNumbers[6] = { one, two, three, four, five, six };

void setup() 
{
  randomSeed(analogRead(0));
  M5.begin(true, false, true);
  delay(20);
}

void loop() 
{
  if(M5.Btn.wasReleased())
  {
    int numberToShow = random(0, 6);

    Serial.println(numberToShow + 1);
    randomPixelAnimation(activeColor);

    drawArray2(displayNumbers[numberToShow], colorList);
  }

  if(M5.Btn.releasedFor(10000))
  {
    M5.dis.clear();
  }

  delay(50);
  M5.update();
}

void drawArray2(int arr[], int colors[])
{
  for(int i = 0; i < 25; i++)
  {
      M5.dis.drawpix(i, colors[arr[i]]);
  }
}

void randomPixelAnimation(int pixelColor)
{
  M5.dis.clear();
  
  for(int i = 0; i < 50; i++)
  {
    int currentPixel = random(0, 25);
    M5.dis.drawpix(currentPixel, pixelColor);
    delay(1);
    M5.dis.drawpix(currentPixel, GRB_COLOR_BLACK);
    delay(1);
  }
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
