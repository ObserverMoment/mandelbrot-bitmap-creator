//
//  Mandlebrot.cpp
//  FractalCreator
//
//  Created by Rich Beans on 23/08/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#include <complex>
#include "Mandlebrot.hpp"

// Iterate over fc(z) = z^2 + c.
// Feeding the result back in
// if f(z) becomes > 2, you are not in the Mandlebrot set.
// if after a set number of iterations (the more you do, the more detailed your image will be) you are still <= 2
// You are in the Mandlebrot set.
// You can use the number of iterations that you reach to decide on the colour for the pixel.
int Mandlebrot::mandleBrotAlgorithm(double x, double y) {

    std::complex<double> z = 0;
    std::complex<double> c(x,y);
    int iterations = 0;
    
    while (abs(z) <= 2 && iterations < MAX_ITERATIONS) {
        z = z*z + c;
        iterations++;
    }
    
    return iterations; // Returns the number of iterations that it took before the result became greater than 2.
};
