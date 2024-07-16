#include "GamePad.hpp"
#include "math.h"

#define Motor1 13
#define dirMotor1 12
#define Motor2 26
#define dirMotor2 25  

GamePad gamepad;


struct speeds_dir
{
    signed int mot1;
    signed int mot2;
    bool dir1;
    bool dir2;
};
typedef struct  speeds_dir speeds_dir;

speeds_dir rover;


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

float normalize(float val)
{

    float k = 0;
    if (abs(val) > 20)
    {
        k = (abs(val) / 512) * 255;
    }
    else
    {
        k = 0;
    }
    //    Console.printf("k: %d   yval: %d \n", k, val);
    return k;
}

void setup()
{
    rover.mot1 = 0;
    rover.mot2 = 0;
    rover.dir1 = 1;
    rover.dir2 = 0;
    Serial.begin(115200);
    gamepad.setup("9D:8C:03:1A:67:63");
    // 30:0E:D5:9F:97:2A
//9D:8C:03:1A:67:63
    pinMode(Motor1, OUTPUT);
    pinMode(Motor2, OUTPUT);
    pinMode(dirMotor1, OUTPUT);
    pinMode(dirMotor2, OUTPUT);
}

void loop()
{
    GamepadState state = gamepad.getState();
        int yVal = state.leftStick.y;
        for(int i=0;i<255;i++){

        }
        for(int i=255;i>0;i++){

        }
    // if (gamepad.update())
    // {
        
    //     int xVal = state.leftStick.x;
    //     //Console.printf("mot2 high: %d\n",state.leftStick.y);
    //         // Console.printf("normalize:%d    mot1:%d\n", normalize (yVal),rover.mot1);
    //     if (normalize (yVal) > rover.mot1  && rover.mot1 < 245)
    //     {
    //         // Console.printf("mot1 high0: %d\n", rover.mot1);
    //         rover.mot1 += (normalize(yVal) / 255) * 10;
    //         rover.mot2 += (normalize(yVal) / 255) * 10;
    //         // Console.printf("mot1 high01: %d\n", rover.mot1);
    //         // Console.printf("mot1 high: %d\n", rover.mot1);
    //         // Console.printf("mot2 high: %d\n", rover.mot2);
    //     }
    //     else if (  normalize (yVal)< rover.mot1 && rover.mot1 > 0)
    //     {
    //         // Console.printf("mot1 high1: %d\n", rover.mot1);
    //         rover.mot1 -= (normalize(yVal) / 255) * 10;
    //         rover.mot2 -= (normalize(yVal) / 255) * 10;
    //         // Console.printf("mot1 high11: %d\n", rover.mot1);
    //     // Console.printf("mot2 high: %d\n", rover.mot2);
    //     }
    //     Console.printf("motor1: %d\n     motor2: %d\n", rover.mot1,rover.mot2);
    // }

    // int yVal2 = state.rightStick.y;
    // analogWrite(Motor1, normalize(yVal) - ((xVal / 512) * 100));
    // analogWrite(Motor2, normalize(yVal) + ((xVal / 512) * 100));
    // digitalWrite(dirMotor1, dir(yVal, 1));
    // digitalWrite(dirMotor2, dir(yVal, 2));

    
        // Console.printf("1: %d\n", rover.mot1);
        // Console.printf("2: %d\n", rover.mot2);
    analogWrite(Motor1, rover.mot1);
    analogWrite(Motor2, rover.mot2);

    digitalWrite(dirMotor1, dir(yVal, 1));
    digitalWrite(dirMotor2, dir(yVal, 2));

    // Console.printf("y: %d\n",dir(yVal,1));
    // Use `state` to control your application
    // Serial.print("X: ");
    // Serial.println(state.leftStick.x);
    delay(50);
}
