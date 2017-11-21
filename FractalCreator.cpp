//
//  FractalCreator.cpp
//  FractalCreator
//
//  Created by Rich Beans on 08/09/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#include "FractalCreator.hpp"


void FractalCreator::calculateIterations(ZoomList& zoomList, std::unique_ptr<int[]>& histogram, std::unique_ptr<int[]>& pixelIterations) {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            // Instead of the code below you can use the zoomList.doZoom method to convert from screen pixel to a scaled X and Y value based on the zoomList current x, y and scale values. Then pass these values to the mandlebrot algo for processing.
            std::pair<double, double> scaledValues = zoomList.doZoom(x,y);
            
            // Put these co-ords into the mandlebrot algo. scaledValues.first is x, scaledValues.second is y.
            int iterations = Mandlebrot::mandleBrotAlgorithm(scaledValues.first, scaledValues.second);
            
            pixelIterations[(y * m_width) + x] = iterations;
            
            // Increment the histogram array at the index of the iteration. Unless it is MAX_ITERATIONS, which we do not want to store in the histogram.
            if (iterations < Mandlebrot::MAX_ITERATIONS) {
                histogram[iterations]++;
            }
        }
    }
}
