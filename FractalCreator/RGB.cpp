//
//  RGB.cpp
//  FractalCreator
//
//  Created by Rich Beans on 14/09/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#include "RGB.hpp"

// Because when we are calculating the colour we are using a uint8_t we do not need to worry about the value of the below operations falling outside of the 0 to 255 range. Values outside of this range will automatically "wrap" as high order bits are just discarded when maximum value of the data type is reached.
RGB operator-(const RGB& first, const RGB& second) {
    return RGB(first.r - second.r, first.g - second.g, first.b - second.b);
};

RGB operator+(const RGB& first, const RGB& second) {
    return RGB(first.r + second.r, first.g + second.g, first.b + second.b);
};

RGB operator*(const RGB& first, const RGB& second) {
    return RGB(first.r * second.r, first.g * second.g, first.b * second.b);
};

RGB operator/(const RGB& first, const RGB& second) {
    return RGB(first.r / second.r, first.g / second.g, first.b / second.b);
};
