//
//  FractalCreator.hpp
//  FractalCreator
//
//  Created by Rich Beans on 08/09/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#ifndef FractalCreator_hpp
#define FractalCreator_hpp

#include <math.h>
#include <vector>
#include "ZoomList.h"
#include "Mandlebrot.hpp"
#include "Bitmap.hpp"
#include "RGB.hpp"

class FractalCreator {
private:
    int m_width{0};
    int m_height{0};
    int totalIterations{0};
    Bitmap bitmap;
    ZoomList zoomList;
    
    // We only need to go up to MAX_ITERATIONS because we are intentionally ignoring the all the values that hit the max_iterations value. We do this because we want a smooth gradient across the histogram and when we run the algorithm we actually get a smooth, decreasing gradient up until MAX and then MAX is a very large number.
    std::unique_ptr<int[]> histogram;
    std::unique_ptr<int[]> pixelIterations;
    
    // These two vectors will store color objects and float ranges. The first will be a RGB colour object. The second will be a value between 0 and 1 which will represent the full range of possible iterations that any pixel value can return once converted to cartesian coords and passed to the Mandelbro algo.
    std::vector<RGB> m_colours;
    std::vector<int> rangeSplits;
    
private:
    void calculateIterations();
    void drawPixels();
    void writeToFile(std::string filename);
    
public:
    FractalCreator(int width, int height): m_width(width), m_height(height), histogram(new int[Mandlebrot::MAX_ITERATIONS]{0}), pixelIterations(new int[width * height]{0}), bitmap(width, height), zoomList(width, height) {
        // Initialize the first zoom within the constructor.
        addZoom(m_width/2, m_height/2, 1);
    };
    
    void addZoom(int pixelX, int pixelY, double zoom) {
        zoomList.addZoom(Zoom(pixelX, m_height-pixelY, zoom));
    }
    
    // Here you can specify a colour in RGB form and a fraction between 0 and 1.
    // This colour will then be used when iterations for that pixel fall between maxIterations for this range, and maxIterations for the previous range that you added - or between maxIterations and zero if it is the first range that you are adding. The end result will be a vector of pairs or colours and values which will split the ful range between 0 and 1. You also probably want to add some tests to make sure that you are not adding a range that is lower than a range that already exists.
    void addColourRange(const RGB& colour, double rangeUpper);
    
    void run(std::string filename);

};

#endif /* FractalCreator_hpp */
