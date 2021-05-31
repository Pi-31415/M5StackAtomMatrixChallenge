#include "M5Atom.h"
#include <stdlib.h>

int GRB_COLOR_WHITE = 0xffffff;
int GRB_COLOR_BLACK = 0x000000;
int GRB_COLOR_RED = 0x00ff00;
int GRB_COLOR_ORANGE = 0x7bff00;
int GRB_COLOR_YELLOW = 0xffff00;
int GRB_COLOR_GREEN = 0xff0000;
int GRB_COLOR_BLUE = 0x0000ff;
int GRB_COLOR_PURPLE = 0x008080;
int GRB_COLOR_PINK = 0x14ff93;

//Temperature Scales
int TempHighest = 0x39f13b;
int TempHigh = 0xcbfe3e;
int TempNorm = 0xffffff;
int TempLow = 0xa210db;
int TempLowest = 0x493fa2;

int activeColor = GRB_COLOR_WHITE;

int colorList[] = {GRB_COLOR_BLACK, GRB_COLOR_WHITE, GRB_COLOR_RED};

int colorListMode[] = {GRB_COLOR_BLACK, GRB_COLOR_PINK, GRB_COLOR_PINK};

float accX = 0;
float accY = 0;
float accZ = 0;

//Timekeeping Variable
unsigned int Time = 0;
unsigned int old_Time = 0;

bool IMU6886Flag = false;

float LOW_TOL = 100;
float HIGH_TOL = 900;

float scaledAccX = 0;
float scaledAccY = 0;
float scaledAccZ = 0;
int n_average = 1;

//List of screens
int black_screen[25] =
    {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0};

int full_screen[25] =
    {
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1};

int zero[25] =
    {
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 1,
        0, 1, 0, 0, 1,
        0, 1, 0, 0, 1,
        0, 0, 1, 1, 0};

int one[25] =
    {
        0, 0, 1, 0, 0,
        0, 1, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 1, 1, 1, 0};

int two[25] =
    {
        0, 1, 1, 1, 0,
        0, 0, 0, 0, 1,
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 0,
        0, 1, 1, 1, 1};

int three[25] =
    {
        0, 1, 1, 1, 0,
        0, 0, 0, 0, 1,
        0, 0, 1, 1, 0,
        0, 0, 0, 0, 1,
        0, 1, 1, 1, 0};

int four[25] =
    {
        0, 0, 0, 1, 0,
        0, 1, 0, 1, 0,
        0, 1, 1, 1, 1,
        0, 0, 0, 1, 0,
        0, 0, 0, 1, 0};

int five[25] =
    {
        0, 1, 1, 1, 1,
        0, 1, 0, 0, 0,
        0, 1, 1, 1, 0,
        0, 0, 0, 0, 1,
        0, 1, 1, 1, 0};

int six[25] =
    {
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 0,
        0, 1, 1, 1, 0,
        0, 1, 0, 0, 1,
        0, 0, 1, 1, 0};

int seven[25] =
    {
        0, 1, 1, 1, 1,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0};

int eight[25] =
    {
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 1,
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 1,
        0, 0, 1, 1, 0};

int nine[25] =
    {
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 1,
        0, 0, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 1, 1, 0};

int dot[25] =
    {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 0, 0};

//Roman Numerals
int ROM_1[25] =
    {
        1, 1, 1, 1, 1,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        1, 1, 1, 1, 1};

int ROM_2[25] =
    {
        1, 1, 1, 1, 1,
        0, 1, 0, 1, 0,
        0, 1, 0, 1, 0,
        0, 1, 0, 1, 0,
        1, 1, 1, 1, 1};

int ROM_3[25] =
    {
        1, 1, 1, 1, 1,
        0, 1, 1, 1, 0,
        0, 1, 1, 1, 0,
        0, 1, 1, 1, 0,
        1, 1, 1, 1, 1};

int ROM_4[25] =
    {
        1, 1, 1, 0, 1,
        0, 1, 1, 0, 1,
        0, 1, 1, 0, 1,
        0, 1, 0, 1, 0,
        1, 1, 1, 1, 0};

int ROM_5[25] =
    {
        1, 1, 0, 1, 1,
        0, 1, 0, 1, 0,
        0, 1, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0};
//F and C units

int F[25] =
    {
        0, 1, 1, 1, 1,
        0, 1, 0, 0, 0,
        0, 1, 1, 1, 0,
        0, 1, 0, 0, 0,
        0, 1, 0, 0, 0};

int C[25] =
    {
        1, 0, 0, 1, 1,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 1, 1};

int displayed_mode = 1;

int selected_mode = 1;

int *displayNumbers[10] = {zero, one, two, three, four, five, six, seven, eight, nine};

int *modeNumbers[10] = {zero, ROM_1, ROM_2, ROM_3, ROM_4, ROM_5};

