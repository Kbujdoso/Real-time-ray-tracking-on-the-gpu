#include "Color.h"
Color::Color() : red(0), blue(0), green(0) {}
Color::Color(int red_val, int blue_val, int green_val){
    red = red_val;
    blue = blue_val;
    green = green_val;
}
int Color::Red(){
    return red;
}
int Color::Blue(){
    return blue;
}
int Color::Green(){
    return green;
}

Color operator*(Color color, float scalar){
    float red = color.Red() * scalar;
    float green = color.Green() * scalar;
    float blue = color.Blue() * scalar;
    return Color(red, blue, green);
}