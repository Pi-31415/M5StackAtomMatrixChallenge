#include "M5Atom.h"

int GRB_COLOR_WHITE = 0xffffff;
int GRB_COLOR_BLACK = 0x000000;
int GRB_COLOR_RED = 0x00ff00;
int GRB_COLOR_ORANGE = 0xa5ff00;
int GRB_COLOR_YELLOW = 0xffff00;
int GRB_COLOR_GREEN = 0xff0000;
int GRB_COLOR_BLUE = 0x0000ff;
int GRB_COLOR_PURPLE = 0x008080;

int activeColor = GRB_COLOR_WHITE;

int colorList[] = {GRB_COLOR_BLACK, GRB_COLOR_GREEN, GRB_COLOR_RED};

float accX = 0;
float accY = 0;
float accZ = 0;

bool IMU6886Flag = false;

float LOW_TOL = 100;
float HIGH_TOL = 900;

float scaledAccX = 0;
float scaledAccY = 0;
float scaledAccZ = 0;

//List of screens
int black_screen[25] =
    {
        2, 0, 0, 0, 2,
        0, 2, 0, 2, 0,
        0, 0, 2, 0, 0,
        0, 2, 0, 2, 0,
        2, 0, 0, 0, 2};

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

int displayed_mode = 1;

int *displayNumbers[10] = {zero, one, two, three, four, five, six, seven, eight, nine};

bool switched_mode = false;

bool mode_selection_on = true;

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
        M5.IMU.getAccelData(&accX, &accY, &accZ);

        Serial.printf("Accel: %.2f, %.2f, %.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

        scaledAccX = accX * 1000;
        scaledAccY = accY * 1000;
        scaledAccZ = accZ * 1000;

        //Selection of mode through button press
        if (M5.Btn.wasPressed())
        {
            Serial.println("wasPressed");
            //Activates Green Screen
            mode_selection_on = false;
        }

        if (abs(scaledAccX) < LOW_TOL && abs(scaledAccY) < LOW_TOL && abs(scaledAccZ) > HIGH_TOL && scaledAccZ > 0)
        {
            //Facing Bottom
            drawArray(black_screen, colorList);
        }

        else if (abs(scaledAccX) < LOW_TOL && abs(scaledAccY) < LOW_TOL && abs(scaledAccZ) > HIGH_TOL && scaledAccZ < 0)
        {
            //Top Facing Code
            switched_mode = false;

            if (mode_selection_on)
            {
                drawArray(displayNumbers[displayed_mode], colorList);
            }
            else
            {
                //Mode activated
                drawArray(full_screen, colorList);
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
            drawArray(displayNumbers[displayed_mode], colorList);
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
            drawArray(displayNumbers[displayed_mode], colorList);
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