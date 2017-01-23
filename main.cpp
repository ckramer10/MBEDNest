#include "mbed.h"
#include "uLCD_4DGL.h"
#include "PinDetect.h"
#include "TMP36.h"
#include "LEDColor.h"
#include "Speaker.h"


TMP36 myTMP36(p15);
DigitalOut P16(p16);
DigitalOut P17(p17);
DigitalOut P18(p18);
DigitalOut P19(p19);
DigitalOut P20(p20);
uLCD_4DGL uLCD(p28, p27, p29); // create a global lcd object
PinDetect pb1(p21);
PinDetect pb2(p22);
PinDetect pb3(p23);
RGBLed myRGBled(p24,p25,p26);
Speaker mySpeaker(p18);
enum Statetype {HEAT_OFF, HEAT_ON, COOL_OFF, COOL_ON, OFF_STATE};
const LEDColor orange(1.0,0.0,0.0);
const LEDColor green(0.0,0.2,0.0);
const LEDColor blue(0.0,0.0,1.0);
float tempC,tempF;
float heatTemp = 75.0;
float coolTemp = 80.0;
float nightHeatTemp = 70.0;
float nightCoolTemp = 85.0;
Statetype prevState;
Statetype state = OFF_STATE;
time_t seconds = time(NULL);
tm * now;
int mins;
int hours;

void increaseHeatTemp()
{
    heatTemp++;
};

void decreaseHeatTemp()
{
    heatTemp--;
};

void increaseCoolTemp()
{
    coolTemp++;
};

void decreaseCoolTemp()
{
    coolTemp--;
};

