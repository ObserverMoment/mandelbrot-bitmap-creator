//
//  Mandlebrot.hpp
//  FractalCreator
//
//  Created by Rich Beans on 23/08/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#ifndef Mandlebrot_hpp
#define Mandlebrot_hpp

#include <stdio.h>
#include <iostream>

class Mandlebrot {
public:
    // Higher iterations will mean higher resolution, but also longer processing times.
    static const int MAX_ITERATIONS{1000};
    
public:
    Mandlebrot();
    ~Mandlebrot();
    
    static int mandleBrotAlgorithm(double x, double y);
};

#endif /* Mandlebrot_hpp */
