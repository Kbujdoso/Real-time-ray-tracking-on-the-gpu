#ifndef COLOR_H
#define COLOR_H
class Color{
    private:
        int red;
        int green;
        int blue; 
    public: 
        Color();
        Color(int red, int green, int blue);
        int Red();
        int Blue();
        int Green();

    };
    Color operator*(Color color, float scalar);
    Color operator*(Color color1, Color color2);
    Color operator+(Color color1, Color color2);
#endif