int main()
{
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    //set_time(1454455200); //At night test
    set_time(1454448000); //Day test
    while(1) {
        switch (state) {
            case (HEAT_OFF):
                while (state == HEAT_OFF) {
                    bool flag = true;
                    myRGBled = orange;
                    tempC = myTMP36.read() * .5;
                    tempF = (9.0*tempC)/5.0 + 32.0;
                    seconds = time(NULL);
                    now = localtime( &seconds);
                    mins = now->tm_min;
                    hours = now->tm_hour;
                    if ((hours >= 23 || hours < 6) && flag) {
                        heatTemp = nightHeatTemp;
                        flag = false;
                    }
                    if (prevState != HEAT_OFF) {
                        uLCD.background_color(BLACK);
                        uLCD.textbackground_color(BLACK);
                        uLCD.color(WHITE);
                        uLCD.cls();
                        prevState = HEAT_OFF;
                    }
                    if (hours >= 23 || hours < 6) {
                        uLCD.filled_circle(105, 100, 6,0xFFFFFF);
                        uLCD.filled_circle(100, 100, 6,0x000000);
                    }
                    uLCD.locate(5,1);
                    uLCD.printf("Set To:");
                    uLCD.locate(6,3);
                    uLCD.text_width(2);     // 2x normal size
                    uLCD.text_height(2);
                    uLCD.printf("%2.0F", heatTemp);
                    uLCD.text_width(1);     // 2x normal size
                    uLCD.text_height(1);
                    uLCD.locate(5,6);
                    uLCD.printf("Heat OFF");
                    uLCD.locate(6,8);
                    uLCD.printf("%d:%d", hours, mins);
                    uLCD.locate(5,10);
                    uLCD.printf("Inside:");
                    uLCD.locate(6,12);
                    uLCD.text_width(2);     // 2x normal size
                    uLCD.text_height(2);
                    uLCD.printf("%2.0F ", tempF);
                    uLCD.text_width(1);     // 2x normal size
                    uLCD.text_height(1);
                    if (pb1 == 0) {
                        mySpeaker.PlayNote(800.00, 0.2, 1.0);
                        decreaseHeatTemp();
                    } else if (pb2 == 0) {
                        mySpeaker.PlayNote(800.00, 0.2, 1.0);
                        increaseHeatTemp();
                    }
                    if (tempF < heatTemp) {
                        state = HEAT_ON;
                        prevState = HEAT_OFF;
                    }
                    if (pb3 == 0) {
                        if (tempF > coolTemp) {
                            state = COOL_ON;
                        } else {
                            state = COOL_OFF;
                        }
                        prevState = HEAT_OFF;
                        mySpeaker.PlayNote(400.00, 0.6, 1.0);
                    }
                }
                break;
            case (HEAT_ON) :
                while (state == HEAT_ON) {
                    bool flag = true;
                    myRGBled = orange;
                    tempC = myTMP36.read() * .5;
                    tempF = (9.0*tempC)/5.0 + 32.0;
                    seconds = time(NULL);
                    now = localtime( &seconds);
                    mins = now->tm_min;
                    hours = now->tm_hour;
                    if ((hours >= 23 || hours < 6) && flag) {
                        heatTemp = nightHeatTemp;
                        flag = false;
                    }
                    if (prevState != HEAT_ON) {
                        uLCD.background_color(0XFF8000);
                        uLCD.textbackground_color(0XFF8000);
                        uLCD.color(WHITE);
                        uLCD.cls();
                        prevState = HEAT_ON;
                    }
                    if (hours >= 23 || hours < 6) {
                        uLCD.filled_circle(105, 100, 6,0xFFFFFF);
                        uLCD.filled_circle(100, 100, 6,0xFF8000);
                    }
                    uLCD.locate(5,1);
                    uLCD.printf("Set To:");
                    uLCD.locate(6,3);
                    uLCD.text_width(2);     // 2x normal size
                    uLCD.text_height(2);
                    uLCD.printf("%2.0F", heatTemp);
                    uLCD.text_width(1);     // 2x normal size
                    uLCD.text_height(1);
                    uLCD.locate(3,6);
                    uLCD.printf("Heating ON");
                    uLCD.locate(6,8);
                    uLCD.printf("%d:%d", hours, mins);
                    uLCD.locate(5,10);
                    uLCD.printf("Inside:");
                    uLCD.locate(6,12);
                    uLCD.text_width(2);     // 2x normal size
                    uLCD.text_height(2);
                    uLCD.printf("%2.0F ", tempF);
                    uLCD.text_width(1);     // 2x normal size
                    uLCD.text_height(1);
                    if (pb1 == 0) {
                        mySpeaker.PlayNote(800.00, 0.2, 1.0);
                        decreaseHeatTemp();
                    } else if (pb2 == 0) {
                        mySpeaker.PlayNote(800.00, 0.2, 1.0);
                        increaseHeatTemp();
                    }
                    if (tempF > heatTemp) {
                        state = HEAT_OFF;
                        prevState = HEAT_ON;
                    }
                    if (pb3 == 0) {
                        if (tempF > coolTemp) {
                            state = COOL_ON;
                        } else {
                            state = COOL_OFF;
                        }
                        prevState = HEAT_ON;
                        mySpeaker.PlayNote(400.00, 0.6, 1.0);
                    }
                }
                break;
            case (OFF_STATE):
                while (state == OFF_STATE) {
                    myRGBled = green;
                    tempC = myTMP36.read() * .5;
                    tempF = (9.0*tempC)/5.0 + 32.0;
                    seconds = time(NULL);
                    now = localtime( &seconds);
                    mins = now->tm_min;
                    hours = now->tm_hour;
                    if (prevState != OFF_STATE) {
                        uLCD.background_color(0x78AB46);
                        uLCD.textbackground_color(0x78AB46);
                        uLCD.color(WHITE);
                        uLCD.cls();
                        prevState = OFF_STATE;
                    }
                    if (hours >= 23 || hours < 6) {
                        uLCD.filled_circle(105, 100, 6,0xFFFFFF);
                        uLCD.filled_circle(100, 100, 6,0x78AB46);
                    }
                    uLCD.locate(5,1);
                    uLCD.printf("Set To:");
                    uLCD.locate(6,3);
                    uLCD.text_width(2);     // 2x normal size
                    uLCD.text_height(2);
                    uLCD.printf("XX");
                    uLCD.text_width(1);     // 2x normal size
                    uLCD.text_height(1);
                    uLCD.locate(4,6);
                    uLCD.printf("System OFF");
                    uLCD.locate(6,8);
                    uLCD.printf("%d:%d", hours, mins);
                    uLCD.locate(5,10);
                    uLCD.printf("Inside:");
                    uLCD.locate(6,12);
                    uLCD.text_width(2);     // 2x normal size
                    uLCD.text_height(2);
                    uLCD.printf("%2.0F ", tempF);
                    uLCD.text_width(1);     // normal size
                    uLCD.text_height(1);
                    if (pb3 == 0) {
                        if (tempF < heatTemp) {
                            state = HEAT_ON;
                        } else {
                            state = HEAT_OFF;
                        }
                        mySpeaker.PlayNote(400.00, 0.6, 1.0);
                    }
                    break;
                case (COOL_OFF):
                    while (state == COOL_OFF) {
                        bool flag = true;
                        myRGBled = blue;
                        tempC = myTMP36.read() * .5;
                        tempF = (9.0*tempC)/5.0 + 32.0;
                        seconds = time(NULL);
                        now = localtime( &seconds);
                        mins = now->tm_min;
                        hours = now->tm_hour;
                        if ((hours >= 23 || hours < 6) && flag) {
                            coolTemp = nightCoolTemp;
                            flag = false;
                        }
                        if (prevState != COOL_OFF) {
                            uLCD.background_color(BLACK);
                            uLCD.textbackground_color(BLACK);
                            uLCD.color(WHITE);
                            uLCD.cls();
                            prevState = COOL_OFF;
                        }
                        if (hours >= 23 || hours < 6) {
                            uLCD.filled_circle(105, 100, 6,0xFFFFFF);
                            uLCD.filled_circle(100, 100, 6,0x000000);
                        }
                        uLCD.locate(5,1);
                        uLCD.printf("Set To:");
                        uLCD.locate(6,3);
                        uLCD.text_width(2);     // 2x normal size
                        uLCD.text_height(2);
                        uLCD.printf("%2.0F", coolTemp);
                        uLCD.text_width(1);     // 2x normal size
                        uLCD.text_height(1);
                        uLCD.locate(4,6);
                        uLCD.printf("Cool OFF");
                        uLCD.locate(6,8);
                        uLCD.printf("%d:%d", hours, mins);
                        uLCD.locate(5,10);
                        uLCD.printf("Inside:");
                        uLCD.locate(6,12);
                        uLCD.text_width(2);     // 2x normal size
                        uLCD.text_height(2);
                        uLCD.printf("%2.0F ", tempF);
                        uLCD.text_width(1);     // 2x normal size
                        uLCD.text_height(1);
                        if (pb1 == 0) {
                            mySpeaker.PlayNote(800.00, 0.2, 1.0);
                            decreaseCoolTemp();
                        } else if (pb2 == 0) {
                            mySpeaker.PlayNote(800.00, 0.2, 1.0);
                            increaseCoolTemp();
                        }
                        if (tempF > coolTemp) {
                            state = COOL_ON;
                            prevState = COOL_OFF;
                        }
                        if (pb3 == 0) {
                            state = OFF_STATE;
                            prevState = COOL_OFF;
                            mySpeaker.PlayNote(400.00, 0.6, 1.0);
                        }
                    }
                    break;
                case (COOL_ON) :
                    while (state == COOL_ON) {
                        bool flag = true;
                        myRGBled = blue;
                        tempC = myTMP36.read() * .5;
                        tempF = (9.0*tempC)/5.0 + 32.0;
                        seconds = time(NULL);
                        now = localtime( &seconds);
                        mins = now->tm_min;
                        hours = now->tm_hour;
                        if ((hours >= 23 || hours < 6) && flag) {
                            coolTemp = nightCoolTemp;
                            flag = false;
                        }
                        if (prevState != COOL_ON) {
                            uLCD.background_color(BLUE);
                            uLCD.textbackground_color(BLUE);
                            uLCD.color(WHITE);
                            uLCD.cls();
                            prevState = COOL_ON;
                        }
                        if (hours >= 23 || hours < 6) {
                            uLCD.filled_circle(105, 100, 6,0xFFFFFF);
                            uLCD.filled_circle(100, 100, 6,0x0000FF);
                        }
                        uLCD.locate(5,1);
                        uLCD.printf("Set To:");
                        uLCD.locate(6,3);
                        uLCD.text_width(2);     // 2x normal size
                        uLCD.text_height(2);
                        uLCD.printf("%2.0F", coolTemp);
                        uLCD.text_width(1);     // 2x normal size
                        uLCD.text_height(1);
                        uLCD.locate(3,6);
                        uLCD.printf("Cooling ON");
                        uLCD.locate(6,8);
                        uLCD.printf("%d:%d", hours, mins);
                        uLCD.locate(5,10);
                        uLCD.printf("Inside:");
                        uLCD.locate(6,12);
                        uLCD.text_width(2);     // 2x normal size
                        uLCD.text_height(2);
                        uLCD.printf("%2.0F ", tempF);
                        uLCD.text_width(1);     // 2x normal size
                        uLCD.text_height(1);
                        if (pb1 == 0) {
                            mySpeaker.PlayNote(800.00, 0.2, 1.0);
                            decreaseCoolTemp();
                        } else if (pb2 == 0) {
                            mySpeaker.PlayNote(800.00, 0.2, 1.0);
                            increaseCoolTemp();

                        }
                        if (tempF < coolTemp) {
                            state = COOL_OFF;
                            prevState = COOL_ON;
                        }
                        if (pb3 == 0) {
                            state = OFF_STATE;
                            prevState = COOL_ON;
                            mySpeaker.PlayNote(400.00, 0.6, 1.0);
                        }
                    }
                    break;
                }
        }
        wait(1);
    }
}