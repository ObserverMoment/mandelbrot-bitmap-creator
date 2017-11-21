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
#include <math.h>
#include "Bitmap.hpp"
#include "Mandlebrot.hpp"
#include "ZoomList.h"

int main(int argc, const char * argv[]) {
    int const WIDTH = 1000;
    int const HEIGHT = 800;
    
    Bitmap bitmap(WIDTH,HEIGHT);
    
    // Create the zoomList.
    ZoomList zoomList(WIDTH, HEIGHT);
    
    // Setup initial zoom in the list. This needs to be centered on the screen, and at 0,0 fractal co-ordinate. With a scale of 1.0.
    zoomList.addZoom(Zoom(295, 580, 0.05));
    
    // We only need to go up to MAX_ITERATIONS because we are intentionally ignoring the all the values that hit the max_iterations value. We do this because we want a smooth gradient across the histogram and when we run the algorithm we actually get a smooth, decreasing gradient up until MAX and then MAX is a very large number.
    std::unique_ptr<int[]> histogram(new int[Mandlebrot::MAX_ITERATIONS]{0});
    std::unique_ptr<int[]> pixelIterations(new int[WIDTH * HEIGHT]{0});
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // TODO
            // Instead of the code below you can use the zoomList.doZoom method to convert from screen pixel to a scaled X and Y value based on the zoomList current x, y and scale values. Then pass these values to the mandlebrot algo for processing.
            std::pair<double, double> scaledValues = zoomList.doZoom(x,y);
            
            
            // Convert from screen pixel to cartesian co-ords with a range of -1->1
            // It is best to scale the x and y values by the same amount so that the resulting image of the mandlebrot set is not squashed or stretched.
            //            double scaledX = ((x - WIDTH/2.0 - 200) * 2.0/HEIGHT);
            //            double scaledY = (y - HEIGHT/2.0) * 2.0/HEIGHT;
            
            // Put these co-ords into the mandlebrot algo. scaledValues.first is x, scaledValues.second is y.
            int iterations = Mandlebrot::mandleBrotAlgorithm(scaledValues.first, scaledValues.second);
            
            pixelIterations[(y * WIDTH) + x] = iterations;
            
            // Increment the histogram array at the index of the iteration. Unless it is MAX_ITERATIONS, which we do not want to store in the histogram.
            if (iterations < Mandlebrot::MAX_ITERATIONS) {
                histogram[iterations]++;
            }
        }
    }
    
    // You also need to calculate the total number of iterations for the whole calculation process so that you can use this to scale the color calculations below. Just sum all the int values in the histogram.
    int totalIterations = 0;
    for (int i = 0; i < Mandlebrot::MAX_ITERATIONS; i++) {
        totalIterations += histogram[i];
    };
    
    // Second nested loop to actually draw the pixels based on the now completed histogram.
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Get the number of iterations that these pixel coords took to break out of the Mandlebrot algo
            int iterations = pixelIterations[(y * WIDTH) + x];
            
            // You will calc the hue based on the number of pixels that took fewer iterations to complete the algorithm than the current pixel.
            double hue = 0.0;
            for (int i = 0; i < iterations; i++) {
                hue += (double)histogram[i]/totalIterations;
            }
            
            // a uint8_t data type will automatically keep its value between 0 and 255. If you try and save a higher value into it then it will just loop around the possible values automatically (like an automatic modulo calculation). This behaviour is the same behaviour that historically caused bugs and issues like the Y2K bug where a data type just runs out of bits and resets to zero.
            //            uint8_t color = (uint8_t)(256 * (double)iterations/Mandlebrot::MAX_ITERATIONS);
            
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;
            
            if (iterations != Mandlebrot::MAX_ITERATIONS) {
                // The calculate a colour.
                red = pow(255, hue);
                green = 0;
                blue = 0;
            }
            
            bitmap.setPixel(x, y, red, green, blue);
        }
    }
    
    // Simple loop to check that the histogram is being filled correctly.
    //    double count = 0;
    //    for (int i = 0; i < Mandlebrot::MAX_ITERATIONS; i++) {
    //        count += histogram[i];
    //        std::cout << histogram[i] << std::endl;
    //    }
    //    std::cout << count << " : " << WIDTH * HEIGHT << std::endl;
    //
    //    std::cout << " ------------------------------- " << std::endl;
    
    // Simple loop to check that the pixelIterations is being filled correctly.
    //    double itCount = 0;
    //    for (int j = 0; j < WIDTH * HEIGHT + 1; j++) {
    //        count += pixelIterations[j];
    //        std::cout << pixelIterations[j] << std::endl;
    //    }
    //    std::cout << itCount << std::endl;
    
    bitmap.writeToFile("test.bmp");
    std::cout << "Finished" << std::endl;
    
    return 0;
}
