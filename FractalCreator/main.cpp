//
//  main.cpp
//  FractalCreator
//
//  Created by Rich Beans on 18/08/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

// NOTE: Mandelbrot is misspelt throughout this program...! (as Mandlebrot).
#include <iostream>
#include <cstdint>
#include <memory>
#include "Bitmap.hpp"
#include "Mandlebrot.hpp"
#include "ZoomList.h"
#include "FractalCreator.hpp"
#include "RGB.hpp"

int main(int argc, const char * argv[]) {
    
    // Create the bitmap, zoomList (within the FractalCreator class) and the main fractalCreator object.
    // An initial zoom object is also added to the zoomList during the running of the constructor.
    FractalCreator fractalCreator(1000, 800);
    
    fractalCreator.addColourRange(RGB(0,0,0), 0.0);
    fractalCreator.addColourRange(RGB(255,255,0), 0.5);
    fractalCreator.addColourRange(RGB(0,255,0), 0.6);
    fractalCreator.addColourRange(RGB(0,0,255), 0.7);
    fractalCreator.addColourRange(RGB(100,255,255), 0.8);
    fractalCreator.addColourRange(RGB(0,0,0), 1.0);
    
    // The addZoom function now just takes in a pixel postion (x and y coords) and a zoom amount. The necessary translations are donoe within the addZoom function.
    fractalCreator.addZoom(415,100,0.2); // x,y,zoom.
    fractalCreator.run("test.bmp");
    
    std::cout << "Finished" << std::endl;
    
    return 0;
}
