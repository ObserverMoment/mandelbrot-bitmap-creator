//
//  FractalCreator.cpp
//  FractalCreator
//
//  Created by Rich Beans on 08/09/2017.
//  Copyright © 2017 Rich Beans. All rights reserved.
//

#include "FractalCreator.hpp"

void FractalCreator::run(std::string filename) {
    calculateIterations();
    std::cout << "Finished Algo" << std::endl;
    drawPixels();
    std::cout << "Drawn Pixels" << std::endl;
    writeToFile(filename);
    std::cout << "Written To File" << std::endl;
};

void FractalCreator::addColourRange(const RGB& colour, double rangeUpper) {
    // Add some error checking to make sure that you are not adding a range value that is lower then the previous highest range value in the vector. Ranges need to increase as you move through the vector otherwise it will not work.
    // Convert the new range value into a value for a number of pixels as a ratio of the MAX_ITERATIONS constant.
    int upperPixelsRange = rangeUpper * Mandlebrot::MAX_ITERATIONS;
    if (rangeSplits.size() == 0) {
        // Then this is the first range that is being added and you do not need to check for an upper bound.
        if (rangeUpper > 1.0) {
            std::cout << "The range of valid values for this input is 0 <= x <= 1.0" << std::endl;
            std::cout << rangeUpper << std::endl;
        } else {
            // Add the range if it is valid
            m_colours.push_back(colour);
            rangeSplits.push_back(upperPixelsRange);
            std::cout << "Upper Pixels Range: " << upperPixelsRange << std::endl;
            std::cout << "Num Ranges After New Range: " << rangeSplits.size() << std::endl;
        }
    } else {
        // You must check both the upper range and that the value is <= 1.0
        if (upperPixelsRange < rangeSplits[rangeSplits.size()-1]) {
            std::cout << "You cannot specify a range with an upper bound lower than the highest bound that already exists" << std::endl;
            std::cout << rangeUpper << std::endl;
        } else if (rangeUpper > 1.0) {
            std::cout << "The range of valid values for this input is 0 <= x <= 1.0" << std::endl;
            std::cout << rangeUpper << std::endl;
        } else {
            // Add the range if it is valid
            m_colours.push_back(colour);
            rangeSplits.push_back(upperPixelsRange);
            std::cout << "Upper Pixels Range: " << upperPixelsRange << std::endl;
            std::cout << "Num Ranges After New Range: " << rangeSplits.size() << std::endl;
        }
    };
};

void FractalCreator::calculateIterations() {
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
    // Save the total sum of all the iteration results.
    // Calculate the total number of iterations for the whole calculation process so that you can use this to scale the color calculations below. Just sum all the int values in the histogram.
    for (int i = 0; i < Mandlebrot::MAX_ITERATIONS; i++) {
        totalIterations += histogram[i];
    };
    
}

void FractalCreator::drawPixels() {
    
    // Create two new RGB objects for use on each iteration. Default them to black.
    RGB startColour(0,0,0);
    RGB endColour(0,0,0);
    
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            // Get the number of iterations that these pixel coords took to break out of the Mandlebrot algo
            int currentPixelIterations = pixelIterations[(y * m_width) + x];
            
            // Loop through the range vector to get the range boundary that is below and above this value within that vector.
            // Save the index of the lower and upper range so you can recall the value stored there later on when calculating the hue.
            int lowerIndex = 0;
            int upperIndex = 1;
            for (int i = 0; i < rangeSplits.size(); i++) {
                // Check if the currentRangeRatio falls between the value at the current index and the value at the next index in the rangeSplits vector. If it does then this is the correct range for this pixel iteration and you can set the start and end colours based on the corresponding indexs in the m_colours vector.
                if (currentPixelIterations > rangeSplits[i] && currentPixelIterations <= rangeSplits[i+1]) {
                    // Log the indexes for later use.
                    lowerIndex = i;
                    upperIndex = i + 1;
//                    std::cout << "LIndex: " << rangeSplits[lowerIndex] << std::endl;
//                    std::cout << "UIndex: " << rangeSplits[upperIndex] << std::endl;
                    // Transfer the colour data from the m_colours vector objects to the start and end colour being used for this pixel.
                    // OPTION: Change the start colour - the start colour is usually black in most fractal images.
                    startColour.r = m_colours[i].r;
                    startColour.g = m_colours[i].g;
                    startColour.b = m_colours[i].b;
                    endColour.r = m_colours[i+1].r;
                    endColour.g = m_colours[i+1].g;
                    endColour.b = m_colours[i+1].b;
                    break;
                }
            }
            
            // Calculate the total iterations in the range.
            int totalIterationsInRange = 0;
            for (int i = rangeSplits[lowerIndex]; i < rangeSplits[upperIndex]; i++) {
                totalIterationsInRange += histogram[i];
            }
            
            
            // You will calc the hue based on the number of pixels that took fewer iterations to complete the algorithm than the current pixel.
            double hue = 0.0;
            for (int i = 0; i < currentPixelIterations; i++) {
                hue += (double)histogram[i]/totalIterationsInRange;
            }
            
            // a uint8_t data type will automatically keep its value between 0 and 255. If you try and save a higher value into it then it will just loop around the possible values automatically (like an automatic modulo calculation). This behaviour is the same behaviour that historically caused bugs and issues like the Y2K bug where a data type just runs out of bits and resets to zero.
            //            uint8_t color = (uint8_t)(256 * (double)iterations/Mandlebrot::MAX_ITERATIONS);
            
            // Then calculate a colour.
            uint8_t red = startColour.r + pow(endColour.r - startColour.r, hue);
            uint8_t green = startColour.g + pow(endColour.g - startColour.g, hue);
            uint8_t blue = startColour.b + pow(endColour.b - startColour.b, hue);
            
            bitmap.setPixel(x, y, red, green, blue);
        }
    }
};

void FractalCreator::writeToFile(std::string filename) {
    bitmap.writeToFile(filename);
};
