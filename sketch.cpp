#include "GamePad.hpp"
#include "math.h"

#define Motor1 2
#define dirMotor1 19
#define Motor2 4
#define dirMotor2 32

GamePad gamepad;

void setup()
{
    Serial.begin(115200);
    gamepad.setup("30:0E:D5:9F:97:2A");

    pinMode(Motor1, OUTPUT);
    pinMode(Motor2, OUTPUT);
    pinMode(dirMotor1, OUTPUT);
    pinMode(dirMotor2, OUTPUT);
}

struct speeds_dir
{
    int mot1;
    int mot2;
    bool dir1;
    bool dir2;
} speeds_dir;

speeds_dir rover;

rover.mot1 = 0;
rover.mot2 = 0;
rover.dir1 = 1;
rover.dir2 = 0;

int normalize(float val)
{

    int k = 0;
    if (abs(val) > 20)
    {
        k = (abs(val) / 512) * 255;
    }
    else
    {
        k = 0;
    }
    Console.printf("k: %d   yval: %d\n", k, val);
    return k;
}

bool dir(int val, int mot)
{
    bool forward = 0;
    if ((val > 0) && mot == 1)
    {
        forward = 1;
    }
    else if ((val > 0) && mot == 2)
    {
        forward = 0;
    }
    else if ((val <= 0) && mot == 1)
    {
        forward = 0;
    }
    else if ((val <= 0) && mot == 2)
    {
        forward = 1;
    }
    return forward;
}

void loop()
{
    GamepadState state = gamepad.getState();
    if (gamepad.update())
    {
        // Console.printf("y: %d\n", state.leftStick.y);
        int yVal = state.leftStick.y;
        int xVal = state.leftStick.x;
    }

    // int yVal2 = state.rightStick.y;
    // analogWrite(Motor1, normalize(yVal) - ((xVal / 512) * 100));
    // analogWrite(Motor2, normalize(yVal) + ((xVal / 512) * 100));
    // digitalWrite(dirMotor1, dir(yVal, 1));
    // digitalWrite(dirMotor2, dir(yVal, 2));

    if normalize (yVal)
        > rover.mot1
        {
            rover.mot1 += (normalize(yval) / 255) * 10;
            rover.mot2 += (normalize(yval) / 255) * 10;
        }
    else if normalize (yVal)
        < rover.mot1
        {
            rover.mot1 -= (normalize(yval) / 255) * 10;
            rover.mot2 -= (normalize(yval) / 255) * 10;
        }

    analogWrite(Motor1, rover.mot1);
    analogWrite(Motor2, rover.mot2);

    digitalWrite(dirMotor1, dir(yVal, 1));
    digitalWrite(dirMotor2, dir(yVal, 2));

    // Console.printf("y: %d\n",dir(yVal,1));
    // Use `state` to control your application
    // Serial.print("X: ");
    // Serial.println(state.leftStick.x);
    delay(20);
}