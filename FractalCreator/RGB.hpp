//
//  RGB.hpp
//  FractalCreator
//
//  Created by Rich Beans on 14/09/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#ifndef RGB_hpp
#define RGB_hpp

#include <stdio.h>

struct RGB {
    double r;
    double g;
    double b;
    
    RGB(double r, double g, double b): r(r), g(g), b(b) {};
    
};

// Overloaded arithmetic operators will allow us to play around with colour changes throughout the image.
RGB operator-(const RGB& first, const RGB& second);
RGB operator+(const RGB& first, const RGB& second);
RGB operator*(const RGB& first, const RGB& second);
RGB operator/(const RGB& first, const RGB& second);

#endif /* RGB_hpp */
