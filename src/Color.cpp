#include "Color.h"
#include <algorithm>

using namespace std;


const Color Color::nullColor = Color(-1, -1, -1);

inline void Color::init(int r, int g, int b) {
    red = r;
    green = g; 
    blue = b;
}

Color::Color(int r, int g, int b) {
    init(r, g, b);
}

Color::Color() {
    init(0, 0, 0);
}



Color Color::darken(int amount)  const {
    int r = max(red - amount, 0);
    int g = max(green - amount, 0);
    int b = max(blue - amount, 0);
    return Color(r, g, b);
}

Color Color::lighten(int amount)  const {
    int r = min(red + amount, 255);
    int g = min(green + amount, 255);
    int b = min(blue + amount, 255);
    return Color(r, g, b);
}

Color Color::averageWith(const Color& other) const {
    return Color((red + other.red) / 2, (green + other.green) / 2, (blue + other.blue) / 2);
}

Color Color::averageWith(const Color& other1, const Color& other2, const Color& other3) const {
    return Color((red + other1.red + other2.red + other3.red) / 4, 
        (green + other1.green + other2.green + other3.green) / 4,
        (blue + other1.blue + other2.blue + other3.blue) / 4);
}


Color Color::randomlyChange(int maxAmount) const {
    // rand() returns value from {0, ..., 32767}
    int ch1 = ((rand() - 16384) * maxAmount) / 16384;
    int ch2 = ((rand() - 16384) * maxAmount) / 16384;
    int ch3 = ((rand() - 16384) * maxAmount) / 16384;
    return Color(min(255, max(0, red + ch1)), min(255, max(0, green + ch2)), min(255, max(0, blue + ch3)));
}