bool switched_mode = false;

bool mode_selection_on = true;

float tempC = 0;

char buff[10]; //Buffer for holding the string of temperature

int dotDuration = 500;

float temp_avg = 0.0;

//Variables for graphing mode
float temp_data[] = {0.0, 0.0, 0.0, 0.0, 0.0};
float temp_graph_sum = 0.0;

void setup()
{
    M5.begin(true, false, true);
    delay(20);

    IMU6886Flag = M5.IMU.Init() == 0;

    if (!IMU6886Flag)
    {
        Serial.println("Error initializing the IMU!");
    }
}

void loop()
{
    if (IMU6886Flag)
    {

        //Sense Current Temperature
        String tempStringF = "";
        String tempStringC = "";

        M5.IMU.getTempData(&tempC);
        //Serial.printf(" Temp : %.2f C \r\n", tempC);

        dtostrf(tempC, 4, 2, buff);
        tempStringC += buff;
        tempStringC += "C";

        float tempF = tempC * 9 / 5 + 32;
        dtostrf(tempF, 4, 2, buff);
        tempStringF += buff;
        tempStringF += "F";
        //Serial.printf(" Temp : %.2f F \r\n", tempF);

        M5.IMU.getAccelData(&accX, &accY, &accZ);

        //Serial.printf("Accel: %.2f, %.2f, %.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

        scaledAccX = accX * 1000;
        scaledAccY = accY * 1000;
        scaledAccZ = accZ * 1000;

        //Selection of mode through button press
        if (M5.Btn.wasPressed())
        {
            //Serial.println("wasPressed");
            //Toggles the mode switch

            mode_selection_on = false;
        }

        if (abs(scaledAccX) < LOW_TOL && abs(scaledAccY) < LOW_TOL && abs(scaledAccZ) > HIGH_TOL && scaledAccZ > 0)
        {
            //Facing Bottom, read background temp as running average
            //Get Time
            Time = millis() / 1000.0;

            //Get Running Average of Temperature every second
            if (old_Time != Time)
            {
                temp_avg = ((temp_avg * (n_average - 1)) + tempC) / n_average;
                n_average++;
                Serial.println(temp_avg);
            }

            old_Time = Time;
            drawArray(black_screen, colorList);
        }

        else if (abs(scaledAccX) < LOW_TOL && abs(scaledAccY) < LOW_TOL && abs(scaledAccZ) > HIGH_TOL && scaledAccZ < 0)
        {
            //Top Facing Code
            switched_mode = false;

            if (mode_selection_on)
            {
                drawArray(modeNumbers[displayed_mode], colorListMode);
            }
            else
            {
                selected_mode = displayed_mode;
                //Mode activated

                if (selected_mode == 1)
                {
                    displayTemperature(tempStringC);
                }
                else if (selected_mode == 2)
                {
                    if(temp_avg == 0.0){
                        temp_avg = tempC;
                    }
                    tempStringC = temp_avg;
                    tempStringC += "C";
                    displayTemperature(tempStringC);
                }
                else if (selected_mode == 3)
                {
                    DisplayTemperatureScale(tempF);
                }
                else if (selected_mode == 4)
                {
                    DisplayGraph();
                }
                else if (selected_mode == 5)
                {
                    displayTemperature(tempStringF);
                }
            }
        }

        else if (abs(scaledAccX) < LOW_TOL && abs(scaledAccY) > HIGH_TOL && abs(scaledAccZ) < LOW_TOL && scaledAccY > 0)
        {
            //UpArrow
        }

        else if (abs(scaledAccX) < LOW_TOL && abs(scaledAccY) > HIGH_TOL && abs(scaledAccZ) < LOW_TOL && scaledAccY < 0)
        {
            //DownArrow
        }

        else if (abs(scaledAccX) > HIGH_TOL && abs(scaledAccY) < LOW_TOL && abs(scaledAccZ) < LOW_TOL && scaledAccX > 0)
        {
            mode_selection_on = true;
            //LeftArrow
            if (!switched_mode)
            {
                displayed_mode++;
                if (displayed_mode > 5)
                {
                    displayed_mode = 1;
                }
                else if (displayed_mode < 1)
                {
                    displayed_mode = 5;
                }
            }
            switched_mode = true;
            drawArray(modeNumbers[displayed_mode], colorListMode);
        }

        else if (abs(scaledAccX) > HIGH_TOL && abs(scaledAccY) < LOW_TOL && abs(scaledAccZ) < LOW_TOL && scaledAccX < 0)
        {
            mode_selection_on = true;
            //RightArrow
            if (!switched_mode)
            {
                displayed_mode--;
                if (displayed_mode > 5)
                {
                    displayed_mode = 1;
                }
                else if (displayed_mode < 1)
                {
                    displayed_mode = 5;
                }
            }
            switched_mode = true;
            drawArray(modeNumbers[displayed_mode], colorListMode);
        }
        else
        {
            //M5.dis.clear();
        }
    }

    M5.update();
}

