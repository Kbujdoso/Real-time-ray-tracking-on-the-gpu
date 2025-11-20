#ifndef COLOR_H
#define COLOR_H
class Color{
    private:
        int red;
        int blue; 
        int green;
    public: 
        Color();
        Color(int red, int blue, int green);
        int Red();
        int Blue();
        int Green();

    };
    Color operator*(Color color, float scalar);
#endif