#include "mbed.h"
 
//class for 3 PWM color values for RGBLED
class LEDColor
{
public:
    LEDColor(float r, float g, float b);
    float red;
    float green;
    float blue;
};
LEDColor:: LEDColor(float r, float g, float b)
    : red(r), green(g), blue(b)
{
}
//Operator overload to adjust brightness with no color change
LEDColor operator * (const LEDColor& x, const float& b)
{
    return LEDColor(x.red*b,x.green*b,x.blue*b);
}
//Operator overload to add colors
LEDColor operator + (const LEDColor& x, const LEDColor& y)
{
    return LEDColor(x.red+y.red,x.green+y.green,x.blue+y.blue);
}
 
//Class to control an RGB LED using three PWM pins
class RGBLed
{
public:
    RGBLed(PinName redpin, PinName greenpin, PinName bluepin);
    void write(float red,float green, float blue);
    void write(LEDColor c);
    RGBLed operator = (LEDColor c) {
        write(c);
        return *this;
    };
private:
    PwmOut _redpin;
    PwmOut _greenpin;
    PwmOut _bluepin;
};
 
RGBLed::RGBLed (PinName redpin, PinName greenpin, PinName bluepin)
    : _redpin(redpin), _greenpin(greenpin), _bluepin(bluepin)
{
    //50Hz PWM clock default a bit too low, go to 2000Hz (less flicker)
    _redpin.period(0.0005);
}
 
void RGBLed::write(float red,float green, float blue)
{
    _redpin = red;
    _greenpin = green;
    _bluepin = blue;
}
void RGBLed::write(LEDColor c)
{
    _redpin = c.red;
    _greenpin = c.green;
    _bluepin = c.blue;
}