void drawArray(int arr[], int colors[])
{
    for (int i = 0; i < 25; i++)
    {
        M5.dis.drawpix(i, colors[arr[i]]);
    }
}

void DisplayBlank()
{
    M5.dis.clear();
    drawArray(black_screen, colorList);
    delay(dotDuration);
}

void displayTemperature(String temperature)
{
    temperature.toUpperCase();

    int Length = temperature.length();

    for (int i = 0; i < Length; i++)
    {
        char currentChar = temperature.charAt(i);
        //Serial.println(currentChar);

        if (currentChar == '.')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(dot, colorList);
            delay(dotDuration);
        }
        else if (currentChar == '0')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(zero, colorList);
            delay(dotDuration);
        }
        else if (currentChar == '1')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(one, colorList);
            delay(dotDuration);
        }
        else if (currentChar == '2')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(two, colorList);
            delay(dotDuration);
        }
        else if (currentChar == '3')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(three, colorList);
            delay(dotDuration);
        }
        else if (currentChar == '4')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(four, colorList);
            delay(dotDuration);
        }
        else if (currentChar == '5')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(five, colorList);
            delay(dotDuration);
        }
        else if (currentChar == '6')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(six, colorList);
            delay(dotDuration);
        }
        else if (currentChar == '7')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(seven, colorList);
            delay(dotDuration);
        }
        else if (currentChar == '8')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(eight, colorList);
            delay(dotDuration);
        }
        else if (currentChar == '9')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(nine, colorList);
            delay(dotDuration);
        }
        else if (currentChar == 'C')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(C, colorList);
            delay(dotDuration);
        }
        else if (currentChar == 'F')
        {
            DisplayBlank();
            M5.dis.clear();
            drawArray(F, colorList);
            delay(dotDuration);
        }
        else if (currentChar == ' ')
        {
            DisplayBlank();
        }
    }
}

void DisplayColor(int fillColor)
{
    for (int i = 0; i < 25; i++)
    {
        M5.dis.drawpix(i, fillColor);
    }
}

void DisplayTemperatureScale(float tempF)
{
    float lowestTempF = 90;
    float lowTempF = 100;
    float midTempF = 110; //112.58
    float highTempF = 120;
    float highestTempF = 130;

    if (tempF < lowestTempF)
    {
        DisplayColor(GRB_COLOR_BLUE);
    }
    else if (lowestTempF < tempF && tempF < lowTempF)
    {
        DisplayColor(TempLowest);
    }
    else if (lowTempF < tempF && tempF < midTempF)
    {
        DisplayColor(TempLow);
    }

    else if (midTempF < tempF && tempF < highTempF)
    {
        DisplayColor(TempNorm);
    }

    else if (highTempF < tempF && tempF < highestTempF)
    {
        DisplayColor(TempHigh);
    }

    else if (tempF > highestTempF)
    {
        DisplayColor(TempHighest);
    }

        /*
    int TempHighest = 0x39f13b;
int TempHigh = 0xcbfe3e;
int TempNorm = 0xffffff;
int TempLow = 0xa210db;
int TempLowest = 0x493fa2;
    */

    M5.dis.drawpix(0, 4, TempLowest );   // Green
    M5.dis.drawpix(1, 4, TempLow );  // Green
    M5.dis.drawpix(2, 4, TempNorm);  // Green
    M5.dis.drawpix(3, 4, TempHigh); // Green
    M5.dis.drawpix(4, 4, TempHighest); // Green
}

void DisplayGraph()
{
    //Print out data array elements
    for (int i = 0; i < 5; i++)
    {
        M5.IMU.getTempData(&tempC);
        temp_data[i] = tempC;
    }

    //Find Average
    temp_graph_sum = 0;
    for (int i = 0; i < 5; i++)
    {
        temp_graph_sum += temp_data[i];
    }

    float temp_average = temp_graph_sum / 5.00;

    //Normalize to be accurate until 0.01 C
    for (int i = 0; i < 5; i++)
    {
        temp_data[i] = (temp_data[i] - temp_average) * 100.00;
    }
    //Shift the graph to middle of screen
    for (int i = 0; i < 5; i++)
    {
        temp_data[i] = temp_data[i] + 2;
    }

    //Plot array
    M5.dis.clear();
    M5.dis.drawpix(0, temp_data[0], TempNorm); // Green
    M5.dis.drawpix(1, temp_data[1], TempNorm); // Green
    M5.dis.drawpix(2, temp_data[2], TempNorm); // Green
    M5.dis.drawpix(3, temp_data[3], TempNorm); // Green
    M5.dis.drawpix(4, temp_data[4], TempNorm); // Green
    delay(250);
}